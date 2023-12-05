#!/usr/bin/env python3

import rospy
from jack_signal.msg import jack_msg
global jack

def callback(msg):
    rospy.loginfo("Received jack state: %s", msg.jack_state)
    jack=msg.jack_state
    #rospy.loginfo("Received jack : %s", jack)
    rospy.set_param('jack', jack)

def jack_subscriber():
    rospy.init_node('jack_subscriber', anonymous=True)
    rospy.Subscriber('jack_topic', jack_msg, callback)  # Use the message class
    rospy.spin()

if __name__ == '__main__':
    try:
        jack_subscriber()
    except rospy.ROSInterruptException:
        pass
