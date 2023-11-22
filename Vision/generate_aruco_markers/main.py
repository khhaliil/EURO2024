import cv2 as cv 
from cv2 import aruco
 
#Marker_size = 400
marker_dict = aruco.Dictionary(aruco.DICT_4X4_1000,200)

param_markers=aruco.DetectorParameters()


cap = cv.VideoCapture(0) 
 

while True:
    ret,frame = cap.read()
    if not ret :
        break
    gray_frame = cv.cvtColor(frame,cv.COLOR_BGR2GRAY)
    markerCorners,markerIds,reject=aruco.detectMarkers(gray_frame,marker_dict,parameters=param_markers)
    print(markerIds)
    cv.imshow("img",frame)
    key = cv.waitKey(1)
    if key == ord('s'):
        break
    

cap.release()
cv.destroyAllWindows()