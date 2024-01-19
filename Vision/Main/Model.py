# yolo_detection.py

import cv2
from ultralytics import YOLO

def initialize_yolo(model_path):
    # Load the YOLO model
    model = YOLO(model_path)
    return model

def perform_detection(model, image):
    # Perform object detection
    results = model.predict(image)

    # Process results and draw bounding boxes
    for result in results:
        for i in range(len(result.boxes)):
            box = result.boxes.data[i]
            # Convert only the bounding box coordinates to integers, not the confidence
            x1, y1, x2, y2 = map(int, box[:4])
            confidence, class_id = box[4], int(box[5])
            cv2.rectangle(image, (x1, y1), (x2, y2), (0, 255, 0), 1)
            label = f'{result.names[class_id]} {confidence:.2f}'  # Keep confidence as a float
            cv2.putText(image, label, (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
    return image
