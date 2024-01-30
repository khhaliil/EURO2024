import os


def print_directory_tree(startpath, excluded_extensions=(".png",".jpg", ".xml")):
    for root, dirs, files in os.walk(startpath):
        level = root.replace(startpath, '').count(os.sep)
        indent = ' ' * 4 * (level)
        print(f"{indent}{os.path.basename(root)}/")
        subindent = ' ' * 4 * (level + 1)
        for f in files:
            if not f.endswith(excluded_extensions):
                print(f"{subindent}{f}")


# Replace 'your_directory_path' with your directory path
print_directory_tree(r"C:\Users\MSI\Desktop\EURO2024")
