import os

# Set the paths to your images and labels directories
images_dir = r"C:\Users\MSI\Desktop\EURO2024\Vision\Data\Model V0\images\train"
labels_dir = r"C:\Users\MSI\Desktop\EURO2024\Vision\Data\Model V0\labels\train"

# List all the files in both directories
image_files = set(os.listdir(images_dir))
label_files = set(os.listdir(labels_dir))

# Convert label filenames to image filenames
# Assuming label files are like 'image1.txt' and image files are like 'image1.png'
label_images = {file.replace('.txt', '.jpg') for file in label_files}

# Find image files that don't have corresponding label files
unlabeled_images = image_files - label_images

# Delete these images
for file in unlabeled_images:
    file_path = os.path.join(images_dir, file)
    os.remove(file_path)
    print(f"Deleted {file_path}")

print("Cleanup complete.")
