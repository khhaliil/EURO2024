import serial
import cv2
import numpy as np

# Set up the serial connection (adjust the COM port as needed)
print("Setting up serial connection...")
ser = serial.Serial('COM14', baudrate=115200, timeout=1)

# Load the predefined dictionary for ArUco tags
print("Loading ArUco dictionary...")
dictionary = cv2.aruco.Dictionary(cv2.aruco.DICT_4X4_50,300)
parameters = cv2.aruco.DetectorParameters()

print("Entering main loop. Waiting for images...")
while True:
    if ser.in_waiting > 0:
        print("Reading data from the serial port...")
        data = ser.read_all()  # Read all data in the buffer

        # Convert to a numpy array
        nparr = np.frombuffer(data, np.uint8)

        # Decode the image
        img = cv2.imdecode(nparr, cv2.IMREAD_COLOR)

        if img is not None:
            print("Displaying received image...")
            cv2.imshow('Received Image', img)

            print("Detecting ArUco markers...")
            # Detect ArUco markers in the image
            corners, ids, rejectedImgPoints = cv2.aruco.detectMarkers(img, dictionary, parameters=parameters)

            # If markers are detected
            if ids is not None:
                print(f"Detected ArUco markers: {ids}")
                # Draw the detected markers
                cv2.aruco.drawDetectedMarkers(img, corners, ids)

            # Display the image with detected ArUco markers
            cv2.imshow('OpenMV - ArUco Detection', img)

        # Break the loop and close the window on pressing 'q'
        if cv2.waitKey(1) & 0xFF == ord('q'):
            print("Exiting...")
            break

# Close the serial connection and destroy all OpenCV windows
print("Closing serial connection and destroying all windows...")
ser.close()
cv2.destroyAllWindows()
