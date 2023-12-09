import cv2 as cv
import numpy as np
from cv2 import aruco

######################################################################################################################""
########################     THIS IS TO TRY THE TOP DOWN VIEW BUT WE HARCODE VALUES USING MOUSE  ####################################################""
######################################################################################################################""


# Load the image and ArUco parameters
img = cv.imread(r"C:\Users\MSI\Desktop\WhatsApp Image 2023-12-08 at 18.34.25.jpeg")

gray_frame = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
marker_dict = aruco.getPredefinedDictionary(aruco.DICT_4X4_50)
param_markers = cv.aruco.DetectorParameters()

# Get image dimensions
height, width = img.shape[:2]

# Detect markers
marker_corners, marker_IDs, _ = aruco.detectMarkers(gray_frame, marker_dict, parameters=param_markers)

colors = [
    (255, 0, 0),   # Blue for top-right
    (0, 255, 0),   # Green for top-left
    (0, 0, 255),   # Red for bottom-right
    (255, 255, 0)  # Cyan for bottom-left
]

if marker_corners:
    for ids, corner_group in zip(marker_IDs, marker_corners):
        int_corners = corner_group[0].astype(int)
        marker_center = int_corners.mean(axis=0)

        # Calculate distances to corners of the image
        distances = {
            "top_left": np.linalg.norm(marker_center - np.array([0, 0])),
            "top_right": np.linalg.norm(marker_center - np.array([width, 0])),
            "bottom_left": np.linalg.norm(marker_center - np.array([0, height])),
            "bottom_right": np.linalg.norm(marker_center - np.array([width, height]))
        }

        # Determine the closest corner
        closest_corner = min(distances, key=distances.get)
        print(f"Marker ID {ids[0]} is closest to thqe {closest_corner} corner.")

        # Draw the marker borders and the marker ID
        cv.polylines(img, [int_corners], True, (0, 255, 0), 2)
        cv.putText(img, f"id: {ids[0]}", tuple(int_corners[0]), cv.FONT_HERSHEY_PLAIN, 1, (0, 0, 255), 2)

        # Draw colored circles on each corner
        for i, corner in enumerate(int_corners):
            cv.circle(img, tuple(corner), 5, colors[i], -1)

# Set up for perspective transform
circles = np.zeros((4, 2), np.int_)
counter = 0

def MouseClick(event, x, y, flags, parms):
    global counter
    if event == cv.EVENT_LBUTTONDOWN and counter < 4 : 
        print(x, y)
        circles[counter] = x, y
        print(circles)
        counter += 1


while True:
    cv.imshow("frame", img)
    cv.setMouseCallback("frame", MouseClick)

    # Check if all four points have been selected
    if np.all(circles != 0):
        pts1 = np.float32([circles[0], circles[1], circles[2], circles[3]])
        pts2 = np.float32([[0, 0], [width, 0], [0, height], [width, height]])
        matrix = cv.getPerspectiveTransform(pts1, pts2)
        output = cv.warpPerspective(img, matrix, (width, height))
        cv.imshow("Perspective Transform", output)

    key = cv.waitKey(1)
    if key == 27:  # ESC key
        break


cv.destroyAllWindows()
######################################################################################################################""
########################     THIS IS TO TRY THE TOP DOWN VIEW BUT WE HARCODE VALUES USING MOUSE  ####################################################""
######################################################################################################################""

