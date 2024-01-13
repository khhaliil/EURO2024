import cv2
import time
from playsound import playsound  # Import playsound library

def save_frame(img, base_path=r'C:\Users\MSI\Desktop\EURO2024\Vision\Data\dataTest_withoutAruco', prefix='frame', interval=5, manual_save=False):
    """
    Save frames to a specified path at a given interval or manually.

    Args:
    - img: Image to be saved.
    - base_path: Base path where images will be saved.
    - prefix: Prefix for the image filenames.
    - interval: Time interval in seconds between automatic saves.
    - manual_save: Flag to trigger manual saving.
    """
    last_saved_time = getattr(save_frame, "last_saved_time", 0)
    current_time = time.time()

    if manual_save or (current_time - last_saved_time) >= interval:
        # Play the "bip bip" sound before saving
        playsound(r"C:\Users\MSI\Desktop\EURO2024\Tools\Censor beep sound effect.mp3")  # Change 'notification_sound.mp3' to the path of your audio file
        time.sleep(2)  # Sleep for 4 seconds before capturing
        filename = f"{prefix}_{int(current_time)}.jpg"
        cv2.imwrite(filename, img)
        save_frame.last_saved_time = current_time
        print(f"Saved: {filename}")
