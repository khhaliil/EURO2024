# EURO2024
# Vision Repository for Eurobot Robotics Competition

## Overview
Welcome to the "Vision" repository, a pivotal component of our larger project tailored for the Eurobot Robotics Competition. This repository is dedicated to advancing the fields of computer vision and robotics, encompassing data management, model development, and real-time detection and calibration. Dive into our structured and well-documented codebase to explore innovative solutions in robotics!

### 🌟 Table of Contents
1. [Data](#1-data---data-and-annotations)
2. [Main](#2-main---core-application-code)
3. [OpenMv Try](#3-openmv-try---camera-experiments)
4. [Detection and Distance Calibration](#4-detection-and-distance-calibration)
5. [Additional Files](#5-additional-files)
6. [Installation and Usage](#6-installation-and-usage)
7. [Contributing](#7-contributing)
8. [License](#8-license)
9. [Acknowledgements](#9-acknowledgements)

### 📁 Repository Structure

#### 1. Data - Data and Annotations
This folder is the heart of our data collection, containing rich datasets and meticulously annotated information crucial for model training.
- **data and annotations**: Packed with datasets and corresponding YOLO annotations.
  - [Task Flower Pots v1.1](./Data/data%20and%20annotations/task_flower_potsv1.1_annot_annotations_2024_01_28_17_08_46_yolo%201.1)
  - [Task Flower Pots v1](./Data/data%20and%20annotations/task_flower_potsv1_annot-2024_01_18_18_30_23-yolo%201.1)
- **models**: Various model iterations and backups.
  - [Model V0](./Data/models/Model%20V0)
  - [Model v1 - Backup](./Data/models/Model%20v1%20-%20Backup%20before%20changes)
  - [Model v1](./Data/models/Model%20v1)
  - [Model v1.1](./Data/models/Modelv1.1)
  - [Weights](./Data/models/weights)
    -- these are the various weights ive trained , trying Nano, medium and large models.
- [Find a Missing Label Script](./Data/find%20a%20missing%20label.py)
    -- this is code for finding missing labels in the data 

#### 2. Main - Core Application Code
The Main folder contains the primary codebase, implementing various functionalities of our project.
- [Kalman Filter](./Main/Kalman.py)
- [Model Definition](./Main/Model.py)
- [Detect Aruco](./Main/detectAruco.py)
- [Main Application](./Main/main.py)
- [Data Saving Utility](./Main/save_data.py)
- [Test Model with Images](./Main/test_model_image.py)

#### 3. OpenMv Try - Camera Experiments
Explorations with the OpenMV camera, focusing on panel orientation detection.
- **Data_images**: Image datasets for OpenMV camera trials.
  - [Data Sc](./OpenMv%20try/Data_images/Data%20Sc)
  - [Flower and Pots Model](./OpenMv%20try/Data_images/Flower%20and%20pots%20Model)
- [Classifying Panneau](./OpenMv%20try/classifying%20panneau)

#### 4. Detection and Distance Calibration
A dedicated section for Aruco marker detection and calibrating distance measurements.
- [Aruco Detection Scripts](./detection%20and%20distance%20and%20calibration/Aruco%20detection)
- [Calibration Scripts](./detection%20and%20distance%20and%20calibration/calibration)
- [Distance Measurement](./detection%20and%20distance%20and%20calibration/distance.py)

#### 5. Additional Files
- [README.md](./README.md)
- [Initialization File](./__init__.py)
- [Dependencies](./requirements.txt)
- [Model Demonstration Video](./testmodelv1.mp4)

## 6. Installation and Usage
Detailed instructions on setting up the project, installing dependencies, and guidelines for usage.

## 7. Contributing
Guidelines for those who wish to contribute to this project. Let's collaborate to push the boundaries of robotics and computer vision!

## 8. License
Information about the licensing of this project, ensuring open and ethical use of our work.

## 9. Acknowledgements
A special thanks section to acknowledge contributors and supporters of this project.

