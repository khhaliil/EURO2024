import cv2
import cv2.aruco as aruco
import numpy as np
from save_data import save_frame
from save_data import Calculate_homography
from save_data import pixel_to_mm
from Kalman import get_measurements, predict_future_positions_kalman
import os
import sys
from save_data import Button, save_frame
import Model
from Model import process_and_visualize_image
# Replace with the absolute path to EURO directory
sys.path.append(r'C:\Users\MSI\Desktop\EURO2024')
# COLORS ##################################################""
gray_output = False
BLUE_TEAM_RANGE = [1, 2, 3, 4, 5]
YELLOW_TEAM_RANGE = [6, 7, 8, 9, 10]
color_to_track = YELLOW_TEAM_RANGE
##################################### ARUCO ##################################################
marker_dict = aruco.getPredefinedDictionary(aruco.DICT_4X4_250)
aruco_params = aruco.DetectorParameters()
# HOMOGRAPHY ###########################################""
Calculate_homography_manually = False
homography_calculated = False
global capture_mode
capture_mode = False
bird_view_done = False
flip = False
homography_matrix_path = r"C:\Users\MSI\Desktop\EURO2024\Tools\homography_matrix.npz"
map_corners_3d = np.float32([[0, 0], [2, 0], [2, 3], [0, 3]])
save_button = Button(10, 10, 60, 30, "Save")
mapx, mapy = 2, 3
# MODEL ###########################################################""
yolo_model = Model.initialize_yolo(
    r"C:\Users\MSI\Desktop\EURO2024\Vision\Data\Model V0\runs\detect\train6\weights\best.pt")
Model.create_trackbar("Adjustments")
#############################################################################################


def nothing(x):
    pass


def switch_team(team_color):
    global current_team_range
    if team_color.lower() == 'blue':
        current_team_range = BLUE_TEAM_RANGE
    elif team_color.lower() == 'yellow':
        current_team_range = YELLOW_TEAM_RANGE
    else:
        print(f"Unknown team color: {team_color}")
#########################################################################################


def load_homography_matrix(path):
    try:
        with np.load(path) as data:
            return data['homography_matrix']
    except KeyError:
        print(f"'homography_matrix' not found in {path}")
        return None
    except IOError:
        print(f"Could not read file: {path}")
        return None


homography_matrix = load_homography_matrix(homography_matrix_path)
#########################################################################################


def click_event(event, x, y, flags, param):
    global capture_mode

    # First, check for button click
    if event == cv2.EVENT_LBUTTONDOWN:
        if save_button.check_click(x, y):
            save_frame(img_top_down, prefix='top_down', manual_save=True)
            return

        # If not a button click, check for capture mode
        if capture_mode:
            captured_x, captured_y = x, y
            print("Captured real coordinates",
                  pixel_to_mm(captured_x, captured_y))
            print(f"Captured pixel coordinates: {captured_x}, {captured_y}")
            capture_mode = False


