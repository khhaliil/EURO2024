import os
import shutil

# Set the base path and label file name
base_path = "C:/Users/MSI/Desktop/EURO2024/Vision/Data"
label_file_name = "top_down_1705930691.txt"  # Name of the label file
found_folder = os.path.join(base_path, "found")

# Create the found folder if it doesn't exist
os.makedirs(found_folder, exist_ok=True)

# Remove the extension from the label file name to match with the image file
image_file_name = label_file_name.replace('.txt', '.jpg')

# Initialize a flag to indicate if the file was found
file_found = False

# Walk through all subdirectories to find the corresponding image file
for dirpath, dirnames, filenames in os.walk(base_path):
    if image_file_name in filenames:
        source_file = os.path.join(dirpath, image_file_name)
        destination_file = os.path.join(found_folder, image_file_name)
        shutil.copy(source_file, destination_file)
        file_found = True
        break

# Print the result
if file_found:
    print(f"Image file '{image_file_name}' copied to '{found_folder}'.")
else:
    print(f"Image file '{image_file_name}' not found in any subdirectory.")
