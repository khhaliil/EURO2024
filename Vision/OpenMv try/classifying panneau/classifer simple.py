import sensor, image, time

# Set up the sensor
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)

# Define the color thresholds for yellow in HSV space
# These thresholds are just an example and will likely need to be tuned for your environment
yellow_thresholds = (44, 100, 48 ,44, 100, 97) # H, S, V min and max for yellow

while(True):
    img = sensor.snapshot()

    # Convert the image to HSV,
    img_hsv = img.to_grayscale().to_rainbow()

    # Find blobs that match the yellow color
    blobs = img.find_blobs([yellow_thresholds], pixels_threshold=100, area_threshold=100, merge=True)

    # If blobs are found, determine their position
    for blob in blobs:
        # Print blob information
        print("Blob:", blob)
        print("Area:", blob.area())
        print("Density:", blob.density())
        print("Bounding box:", blob.rect())
        print("Center:", (blob.cx(), blob.cy()))

        # Draw a rectangle around the blob
        img.draw_rectangle(blob.rect())
        img.draw_cross(blob.cx(), blob.cy())

        # Check the position of the blob's center in the X direction
        if blob.cx() > (img.width() / 2):
            print("Yellow is on the right")
        else:
            print("Yellow is on the left")
