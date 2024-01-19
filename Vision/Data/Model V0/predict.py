import cv2
from ultralytics import YOLO

# Load the trained YOLO model
model = YOLO("yolov8m.yaml")  # Adjust this to your model file

# Open a handle to the default camera
cap = cv2.VideoCapture(3)

# Check if the webcam is opened correctly
if not cap.isOpened():
    raise IOError("Cannot open webcam")

try:
    while True:
        ret, frame = cap.read()
        if not ret:
            break

        # Perform detection on the frame
        results = model.predict(frame)

        # Process results
        for result in results:
            for i in range(len(result.boxes)):
                box = result.boxes.data[i]
                x1, y1, x2, y2, confidence, class_id = map(int, box)
                cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
                label = f'{result.names[class_id]} {confidence:.2f}'
                cv2.putText(frame, label, (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

        # Display the resulting frame
        cv2.imshow('Frame', frame)

        # Break the loop with the 'q' key
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
finally:
    cap.release()
    cv2.destroyAllWindows()
