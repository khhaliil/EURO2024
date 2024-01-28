from ultralytics import YOLO

# Load a model
model = YOLO("yolov8n.yaml")  # build a new model from scratch

################################## for retrainnig !!!! ##############################

#model = YOLO("yolov8n.pt")  # load a pretrained model (recommended for training)
    
# Use the model
model.train(data=r"C:\Users\MSI\Desktop\EURO2024\Vision\Data\Modelv1.1\config.yaml", epochs=70)  # train the model
