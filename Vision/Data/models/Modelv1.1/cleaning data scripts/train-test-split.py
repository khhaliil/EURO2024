import os
import shutil
import random

# Set the path to your dataset
base_path = r"C:\Users\MSI\Desktop\EURO2024\Vision\Data\Modelv1.1"
images_train_path = os.path.join(base_path, "images/train")
labels_train_path = os.path.join(base_path, "labels/train")
images_test_path = os.path.join(base_path, "images/test")
labels_test_path = os.path.join(base_path, "labels/test")

# Create test directories if they don't exist
os.makedirs(images_test_path, exist_ok=True)
os.makedirs(labels_test_path, exist_ok=True)

# Get list of images
images = [f for f in os.listdir(images_train_path) if f.endswith('.jpg')]

# Randomly select 8% of the images
sample_size = int(len(images) * 0.09)
selected_images = random.sample(images, sample_size)

# Move the selected images and corresponding labels
for image in selected_images:
    label = image.replace('.jpg', '.txt')

    # Construct full file paths
    image_src = os.path.join(images_train_path, image)
    label_src = os.path.join(labels_train_path, label)
    image_dest = os.path.join(images_test_path, image)
    label_dest = os.path.join(labels_test_path, label)

    # Move files
    shutil.move(image_src, image_dest)
    shutil.move(label_src, label_dest)

print(
    f"Moved {sample_size} images and their corresponding labels to the test folders.")
