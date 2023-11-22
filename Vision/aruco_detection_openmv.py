# Untitled - By: MSI - Sat Nov 18 2023

import sensor, image, time, math

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
#golable
c1=(255,0,0)
c2=(0,255,0)
c3=(255,255,0)
textScale= 1
text_color=c1
rect_color=c2
cross_color=c3
numberOfTags=6
tagNames= ["top","left","Bottom","right","Front","Back"]

tagFamilies= 1
tagFamilies |= image.TAG36H11

clock = time.clock()

while(True):

    clock.tick()
    img = sensor.snapshot()
    print(clock.fps())
    for tag in img.find_apriltags():
        img.draw_rectangle(tag.rect(),color=rect_color)
        img.draw_cross(tag.cx(),tag.cy(),color=cross_color)
        for i in range(0,numberOfTags,1):
            if tag.id() == i :
                img.draw_string(10,90,tagNames[i]+" side",
                                color=text_color,
                                scale=TextScale,mono_space=False)
                img.draw_string(10,100,"angle: "+str(int((180*tag.rotation())/math.pi)),
                                color=text_color,
                                scale=textScale,mono_space=False)
