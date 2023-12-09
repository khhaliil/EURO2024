#!/usr/bin/env python3

import rospy
import can
import struct
from ros_can_interface.msg import master_navigationMessage

# Declare bus as a global variable
bus = None

def encode_navigationMessage(msg):
    nav_targetX_bits = int(msg.nav_targetX * 100) & 0x7FFFF  # 19 bits
    nav_targetY_bits = int(msg.nav_targetY * 100) & 0x3FFFF  # 18 bits
    nav_targetAngle_bits = int(msg.nav_targetAngle * 100) & 0xFFFF  # 16 bits
    nav_isForward_bits = int(msg.nav_isForward) & 0x1  # 1 bit (bool)

    combined_value = (
        (nav_targetX_bits << 45)
        | (nav_targetY_bits << 27)
        | (nav_targetAngle_bits << 11)
        | (nav_isForward_bits << 10)
    )
    
    return combined_value

def navigationMessageCallback(msg): 
      
    #encode the message into a 64bit integer
    encoded_message = encode_navigationMessage(msg)
    
    # Convert the 64-bit integer to bytes
    data_bytes = struct.pack('>Q', encoded_message)
    
    # Create a CAN message object
    message_obj = can.Message(arbitration_id=0x002, data=list(data_bytes[:8]), is_extended_id=False)
    
    # Send the CAN message
    bus.send(message_obj)   
    
    # Log the data for demonstration purposes
    rospy.loginfo("Transmitted Navigation Data from Master: targetX: %f, targetY: %f, targetAngle: %f,",
                  msg.nav_targetX, msg.nav_targetY, msg.nav_targetAngle)
        

def main():
    global bus  # Declare bus as a global variable
    
    # Initialize the CAN bus
    bus = can.interface.Bus(channel='can0', bustype='socketcan')  # socketcan_native
    
    # Initialize ROS node
    rospy.init_node('can_sendMessage', anonymous=True)
    
    rospy.loginfo("can_sendMessage node has been started.")

    # Subscribe to the /navigation_data topic
    rospy.Subscriber('/ros_can_interface/navigation_data', master_navigationMessage, navigationMessageCallback)
        
    # Spin to keep the script from exiting
    rospy.spin()

if __name__ == '__main__':
    main()
