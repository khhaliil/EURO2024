import cv2
import Model

# Initialize YOLO model
yolo_model = Model.initialize_yolo(r"C:\Users\MSI\Desktop\EURO2024\Vision\Data\Model V0\runs\detect\train6\weights\best.pt")

# Load an image from the folder
image_path = r"C:\Users\MSI\Desktop\EURO2024\Vision\Data\Model V0\images\train\top_down_1705318679.jpg"  # Replace with the path to your image
image = cv2.imread(image_path)

# Check if the image was loaded correctly
if image is None:
    print("Error: Image could not be loaded.")
    exit(1)

# Perform detection on the image
centers=Model.perform_detection(yolo_model, image)
print("Centers returned:", centers)

# Display the image
cv2.imshow("Detection", image)
cv2.waitKey(0)
cv2.destroyAllWindows()
