import cv2 as cv
from cv2 import aruco
import numpy as np

calib_data_path = r"C:\Users\MSI\Desktop\EURO2024\Vision\calibration\Calib_matrix\MultiMatrixMicrosoft.npz"

calib_data = np.load(calib_data_path)
print(calib_data.files)

cam_mat = calib_data["camMatrix"]
dist_coef = calib_data["distCoef"]
r_vectors = calib_data["rVector"]
t_vectors = calib_data["tVector"]

MARKER_SIZE = 10  # centimeters

marker_dict = aruco.getPredefinedDictionary(aruco.DICT_4X4_50)

param_markers = aruco.DetectorParameters()

cap = cv.VideoCapture(0)
cap.set(10, 50)


def denoise_frame(frame, strength=3):
    """
    Apply denoising to the given frame.
    :param frame: Input frame to be denoised
    :param strength: Denoising strength, higher values remove more noise but can remove image details
    :return: Denoised frame
    """
    # Check if the frame is valid
    if frame is None:
        return None

    # Apply fast Non-Local Means Denoising
    denoised_frame = cv.fastNlMeansDenoisingColored(frame, None, strength, strength, 7, 21)
    return denoised_frame

while True:
    ret, frame = cap.read()
    if not ret:
        break
    frame=denoise_frame(frame)
    gray_frame = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    
    marker_corners, marker_IDs, reject = aruco.detectMarkers(
        gray_frame, marker_dict, parameters=param_markers
    )
    if marker_corners:
        rVec, tVec, _ = aruco.estimatePoseSingleMarkers(
            marker_corners, MARKER_SIZE, cam_mat, dist_coef
        )
        total_markers = range(0, marker_IDs.size)
        for ids, corners, i in zip(marker_IDs, marker_corners, total_markers):
            cv.polylines(
                frame, [corners.astype(np.int32)], True, (0, 255, 255), 4, cv.LINE_AA
            )
            corners = corners.reshape(4, 2)
            corners = corners.astype(int)
            top_right = corners[0].ravel()
            top_left = corners[1].ravel()
            bottom_right = corners[2].ravel()
            bottom_left = corners[3].ravel()

            # Since there was mistake in calculating the distance approach point-outed in the Video Tutorial's comment
            # so I have rectified that mistake, I have test that out it increase the accuracy overall.
            # Calculating the distance
            distance = np.sqrt(
                tVec[i][0][2] ** 2 + tVec[i][0][0] ** 2 + tVec[i][0][1] ** 2
            )
            # Draw the pose of the marker
            point = cv.drawFrameAxes(frame, cam_mat, dist_coef, rVec[i], tVec[i], 4, 4)
            cv.putText(
                frame,
                f"id: {ids[0]} Dist: {round(distance, 1)}",
                top_right,
                cv.FONT_HERSHEY_PLAIN,
                1.1,
                (0, 0, 255),
                1,
                cv.LINE_AA,
            )
            cv.putText(
                frame,
                f"x:{round(tVec[i][0][0],1)} y: {round(tVec[i][0][1],1)} ",
                bottom_right,
                cv.FONT_HERSHEY_PLAIN,
                1.0,
                (0, 0, 255),
                1,
                cv.LINE_AA,
            )
            # print(ids, "  ", corners)
    cv.imshow("frame", frame)
    key = cv.waitKey(1)
    if key == ord("q"):
        break
cap.release()
cv.destroyAllWindows()