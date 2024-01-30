import os 
import numpy as np 

def load_homography_matrix(path):
    try:
        with np.load(path) as data:
            return data['homography_matrix']
    except KeyError:
        print(f"'homography_matrix' not found in {path}")
        return None
    except IOError:
        print(f"Could not read file: {path}")
        return None
    
print(load_homography_matrix(r"C:\Users\MSI\Desktop\EURO2024\Tools\homography_matrix.npz"))
