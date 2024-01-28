import cv2
from ultralytics import YOLO
import numpy as np
from save_data import calculate_distance_from_camera
import math


def initialize_yolo(model_path):
    model = YOLO(model_path)
    return model


def perform_detection(model, image, radius_correction_factor, threshold=0.45):
    results = model.predict(image)
    centers = []

    for result in results:
        for i in range(len(result.boxes)):
            box = result.boxes.data[i]
            x1, y1, x2, y2 = map(int, box[:4])
            confidence, class_id = box[4].item(), int(box[5])
            # Only process boxes with confidence greater than the threshold
            if confidence > threshold:
                center_x, center_y = (x1 + x2) // 2, (y1 + y2) // 2
                corrected_x, corrected_y = treat_camera_distorsion(
                    center_x, center_y, radius_correction_factor)
                centers.append(((int(corrected_x), int(corrected_y)),
                               confidence, result.names[class_id]))

    return centers


def draw_distance_line(image, objx, objy, color):
    camerax = 320
    cameray = 480
    distance = calculate_distance_from_camera(objx, objy)

    objx = int(objx)
    objy = int(objy)
    # Draw a line from camera to object
    if color == 1:
        cv2.line(image, (camerax, cameray), (objx, objy), (255, 0, 0), 1)
    if color == 2:
        cv2.line(image, (camerax, cameray), (objx, objy), (0, 255, 0), 2)
    # Optionally, you can put a text label indicating the distance
    label = f"Distance: {distance:.2f} units"
    cv2.putText(image, label, (objx, objy),
                cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 0, 0), 1)

    return image


def adjust_center(bbox, img_width, img_height, vertical_factor, horizontal_factor):
    x1, y1, x2, y2 = bbox
    bbox_width = x2 - x1
    bbox_height = y2 - y1

    center_x = x1 + bbox_width / 2
    center_y = y1 + bbox_height / 2

    # Adjust for vertical distortion
    vertical_adjustment = (bbox_height * (y1 + y2) /
                           2 / img_height) * vertical_factor
    adjusted_center_y = center_y - vertical_adjustment

    # Adjust for horizontal distortion
    horizontal_adjustment = (bbox_width * (x1 + x2) /
                             2 / img_width) * horizontal_factor
    adjusted_center_x = center_x - horizontal_adjustment

    return (int(adjusted_center_x), int(adjusted_center_y))


def create_trackbar(window_name):
    def nothing(x):
        pass

    cv2.namedWindow(window_name)
    cv2.createTrackbar('Vertical Factor', window_name, -10, 10, nothing)
    cv2.createTrackbar('Horizontal Factor', window_name, -10, 10, nothing)


# DISTORSION CORRECTION #####################################""
def abs_to_cam_cartesian(x, y):
    """
    Convertit les coordonnées d'un pixel (x, y) dans une image de dimension 480x640 pixels
    à un nouveau système de coordonnées où le point (480,320) est le nouveau (0,0).

    Args:
    x (int): Coordonnée x du pixel dans l'ancien système de coordonnées.
    y (int): Coordonnée y du pixel dans l'ancien système de coordonnées.

    Returns:
    tuple: Nouvelles coordonnées (nouveau_x, nouveau_y) dans le nouveau système.
    """
    nouveau_x = x - 320
    nouveau_y = 480 - y
    return nouveau_x, nouveau_y


def cartesian_to_polar(x, y, coef):
    """
    Convertit les coordonnées cartésiennes (x, y) en coordonnées polaires (r, θ en degrés)
    sans aucune contrainte supplémentaire.

    Args:
    x (float): Coordonnée x en cartésien.
    y (float): Coordonnée y en cartésien.

    Returns:
    tuple: Coordonnées polaires (r, θ en degrés), où r est le rayon et θ est l'angle en degrés.
    """
    r = math.sqrt(x**2 + y**2)*coef

    theta_rad = math.atan2(y, x)
    theta_deg = math.degrees(theta_rad)
    return r, theta_deg


def polar_to_cartesian(r, theta_deg):
    """
    Convertit les coordonnées polaires (r, θ en degrés) en coordonnées cartésiennes (x, y).

    Args:
    r (float): Rayon en coordonnées polaires.
    theta_deg (float): Angle en degrés en coordonnées polaires.

    Returns:
    tuple: Coordonnées cartésiennes (x, y).
    """
    theta_rad = math.radians(theta_deg)
    seuil = 1e-10
    x = r * math.cos(theta_rad)
    y = r * math.sin(theta_rad)

    x = 0 if abs(x) < seuil else round(x)
    y = 0 if abs(y) < seuil else round(y)
    return x, y


