import os


def process_file(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    with open(file_path, 'w') as file:
        for line in lines:
            if line.startswith('0'):
                file.write('1' + line[1:])
            elif line.startswith('1'):
                file.write('0' + line[1:])
            else:
                file.write(line)


def process_directory(directory):
    for filename in os.listdir(directory):
        if filename.endswith('.txt'):
            file_path = os.path.join(directory, filename)
            process_file(file_path)


# Set the base path to the labels directory
base_path = "C:/Users/MSI/Desktop/EURO2024/Vision/Data/Model v1/labels"

# Process the 'train' and 'test' subdirectories
train_path = os.path.join(base_path, 'train')
test_path = os.path.join(base_path, 'test')

process_directory(train_path)
process_directory(test_path)

print("Processing complete.")