def button_click_event(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN:
        if save_button.check_click(x, y):
            save_frame(img_top_down, prefix='top_down', manual_save=True)


def launch_saving_window():
    save_button.draw(button_window_img)
    cv2.imshow('Button Window', button_window_img)


cv2.namedWindow('Top-Down View')
cv2.setMouseCallback('Top-Down View', click_event)
cv2.namedWindow('Button Window')
cv2.setMouseCallback('Button Window', button_click_event)
cv2.namedWindow("Trackbars")
cv2.createTrackbar("X Correction", "Trackbars", 850, 1000,
                   nothing)  # 50 is the initial value
######################################### TRACKING ############################################################
global_current_position = None
global_enemy_robot_predictions = None


def update_tracking_data(tag_to_track):
    global global_current_position, global_enemy_robot_predictions

    get_measurements(img_top_down, tags_to_track=color_to_track, debug=False)

    for tag in color_to_track:
        current_position, ennemy_robot_predictions = predict_future_positions_kalman(
            tag, debug=False)
        if current_position is not None:
            global_current_position = pixel_to_mm(
                current_position[0], current_position[1])
            cv2.circle(img_top_down, (int(current_position[0]), int(
                current_position[1])), 5, (255, 0, 255), -1)
        if ennemy_robot_predictions is not None:
            global_enemy_robot_predictions = [pixel_to_mm(
                pos[0], pos[1]) for pos in ennemy_robot_predictions]
            for pos in ennemy_robot_predictions:
                x, y = int(pos[0]), int(pos[1])
                cv2.circle(img_top_down, (x, y), 4, (0, 0, 255), -1)
    return global_current_position, global_enemy_robot_predictions


####################################################################################
distorsion_coef = 0.967
min_cluster_size=3

####################################################################################
cap = cv2.VideoCapture(3)
cv2.namedWindow("Trackbars")
initial_radius_threshold = 5  # Initial value
cv2.createTrackbar('Radius Threshold', 'Trackbars',
                   initial_radius_threshold, 150, nothing)
cv2.createTrackbar("Marker Length", "Trackbars", 10, 20,
                   nothing)  # Range from 0.1m to 0.2m
cv2.createTrackbar("X Aruco", "Trackbars", 516, 1000, nothing)  # Example range
cv2.createTrackbar("Y Aruco", "Trackbars", 755, 1000, nothing)
button_window_img = np.zeros((100, 200, 3), dtype=np.uint8)
while True:
    ret, img = cap.read()
    if not ret:
        print("erreur image")
        break
    if flip:
        img = cv2.flip(img, -1)
    if gray_output:
        img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    img_top_down = img
    # Calculation ###############################""
    # si lhomgrpahie nest pas calculé
    if homography_calculated == False:
        if homography_matrix is None or Calculate_homography_manually == True:
            corners, ids, rejected = aruco.detectMarkers(
                img, marker_dict, parameters=aruco_params)
            homography_matrix = Calculate_homography(corners, ids, img)
            # print("hhnfdj",homography_matrix)
            if homography_matrix is not None:
                Calculate_homography_manually = not Calculate_homography_manually
                homography_calculated = True
            else:
                print("Homography matrix calculation failed")
        else:
            print("loaded homography matrix from local")
            homography_calculated = True
    # si l'homographie est calcule
    if homography_matrix is not None and not bird_view_done:
        try:
            map_corners_2d = cv2.perspectiveTransform(
                map_corners_3d.reshape(-1, 1, 2), homography_matrix)
        except cv2.error as e:
            print(f"Error in perspective transform: {e}")
        points = []
        for i in range(map_corners_2d.shape[0]):
            point = tuple(map_corners_2d[i, 0].astype(int))
            points.append(point)
        src_pts = np.array(
            [points[1], points[0],  points[2], points[3]], dtype='float32')
        dst_pts = np.array([[0, 0], [0, img.shape[0]],  [img.shape[1], 0], [
                           img.shape[1], img.shape[0]]], dtype='float32')
        M = cv2.getPerspectiveTransform(src_pts, dst_pts)
        homography_calculated = True
        bird_view_done = not bird_view_done
    
    ennemy_robot_predictions = []
    img_top_down = cv2.warpPerspective(img, M, (img.shape[1], img.shape[0]))
    img_top_down_cp = img_top_down.copy()
    current_pos, ennemy_pos_preduction = update_tracking_data(color_to_track)
    correction_factor = cv2.getTrackbarPos("X Correction", "Trackbars") / 1000
    launch_saving_window()
    radius_threshold = 40
    
    #img_top_down, obstacles, centers = process_and_visualize_image(img_top_down, yolo_model, distorsion_coef,cv2.getTrackbarPos('Radius Threshold', 'Trackbars'), min_cluster_size)

    cv2.imshow('Top-Down View', img_top_down)
    cv2.imshow('Marked Image', img)

    key = cv2.waitKey(1) & 0xFF
    if key == ord('s'):
        # Manual save
        save_frame(img_top_down_cp, prefix='top_down', manual_save=True)
    else:
        # Automatic save every 10 seconds
        pass
        # save_frame(img_top_down, prefix='top_down', interval=12)
    if key == ord('g'):
        # Toggle capture mode
        capture_mode = not capture_mode
        if capture_mode:
            print("Capture mode activated. Click on the desired pixel.")
        else:
            print("Capture mode deactivated.")
    if key == ord('h'):
        # Toggle the Calculate_homography_manually flag
        Calculate_homography_manually = not Calculate_homography_manually
        homography_calculated = False
        bird_view_done = not bird_view_done
        if Calculate_homography_manually:
            print("Manual homography calculation mode activated.")
        else:
            print("Manual homography calculation mode deactivated.")
    if key == ord('q'):
        break


cap.release()
cv2.destroyAllWindows()