def cam_cartesian_to_abs(nouveau_x, nouveau_y):
    """
    Convertit les coordonnées d'un pixel dans le nouveau système de coordonnées centré sur la caméra
    (où le point (320,480) est le nouveau (0,0)) en coordonnées absolues dans le système d'origine
    pour une image de dimension 480x640 pixels.

    Args:
    nouveau_x (int): Coordonnée x du pixel dans le nouveau système de coordonnées.
    nouveau_y (int): Coordonnée y du pixel dans le nouveau système de coordonnées.

    Returns:
    tuple: Coordonnées absolues (x, y) dans l'ancien système.
    """
    x = nouveau_x + 320
    y = 480 - nouveau_y
    return x, y


def treat_camera_distorsion(x, y, coef=1):
    xcam, ycam = abs_to_cam_cartesian(x, y)
    r, theta = cartesian_to_polar(xcam, ycam, coef)
    new_xcam, new_ycam = polar_to_cartesian(r, theta)
    return cam_cartesian_to_abs(new_xcam, new_ycam)

###################################################################


def process_centers(centers, radius_threshold, min_cluster_size=3):
    obstacles = []
    used = set()
    total_plant_count = 0
    total_pot_count = 0

    for i, ((center1_x, center1_y), _, class_name1) in enumerate(centers):
        if i in used:
            continue

        cluster = [(center1_x, center1_y)]
        plant_count = 0
        pot_count = 0
        if class_name1 == 'plant':
            plant_count += 1
        elif class_name1 == 'pot':
            pot_count += 1

        for j, ((center2_x, center2_y), _, class_name2) in enumerate(centers):
            if i != j and distance((center1_x, center1_y), (center2_x, center2_y)) <= radius_threshold:
                cluster.append((center2_x, center2_y))
                if class_name2 == 'plant':
                    plant_count += 1
                elif class_name2 == 'pot':
                    pot_count += 1
                used.add(j)

        if len(cluster) >= min_cluster_size:
            obstacle_center = calculate_cluster_center(cluster)
            obstacle_radius = calculate_cluster_radius(
                cluster, obstacle_center)
            total_plant_count += plant_count
            total_pot_count += pot_count
            obstacles.append({
                'center': obstacle_center,
                'radius': obstacle_radius,
                'contents': cluster,
                'total_flower_count': total_plant_count,
                'total_pot_count': total_pot_count
            })

    if len(obstacles) == 0:
        obstacles = None

    return obstacles

# Helper functions remain unchanged


def distance(center1, center2):
    return ((center1[0] - center2[0])**2 + (center1[1] - center2[1])**2)**0.5


def calculate_cluster_center(cluster):
    x, y = zip(*cluster)
    return (sum(x) / len(cluster), sum(y) / len(cluster))


def calculate_cluster_radius(cluster, center):
    return max(distance(center, point) for point in cluster)


def update_centers_and_obstacles(centers, obstacles):
    # Create a set of all centers that are part of an obstacle
    if obstacles == None:
        return centers, None

    if obstacles is not None:
        obstacle_centers = set()
        for obstacle in obstacles:
            for center in obstacle['contents']:
                obstacle_centers.add(center)

        # Filter the centers to include only those not in any obstacle
        updated_centers = [
            center_info for center_info in centers if center_info[0] not in obstacle_centers]

    return updated_centers, obstacles


def draw_centers_and_obstacles(image, obstacles, centers):
    # Draw each obstacle as a circle
    if obstacles is not None:
        for obstacle in obstacles:
            center_x, center_y = obstacle['center']
            radius = int(obstacle['radius'])
            content_length = len(obstacle['contents'])

            cv2.circle(image, (int(center_x), int(center_y)),
                       radius, (0, 255, 0), 1)  # Draw obstacle circle
            text_position = (int(center_x) - radius,
                             int(center_y) + radius + 20)

            cv2.putText(image, str(content_length), text_position,
                        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 1)

    if centers is not None:
        for (center_x, center_y), confidence, class_name in centers:
            cv2.circle(image, (center_x, center_y), 5, (0, 0, 255), -1)
            label = f'{class_name} {confidence:.2f}'
            cv2.putText(image, label, (center_x + 10, center_y + 10),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 1)

    return image, obstacles, centers


def process_and_visualize_image(image, model, radius_correction_factor, radius_threshold, min_cluster_size):
    # Step 1: Perform Detection
    centers = perform_detection(model, image, radius_correction_factor)

    # Step 2: Process Centers to Form Obstacles
    obstacles = process_centers(centers, radius_threshold, min_cluster_size)

    # Step 3: Update Centers and Obstacles
    # updated_centers, updated_obstacles = update_centers_and_obstacles(centers, obstacles)

    # Step 4: Draw Centers and Obstacles on the Image
    processed_image, updated_obstacles, updated_centers = draw_centers_and_obstacles(
        image, obstacles, centers)

    return processed_image, updated_centers, updated_obstacles


# Example usage
# Assuming 'img_top_down', 'yolo_model', etc. are defined and initialized


# Example usage
