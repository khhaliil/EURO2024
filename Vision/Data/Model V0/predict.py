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
bounding_boxes = result.boxes.data

# Define the detection threshold
threshold = 0.1

# Plot bounding boxes on the image
# Plot bounding boxes on the image
for box in bounding_boxes:
    # Convert the mapped values to a list before concatenating
    x1, y1, x2, y2, confidence = map(int, box[:5])
    class_id = int(box[5])

    if confidence >= threshold:
        cv2.rectangle(image, (x1, y1), (x2, y2), (0, 255, 0), 2)
        cv2.putText(image, f'{result.names[class_id]} {confidence:.2f}', (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)


# Display the image
cv2.imshow('Detection', image)
cv2.waitKey(0)
cv2.destroyAllWindows()
