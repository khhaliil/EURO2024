#!/usr/bin/env python3
import rospy
import RPi.GPIO as GPIO
import time
from jack_signal.msg import jack_msg

def jack_publisher():
    pub = rospy.Publisher('jack_topic', jack_msg,queue_size=10)
    rospy.init_node('jack_publisher', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    msg=jack_msg()
    msg.jack_state=0
# Set up GPIO pins
    GPIO.setmode(GPIO.BCM)
    JACK_PIN = 6
    GPIO.setup(JACK_PIN, GPIO.IN,GPIO.PUD_UP)

# Set up edge detection
    GPIO.add_event_detect(JACK_PIN, GPIO.RISING,bouncetime=200)
    while not rospy.is_shutdown():
      if GPIO.event_detected(JACK_PIN):
         print("Rising edge detected!")
         msg.jack_state=1
         time.sleep(0.01)

      rospy.loginfo(msg.jack_state)
      pub.publish(msg.jack_state)
      rate.sleep()

if __name__ == '__main__':
    try:
        jack_publisher()
    except rospy.ROSInterruptException:
        pass
