#!/usr/bin/env python3

import rospy
from ros_can_interface.msg import master_navigationMessage
from ros_can_interface.msg import master_acknowledgSignal
from ros_can_interface.msg import lidar_stopSignal

def talker():
    # Initialize ROS node
    rospy.init_node('master_talker', anonymous=True)

    rospy.loginfo("master_talker node has been started.")

    # Create publishers for the topics that can_sendMessage subscribes to
    nav_pub = rospy.Publisher('/ros_can_interface/navigation_data', master_navigationMessage, queue_size=10)
    ack_pub = rospy.Publisher('/ros_can_interface/master_acknowledge', master_acknowledgSignal, queue_size=10)
    stop_pub = rospy.Publisher('/ros_can_interface/stopSignal', lidar_stopSignal, queue_size=10)

    # Rate at which to publish messages (adjust as needed)
    rate = rospy.Rate(1)

    while not rospy.is_shutdown():
        # Ask the user for the type of message
        message_type = input("Enter message type (nav/ack/stop): ").lower()

        if message_type == 'nav':
            # Create a sample navigation message
            nav_msg = master_navigationMessage()
            nav_msg.nav_targetX = float(input("Enter targetX: "))
            nav_msg.nav_targetY = float(input("Enter targetY: "))
            nav_msg.nav_targetAngle = float(input("Enter targetAngle: "))
            nav_msg.nav_isForward = input("Is it forward? (True/False): ").lower() == 'true'

            # Publish the navigation message
            nav_pub.publish(nav_msg)

            rospy.loginfo("Published Navigation Data: targetX: %f, targetY: %f, targetAngle: %f",
                          nav_msg.nav_targetX, nav_msg.nav_targetY, nav_msg.nav_targetAngle)

        elif message_type == 'ack':
            # Create an acknowledgment signal message
            ack_msg = master_acknowledgSignal()
            ack_msg.master_acknowledgeSignal = True

            # Publish the acknowledgment signal message
            ack_pub.publish(ack_msg)

            rospy.loginfo("Published Acknowledgment Signal: %s", str(ack_msg.master_acknowledgeSignal))

        elif message_type == 'stop':
            # Create a lidar stop signal message
            stop_msg = lidar_stopSignal()
            stop_msg.stopSignalState = True

            # Publish the lidar stop signal message
            stop_pub.publish(stop_msg)

            rospy.loginfo("Published Lidar Stop Signal: %s", str(stop_msg.stopSignalState))

        else:
            rospy.logwarn("Invalid message type. Please enter 'nav', 'ack', or 'stop'.")

        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
