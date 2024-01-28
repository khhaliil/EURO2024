import cv2
import Model
from Model import process_and_visualize_image
from Model import perform_detection
from Model import process_centers
from Model import update_centers_and_obstacles
from Model import draw_centers_and_obstacles
# Initialize YOLO model
yolo_model = Model.initialize_yolo(r"C:\Users\MSI\Desktop\EURO2024\Vision\Data\Modelv1.1\runs\detect\train11\weights\best.pt")

# Load an image from the folder
# Replace with the path to your image
image_path = r"C:\Users\MSI\Desktop\EURO2024\Vision\Data\Modelv1.1\images\val\top_down_1705318849.jpg"
image = cv2.imread(image_path)

# Check if the image was loaded correctly
if image is None:
    print("Error: Image could not be loaded.")
    exit(1)

# Perform detection on the image
centers= perform_detection(yolo_model,image,0.970)

obs=process_centers(centers=centers,radius_threshold=30,min_cluster_size=4)
centers,obs = update_centers_and_obstacles(centers=centers,obstacles=obs)

image,centers,obs=draw_centers_and_obstacles(image=image,centers=centers,obstacles=obs) 
# print(obs) 
# print("centers:")
#print(centers)
                    

#image,centers,obs = process_and_visualize_image(image,yolo_model,0.971,10,3)
cv2.imshow("img",image)
#print(centers,obs)

# Display the image
cv2.waitKey(0)
cv2.destroyAllWindows()
