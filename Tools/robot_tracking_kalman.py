import numpy as np
import matplotlib.pyplot as plt
from filterpy.kalman import KalmanFilter
from filterpy.common import Q_discrete_white_noise

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
np.random.seed(42)
actual_x = np.linspace(0, 1, 20)
actual_y = actual_x * 2  # Quadratic path (hidden)
measurements = np.vstack((actual_x, actual_y)).T + np.random.normal(0, 0.01, (20, 2))



def predict_future_positions_kalman(measurement,num_future_steps = 8):
    kf = initialize_kalman_filter()

    for measurement in measurements:
        kf.predict()
        kf.update(measurement)
    
    future_positions = []
    future_velocities = []

    for _ in range(num_future_steps):
        kf.predict()
        future_positions.append(kf.x[:2])
        future_velocities.append(kf.x[2:])

    future_positions = np.array(future_positions)
    future_velocities = np.array(future_velocities)
    return future_positions,future_velocities


# Initialize the Kalman Filter

# Plotting
plt.figure(figsize=(10, 6))
plt.scatter(measurements[:, 0], measurements[:, 1], label='Measurements', color='r')
plt.plot(predict_future_positions_kalman(measurement=measurements)[0][:, 0], predict_future_positions_kalman(measurement=measurements)[0][:, 1], label='Predicted Future Positions', color='g')
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Kalman Filter Future Position Prediction')
plt.legend()
plt.grid()
plt.show()