#!/usr/bin/env python3

import rospy
import can
import struct
from ros_can_interface.msg import navigator_navigationMessage

bus = None
rate = None 

def decode_message(can_msg):

    # Combine the received bytes into a 64-bit integer
    combined_value = struct.unpack('<Q', bytes(can_msg))[0]

    # Decode the combined value back into the original variables
    nav_currentX = ((combined_value >> 45) & 0x7FFFF) * 0.01
    nav_currentY = ((combined_value >> 27) & 0x3FFFF) * 0.01
    nav_currentAngle = ((combined_value >> 11) & 0xFFFF) * 0.01
    nav_currentState = (combined_value >> 3) & 0xFF

    # Create a NavigationMessage object
    nav_msg = navigator_navigationMessage()
    nav_msg.nav_currentX = nav_currentX
    nav_msg.nav_currentY = nav_currentY
    nav_msg.nav_currentAngle = nav_currentAngle
    nav_msg.nav_currentState = nav_currentState

    return nav_msg

def can_startReceiveMessage():
    # Initialize ROS node
    rospy.init_node('can_receiveMessage', anonymous=True)
    
    rate = rospy.Rate(200)  # Set the rate for the ROS node

    # Create a publisher for the /received_navigation_data topic
    navigationMessage_pub = rospy.Publisher('ros_can_interface/received_navigation_data', navigator_navigationMessage, queue_size=10)
    
    # Main loop to receive and publish CAN messages
    while not rospy.is_shutdown():
        try:
            can_msg = bus.recv(1)  # Adjust the timeout as needed
            
            if (can_msg is not None) and (can_msg.arbitration_id == 0x003):
                
                decoded_message = decode_message(can_msg)
                
                #navigationMessage_pub.publish(decoded_message)
                nav_currentX=decoded_message.nav_currentX
                nav_currentY=decoded_message.nav_currentY
                nav_currentAngle=decoded_message.nav_currentAngle
                nav_currentState=decoded_message.nav_currentState
                
                rospy.set_param('nav_currentX', nav_currentX)
                rospy.set_param('nav_currentY', nav_currentY)
                rospy.set_param('nav_currentAngle', nav_currentAngle)
                rospy.set_param('nav_currentState', nav_currentState)
                
                rospy.loginfo("Received CAN Message: Data: currentX: %f, currentY: %f, currentAngle %f, currentState %d",
                              decoded_message.nav_currentX, decoded_message.nav_currentY,
                              decoded_message.nav_currentAngle, decoded_message.nav_currentState
                              )
        
        except can.CanError:
            rospy.logwarn("Error receiving CAN message")
        
        rate.sleep()

def main():
    # Initialize the CAN bus
    bus = can.interface.Bus(channel='can0', bustype='socketcan')  # socketcan_native
    
    # Start the CAN receiver node
    can_startReceiveMessage()

if __name__ == '__main__':
    main()
