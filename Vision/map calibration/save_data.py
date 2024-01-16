import cv2
import time
from playsound import playsound  # Import playsound library
import cv2.aruco as aruco
import numpy as np 

def save_frame(img, base_path=r'C:\Users\MSI\Desktop\EURO2024\Vision\Data\dataTest_withoutAruco', prefix='frame', interval=5, manual_save=False):
    """
    Save frames to a specified path at a given interval or manually.

    Args:
    - img: Image to be saved.
    - base_path: Base path where images will be saved.
    - prefix: Prefix for the image filenames.
    - interval: Time interval in seconds between automatic saves.
    - manual_save: Flag to trigger manual saving.
    """
    last_saved_time = getattr(save_frame, "last_saved_time", 0)
    current_time = time.time()

    if manual_save or (current_time - last_saved_time) >= interval:
        # Play the "bip bip" sound before saving
        #playsound(r"C:\Users\MSI\Desktop\EURO2024\Tools\Censor_beep_sound_effect.mp3")  # Change 'notification_sound.mp3' to the path of your audio file
        time.sleep(2)  # Sleep for 4 seconds before capturing
        filename = f"{prefix}_{int(current_time)}.jpg"
        cv2.imwrite(filename, img)
        save_frame.last_saved_time = current_time
        #playsound(r"C:\Users\MSI\Desktop\EURO2024\Tools\Camera_Shutter_Sound_Effect.mp3")
        print(f"Saved: {filename}")

#####################################################################################

marker_dict = aruco.getPredefinedDictionary(aruco.DICT_4X4_250)
aruco_params = aruco.DetectorParameters()

mapx=2000
mapy=3000

def Calculate_homography(img, mapx=mapx/1000 , mapy=mapy/1000,homography_matrix_path = r"C:\Users\MSI\Desktop\EURO2024\Tools\homography_matrix.npz"):
    #img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    homography_matrix = None
    corners, ids, rejected = aruco.detectMarkers(img, marker_dict, parameters=aruco_params)

    if ids is not None:
        print("Detected ArUco IDs:", ids.flatten())
        aruco.drawDetectedMarkers(img, corners, ids)
    else:
        print("No ArUco markers detected")
    
# Define marker locations in 3D space (assuming they lie on the z=0 plane)
    marker_length = cv2.getTrackbarPos("Marker Length", "Trackbars") / 100.0  # Scaling back to meters
    x_aruco = cv2.getTrackbarPos("X Aruco", "Trackbars") / 1000.0  # Adjust scale as needed
    y_aruco = cv2.getTrackbarPos("Y Aruco", "Trackbars") / 1000.0  # Adjust scale as needed
    marker_locations_3d = {
    21: np.array([(x_aruco-marker_length, y_aruco-marker_length, 0), (x_aruco+marker_length, y_aruco-marker_length, 0), (x_aruco+marker_length, y_aruco+marker_length, 0), (x_aruco-marker_length, y_aruco+marker_length, 0)]),
    23: np.array([(mapx-x_aruco-marker_length, y_aruco-marker_length, 0), (mapx-x_aruco+marker_length, y_aruco-marker_length, 0), (mapx-x_aruco+marker_length, y_aruco+marker_length, 0), (mapx-x_aruco-marker_length, y_aruco+marker_length, 0)]),
    20: np.array([(x_aruco-marker_length, mapy-y_aruco-marker_length, 0), (x_aruco+marker_length, mapy-y_aruco-marker_length, 0), (x_aruco+marker_length, mapy-y_aruco+marker_length, 0), (x_aruco, mapy-y_aruco+marker_length, 0)]),
    22: np.array([(mapx-x_aruco-marker_length, mapy-y_aruco-marker_length, 0), (mapx-x_aruco+marker_length, mapy-y_aruco-marker_length, 0), (mapx-x_aruco+marker_length, mapy-y_aruco+marker_length, 0), (mapx-x_aruco-marker_length, mapy-y_aruco+marker_length, 0)])
    }   
# Assume all markers are on the same flat surface (z=0)
    image_points = []
    object_points = []
    
    if ids is not None:
        for i, marker_id in enumerate(ids.flatten()):
            if marker_id in marker_locations_3d:
                image_points.append(corners[i][0])
                object_points.append(marker_locations_3d[marker_id])
# Flatten the arrays for homography
    image_points = np.array(image_points).reshape(-1, 2)
    
    object_points = np.array(object_points).reshape(-1, 3)
# Compute the homography matrix if we have enough correspondences
    if len(image_points) >= 4:
    # Calculate homography
        homography_matrix, _ = cv2.findHomography(object_points[:, :2], image_points)
    # Define the 3D coordinates of the map corners assuming z=0
        np.savez(homography_matrix_path, homography_matrix=homography_matrix)

    # if len(image_points) < 4:
    #     cv2.imshow('Marked Image', img)
    #     print("Not enough markers detected to compute the homography matrix.")
    #     homography_matrix = None
    
    return homography_matrix 
    

def pixel_to_mm(pixelx,pixely,mapdimx=mapy,mapdimy=mapx,imageh=480,imagew=640):
    threshhold = 0.0001
    x=pixelx
    y=pixely
    mmx = x*(mapdimx/imagew)
    mmy= mapdimy - y*(mapdimy/imageh)
    mmx = 0 if mmx < threshhold else mmx 
    mmy = 0 if mmy < threshhold else mmy
    return mmx,mmy

