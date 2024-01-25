import cv2
from ultralytics import YOLO
import numpy as np
from save_data import calculate_distance_from_camera
import math

def initialize_yolo(model_path):
    model = YOLO(model_path)
    return model

def perform_detection(model, image, radius_correction_factor):
    results = model.predict(image)
    centers = []

    camera_x, camera_y = image.shape[0]/2, image.shape[1]

    for result in results:
        for i in range(len(result.boxes)):
            box = result.boxes.data[i]
            x1, y1, x2, y2 = map(int, box[:4])
            confidence, class_id = box[4].item(), int(box[5])
            center_x, center_y = (x1 + x2) // 2, (y1 + y2) // 2
            corrected_x,corrected_y=treat_camera_distorsion(center_x,center_y,radius_correction_factor)
            centers.append(((int(corrected_x), int(corrected_y)), confidence, result.names[class_id]))

    return centers






def draw_distance_line(image, objx, objy,color):
    camerax = 320
    cameray = 480
    distance = calculate_distance_from_camera(objx, objy)

    objx = int(objx)
    objy = int(objy)
    # Draw a line from camera to object
    if color == 1 :
        cv2.line(image, (camerax, cameray), (objx, objy), (255, 0, 0), 1)
    if color == 2 :
        cv2.line(image, (camerax, cameray), (objx, objy), (0, 255, 0), 2)
    # Optionally, you can put a text label indicating the distance
    label = f"Distance: {distance:.2f} units"
    cv2.putText(image, label, (objx, objy), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 0, 0), 1)

    return image

def adjust_center(bbox, img_width, img_height, vertical_factor, horizontal_factor):
    x1, y1, x2, y2 = bbox
    bbox_width = x2 - x1
    bbox_height = y2 - y1

    center_x = x1 + bbox_width / 2
    center_y = y1 + bbox_height / 2

    # Adjust for vertical distortion
    vertical_adjustment = (bbox_height * (y1 + y2) / 2 / img_height) * vertical_factor
    adjusted_center_y = center_y - vertical_adjustment

    # Adjust for horizontal distortion
    horizontal_adjustment = (bbox_width * (x1 + x2) / 2 / img_width) * horizontal_factor
    adjusted_center_x = center_x - horizontal_adjustment

    return (int(adjusted_center_x), int(adjusted_center_y))
def create_trackbar(window_name):
    def nothing(x):
        pass

    cv2.namedWindow(window_name)
    cv2.createTrackbar('Vertical Factor', window_name, -10, 10, nothing)
    cv2.createTrackbar('Horizontal Factor', window_name, -10, 10, nothing)


####################################################################""
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

# Exemple d'utilisation de la fonction
exemple_x, exemple_y = 320, 0  # Coordonnées d'un pixel quelconque


def cartesian_to_polar(x, y,coef):
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



def treat_camera_distorsion(x,y,coef=1):
    xcam,ycam=abs_to_cam_cartesian(x,y)
    r,theta=cartesian_to_polar(xcam,ycam,coef)
    new_xcam,new_ycam=polar_to_cartesian(r,theta)
    return cam_cartesian_to_abs(new_xcam,new_ycam)



