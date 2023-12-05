#!/usr/bin/env python3

import rospy
import can
import os

def can_init():
    # Initialize the node with a name
    rospy.init_node('can_init')
    
    rospy.loginfo("can_init node has started.")
    
    # Configure the CAN interface
    os.system('sudo ip link set can0 type can bitrate 500000 restart-ms 100')
    os.system('sudo ip link set up can0')

    rospy.loginfo("CAN Peripheral has been successfully started.")

if __name__ == '__main__':
    can_init()
    