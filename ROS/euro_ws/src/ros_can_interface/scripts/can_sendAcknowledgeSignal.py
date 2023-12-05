#!/usr/bin/env python3

import rospy
import can
import struct
from ros_can_interface.msg import master_acknowledgSignal

def acknowledgeMessageCallbaack(msg):
    if msg.master_acknowledgeSignal == True:
        #declare a 64bit integer
        acknowledgeSignal = 0xFFFFFFFFFFFFFFFF
            
        # Convert the 64-bit integer to bytes
        data_bytes = struct.pack('>Q', acknowledgeSignal)
            
        # Create a CAN message object
        message_obj = can.Message(arbitration_id=0x001, data=list(data_bytes[:8]), is_extended_id=False)
            
        # Send the CAN message
        bus.send(message_obj)
            
        # Log the data for demonstration purposes
        rospy.loginfo("Transmitted Acknowledge Signal.")
    
def main():
    global bus  # Declare bus as a global variable
    
    # Initialize the CAN bus
    bus = can.interface.Bus(channel='can0', bustype='socketcan')  # socketcan_native
    
    # Initialize ROS node
    rospy.init_node('can_sendAcknowledgeSignal', anonymous=True)
    
    rospy.loginfo("can_sendAcknowledgeSignal has been started.")
    
    # Subscribe to the /stopSignal topic
    rospy.Subscriber('/ros_can_interface/master_acknowledge', master_acknowledgSignal, acknowledgeMessageCallbaack)

    # Spin to keep the script from exiting
    rospy.spin()

if __name__ == '__main__':
    main()
