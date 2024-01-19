import os
import cv2
from ultralytics import YOLO

# Define the path for the model and the image
model_path = r"C:\Users\MSI\Desktop\EURO2024\Vision\Data\Model V0\runs\detect\train4\weights\best.pt"
image_path = r"C:\Users\MSI\Desktop\EURO2024\Vision\Data\Model V0\images\train\top_down_1705318679.jpg"

# Load the custom model
model = YOLO(model_path)

# Load the image
image = cv2.imread(image_path)

# Check if the image is loaded successfully
if image is None:
    print("Failed to load the image")
    exit(1)

# Perform detection
results = model(image)

# Access the first (and likely only) results object
result = results[0]

# Access the bounding boxes
bounding_boxes = result.boxes

# Define the detection threshold
conf_threshold = 0.7

# Process each detection
for i in range(len(bounding_boxes)):
    box = bounding_boxes.data[i]  # Access the bounding box data
    x1, y1, x2, y2, confidence, class_id = box
    x1, y1, x2, y2, class_id = map(int, [x1, y1, x2, y2, class_id])
    
    if confidence >= conf_threshold:
        # Draw bounding box and label on the image
        cv2.rectangle(image, (x1, y1), (x2, y2), (0, 255, 0), 2)
        label = f'{result.names[class_id]} {confidence:.2f}'
        cv2.putText(image, label, (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

# Display the image and wait until a key is pressed
cv2.imshow('Detection', image)
cv2.waitKey(0)  # Wait indefinitely for a key press
cv2.destroyAllWindows()
