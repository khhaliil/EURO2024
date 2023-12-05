#!/usr/bin/env python3

import rospy
import can
import struct
from ros_can_interface.msg import lidar_stopSignal

def stopSignalCallback(msg):
    if msg.stopSignalState == True:
        #declare a 64bit integer
        stopSignal = 0xFFFFFFFFFFFFFFFF
            
        # Convert the 64-bit integer to bytes
        data_bytes = struct.pack('>Q', stopSignal)
            
        # Create a CAN message object
        message_obj = can.Message(arbitration_id=0x000, data=list(data_bytes[:8]), is_extended_id=False)
            
        # Send the CAN message
        bus.send(message_obj)
            
        # Log the data for demonstration purposes
        rospy.loginfo("Transmitted Stop Signal.")
    
def main():
    global bus  # Declare bus as a global variable
    
    # Initialize the CAN bus
    bus = can.interface.Bus(channel='can0', bustype='socketcan')  # socketcan_native
    
    # Initialize ROS node
    rospy.init_node('can_sendStopSignal', anonymous=True)
    
    rospy.loginfo("can_sendStopSignal has benn started.")
    
    # Subscribe to the /stopSignal topic
    rospy.Subscriber('/ros_can_interface/stopSignal', lidar_stopSignal, stopSignalCallback)

    # Spin to keep the script from exiting
    rospy.spin()

if __name__ == '__main__':
    main()
