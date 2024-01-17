import numpy as np
import matplotlib.pyplot as plt
from filterpy.kalman import KalmanFilter
from filterpy.common import Q_discrete_white_noise
import cv2.aruco as aruco
from save_data import pixel_to_mm

Max_centers_length = 60 

# Initialize Kalman Filter
def initialize_kalman_filter():
    kf = KalmanFilter(dim_x=4, dim_z=2)
    kf.x = np.array([0., 0., 0., 0.])  # Initial state (x, y, vx, vy)
    kf.F = np.array([[1., 0., 1., 0.],  # State transition matrix
                     [0., 1., 0., 1.],
                     [0., 0., 1., 0.],
                     [0., 0., 0., 1.]])
    kf.H = np.array([[1., 0., 0., 0.],  # Measurement function
                     [0., 1., 0., 0.]])
    kf.P *= 100.  # Covariance matrix
    kf.R = 1  # Measurement noise
    #kf.Q = Q_discrete_white_noise(dim=2, dt=1, var=0.1, block_size=2)
    return kf

# Create synthetic data (measurements)


marker_dict = aruco.getPredefinedDictionary(aruco.DICT_4X4_250)
aruco_params = aruco.DetectorParameters()

centers= []

def get_measurements(img,color_to_track):
    corners, ids, rejected = aruco.detectMarkers(img, marker_dict, parameters=aruco_params)
    center = []
    global centers
    if ids is not None:
        for i, marker_id in enumerate(ids.flatten()):
            if color_to_track[0] <= marker_id <= color_to_track[1]:
                print("detected", marker_id)
                center = np.mean(corners[i][0], axis=0)
                
                centers.append(center)
    else :
        print("NO IDS detected")
    if len(centers) > Max_centers_length:
        centers = centers[-50:]

# Global variable for the Kalman filter
kf = initialize_kalman_filter()

def predict_future_positions_kalman(num_future_steps=8, threshold=10, max_measurements=20):
    global kf
    global centers  # Assuming centers are your measurements

    print("Prediction")
    
    # Check if enough measurements are available
    if len(centers) < threshold:
        print("Insufficient data")
        return None, None

    # Limit the number of measurements if necessary
    if len(centers) > max_measurements:
        centers = centers[-max_measurements:]

    # Process each measurement
    for measurement in centers:
        z = np.array(measurement).reshape(-1, 1)
        kf.predict()
        kf.update(z)

    # Predict future positions
    future_positions = []
    for _ in range(num_future_steps):
        kf.predict()
        future_positions.append(kf.x[:2])

    future_positions = np.array(future_positions)
    current_position = centers[-1] if centers else [0, 0]
    return current_position, future_positions




# Initialize the Kalman Filter

# Plotting
