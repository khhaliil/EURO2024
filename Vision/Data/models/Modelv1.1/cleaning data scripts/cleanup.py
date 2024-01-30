import os
import shutil

# Set the path to your dataset
base_path = "C:/Users/MSI/Desktop/EURO2024/Vision/Data/Modelv1.1"
images_train_path = os.path.join(base_path, "images/train")
labels_train_path = os.path.join(base_path, "labels/train")
fail_path = os.path.join(base_path, "fail")

# Create fail directory if it doesn't exist
os.makedirs(fail_path, exist_ok=True)

# Get list of images and labels
images = {f.split('.')[0] for f in os.listdir(
    images_train_path) if f.endswith('.jpg')}
labels = {f.split('.')[0] for f in os.listdir(
    labels_train_path) if f.endswith('.txt')}

# Find images without labels and labels without images
images_without_labels = images - labels
labels_without_images = labels - images

# Move the unmatched files
for image in images_without_labels:
    src = os.path.join(images_train_path, image + '.jpg')
    dest = os.path.join(fail_path, image + '.jpg')
    shutil.move(src, dest)

for label in labels_without_images:
    src = os.path.join(labels_train_path, label + '.txt')
    dest = os.path.join(fail_path, label + '.txt')
    shutil.move(src, dest)

print(f"Moved {len(images_without_labels)} unmatched images and {len(labels_without_images)} unmatched labels to the fail folder.")
