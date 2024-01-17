import cv2 as cv
from cv2 import aruco
import numpy as np

marker_dict = aruco.getPredefinedDictionary(aruco.DICT_4X4_50)
#BLUR_INTENSITY = 1
#= aruco.DetectorParameters_create()
param_markers  = cv.aruco.DetectorParameters()

# CAMERA_WIDTH = 1280
# CAMERA_HEIGHT = 720

cap = cv.VideoCapture(2)
# cap.set(cv.CAP_PROP_FRAME_WIDTH, CAMERA_WIDTH)    
# cap.set(cv.CAP_PROP_FRAME_HEIGHT, CAMERA_HEIGHT)

cv.imshow("test",cap.read()[1])
while True:
    ret, frame = cap.read()
    frame = cv.flip(frame , -1)
   
    if not ret:
        break
    gray_frame = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    marker_corners, marker_IDs, reject = aruco.detectMarkers(
        gray_frame, marker_dict, parameters=param_markers
    )
    cv.imshow("gray",gray_frame)
    if marker_corners:
        for ids, corners in zip(marker_IDs, marker_corners):
            cv.polylines(
                frame, [corners.astype(np.int32)], True, (0, 255, 255), 1, cv.LINE_AA
            )
            corners = corners.reshape(4, 2)
            corners = corners.astype(int)
            top_right = corners[0].ravel()
            top_left = corners[1].ravel()
            bottom_right = corners[2].ravel()
            bottom_left = corners[3].ravel()
            cv.putText(
                frame,
                f"id: {ids[0]}",
                top_right,
                cv.FONT_HERSHEY_PLAIN,
                1,
                (200, 100, 0),
                1   ,
                cv.LINE_AA,
            )
            # print(ids, "  ", corners)
        
    frame_resized = cv.resize(frame, (1040, 960))  # Resize to double the capture resolution
    cv.imshow("frame", frame_resized)
    key = cv.waitKey(1)
    if key == ord("q"):
        break
cap.release()
cv.destroyAllWindows()