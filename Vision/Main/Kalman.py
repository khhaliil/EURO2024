import numpy as np
from filterpy.kalman import KalmanFilter
import cv2.aruco as aruco

Max_centers_length =60

# Initialize Kalman Filter
def initialize_kalman_filter():
    kf = KalmanFilter(dim_x=4, dim_z=2)
    kf.x = np.array([0., 0., 0., 0.])
    kf.F = np.array([[1., 0., 1., 0.], [0., 1., 0., 1.], [0., 0., 1., 0.], [0., 0., 0., 1.]])
    kf.H = np.array([[1., 0., 0., 0.], [0., 1., 0., 0.]])
    kf.P *= 10.
    kf.R = 1
    return kf

marker_dict = aruco.getPredefinedDictionary(aruco.DICT_4X4_250)
aruco_params = aruco.DetectorParameters()

# Dictionary to store centers for each tag
tag_centers = {}

def get_measurements(img, tags_to_track,debug=True):
    corners, ids, rejected = aruco.detectMarkers(img, marker_dict, parameters=aruco_params)
    if ids is not None:
        for i, marker_id in enumerate(ids.flatten()):
            if marker_id in tags_to_track:
                if debug:
                    print("Detected", marker_id)
                center = np.mean(corners[i][0], axis=0)
                if marker_id not in tag_centers:
                    tag_centers[marker_id] = []
                tag_centers[marker_id].append(center)

                # Limit the length of center data
                if len(tag_centers[marker_id]) > Max_centers_length:
                    tag_centers[marker_id] = tag_centers[marker_id][-50:]
    else:
        if debug:
            print("No IDs detected")

def predict_future_positions_kalman(tag, num_future_steps=6, threshold=10, max_measurements=30,debug=True):
    global tag_centers

    if tag not in tag_centers or len(tag_centers[tag]) < threshold:
        if debug:
            print(f"Insufficient data for tag {tag}")
        return None, None

    kf = initialize_kalman_filter()
    measurements = tag_centers[tag][-max_measurements:]  # Get the latest measurements

    # Process each measurement
    for measurement in measurements:
        z = np.array(measurement).reshape(-1, 1)
        kf.predict()
        kf.update(z)

    # Predict future positions
    future_positions = []
    for _ in range(num_future_steps):
        kf.predict()
        future_positions.append(kf.x[:2])

    future_positions = np.array(future_positions)
    current_position = measurements[-1] if measurements else [0, 0]
    return current_position, future_positions

