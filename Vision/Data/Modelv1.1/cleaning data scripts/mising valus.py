import os
import shutil

# Set the base path
base_path = "C:/Users/MSI/Desktop/EURO2024/Vision/Data/Modelv1.1"
images_train_path = os.path.join(base_path, "images/train")
labels_train_path = os.path.join(base_path, "labels/train")
fail_path = os.path.join(base_path, "fail")

# Create fail directory if it doesn't exist
os.makedirs(fail_path, exist_ok=True)

# Iterate over all images in images/train
for image_filename in os.listdir(images_train_path):
    if image_filename.endswith('.jpg'):
        # Construct the expected label filename
        label_filename = image_filename.replace('.jpg', '.txt')
        label_file_path = os.path.join(labels_train_path, label_filename)

        # Check if the label file exists and is not empty
        if not os.path.exists(label_file_path) or os.stat(label_file_path).st_size == 0:
            # Move the image to the fail directory
            image_file_path = os.path.join(images_train_path, image_filename)
            fail_file_path = os.path.join(fail_path, image_filename)
            shutil.move(image_file_path, fail_file_path)

print("Verification complete. Images with missing or empty labels have been moved to the fail directory.")
