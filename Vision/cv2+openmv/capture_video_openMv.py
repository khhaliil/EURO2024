# OpenMV Camera Script
import sensor, image, time, pyb

sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)  # Set pixel format to RGB565
sensor.set_framesize(sensor.QVGA)     # Set frame size to VGA (640x480)
sensor.skip_frames(time = 2000)      # Wait for settings to take effect

# Initialize the USB Virtual COM Port (VCP)

print("hello")
while(True):
    usb = pyb.USB_VCP()
    usb.init(flow=-1)
    img = sensor.snapshot()         # Take a picture
    usb.send(img.compress(quality=70),timeout=10) # Send the image over USB. Adjust quality as needed
    print(usb.isconnected())
    print(usb.any())
    usb.close()
    time.sleep(20)                # Delay to prevent buffer overflow
