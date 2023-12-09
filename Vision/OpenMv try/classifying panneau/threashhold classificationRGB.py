import sensor, image, time

# Set up the sensor
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)

# Define the color thresholds for yellow in RGB space
yellow_thresholds = (247, 181, 0)
blue_thresholds=(0, 91, 140)

# Define a margin of error for color detection
# This allows for some variation in the color
color_tolerance = 82
yellow_pixels=[]

while(True):
    img = sensor.snapshot()

    # Find pixels that match the yellow color within some tolerance
    for x in range(0,img.width()/2):
        for y in range(0,img.height(),2):
            pixel = img.get_pixel(x, y)
            if (abs(pixel[0] - yellow_thresholds[0]) < color_tolerance and
                abs(pixel[1] - yellow_thresholds[1]) < color_tolerance and
                abs(pixel[2] - yellow_thresholds[2]) < color_tolerance):
                # This pixel is yellow
                img.draw_circle(x, y, 2, color=(255, 0, 0))
                yellow_pixels.append(pixel)



    if (len(yellow_pixels)> 5):
        print("yellow on left")

    if (len(yellow_pixels) == 0) :
        print("blue on left")

    yellow_pixels=[]



    # Output the image to the IDE
    img.compress(quality=5) # Compress the image to reduce transmission size
