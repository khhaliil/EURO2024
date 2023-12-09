import cv2 as cv
import os
import time

CHESS_BOARD_DIM = (7, 4)

n = 0  # Image counter

# Directory to save images
image_dir_path = r"C:\Users\MSI\Desktop\EURO2024\Vision\calibration\calib_images_Xiaomi_0.5"
if not os.path.isdir(image_dir_path):
    os.makedirs(image_dir_path)
    print(f'"{image_dir_path}" Directory is created')
else:
    print(f'"{image_dir_path}" Directory already Exists.')

criteria = (cv.TERM_CRITERIA_EPS + cv.TERM_CRITERIA_MAX_ITER, 30, 0.001)

# Function to detect the chessboard
def detect_checker_board(image, grayImage, criteria, boardDimension):
    ret, corners = cv.findChessboardCorners(grayImage, boardDimension)
    if ret:
        corners1 = cv.cornerSubPix(grayImage, corners, (3, 3), (-1, -1), criteria)
        image = cv.drawChessboardCorners(image, boardDimension, corners1, ret)
    return image, ret

# Replace with the path to your video file
video_path = r"C:\Users\MSI\Desktop\VID_20231208_193212.mp4"

cap = cv.VideoCapture(video_path)

last_capture_time = time.time()
capture_interval = 1 # Interval in seconds

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break

    gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    image, board_detected = detect_checker_board(frame, gray, criteria, CHESS_BOARD_DIM)

    if (time.time() - last_capture_time > capture_interval) and board_detected:
        image_path = f"{image_dir_path}/image{n}.png"
        cv.imwrite(image_path, frame)
        print(f"Saved image number {n} at {image_path}")
        n += 1
        last_capture_time = time.time()

    cv.imshow("Chessboard Detection", image)
    if cv.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv.destroyAllWindows()

print(f"Total saved Images: {n}")
