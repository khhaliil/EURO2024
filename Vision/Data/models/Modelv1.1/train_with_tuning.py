from ultralytics import YOLO

# Load your model
model = YOLO("yolov8n.yaml")  # For a new model
# model = YOLO("yolov8n.pt")  # For a pre-trained model

# Define the hyperparameter search space (if you want to customize it)
# space = {
#     "lr0": tune.uniform(1e-5, 1e-1),
#     ... # other hyperparameters
# }

# Run hyperparameter tuning
result_grid = model.tune(
    use_ray=True,
    max_samples=10,  # The number of different hyperparameter combinations to try
    # Replace with your data config file path
    data=r"C:\Users\MSI\Desktop\EURO2024\Vision\Data\Modelv1.1\config.yaml",
    epochs=10  # Number of epochs for training
    # space=space, # Uncomment if you defined a custom search space
)

# The best hyperparameters are now stored in result_grid
# You can inspect the result_grid to find the best hyperparameters

# Now train your model with the best hyperparameters
best_hyperparameters = result_grid.get_best_result().config
model.train(
    data=r"C:\Users\MSI\Desktop\EURO2024\Vision\Data\Modelv1.1\config.yaml",
    epochs=10,
    **best_hyperparameters  # Use the best hyperparameters found
)
