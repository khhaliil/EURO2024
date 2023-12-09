#!/usr/bin/env python3
import rospy
from sensor_msgs.msg import LaserScan
from std_msgs.msg import Float64
from std_msgs.msg import Bool

import math
from math import sin
from math import cos

ObstacleDetected = False  # Change variable name to match topic name


def scan_callback(scan_data):

    global ObstacleDetected
    global nav_currentY
    global nav_currentX
    nav_currentX = 1
    nav_currentY = 1
    #nav_currentX=rospy.get_param('nav_currentX')
    #nav_currentY=rospy.get_param('nav_currentY')
    N = round(scan_data.scan_time / scan_data.time_increment)
    min_value, min_index = min_range_index(scan_data.ranges, N)

    
    angle= (math.degrees (min_index*scan_data.angle_increment)-5)

    ClosestObstacle_X_LIDAR=min_value*cos(angle*math.pi/180)
    ClosestObstacle_Y_LIDAR=min_value*sin(angle*math.pi/180)


    # Calculate obstacle coordinates in map frame
    Teta_map = 0
    ClosestObstacle_X_Map=(ClosestObstacle_X_LIDAR*cos(Teta_map*math.pi/180)) + (-ClosestObstacle_Y_LIDAR*sin(Teta_map*math.pi/180))+nav_currentX
    ClosestObstacle_Y_Map= ClosestObstacle_X_LIDAR*sin(Teta_map*math.pi/180)  + ClosestObstacle_Y_LIDAR*cos(Teta_map*math.pi/180)+nav_currentY
    print("ClosestObstacle_X_LIDAR", ClosestObstacle_X_Map)
    print("ClosestObstacle_y_LIDAR", ClosestObstacle_Y_Map)

    if (min_value < 0.3) and ( 0 < ClosestObstacle_X_Map < 3) and (0 < ClosestObstacle_Y_Map < 2):
        ObstacleDetected = True
        rospy.loginfo(ObstacleDetected)
        pub.publish(ObstacleDetected)
    else:
        ObstacleDetected = False
        rospy.loginfo(ObstacleDetected)
        pub.publish(ObstacleDetected)
    rospy.set_param('ClosestObstacle_X_Map', ClosestObstacle_X_Map)
    rospy.set_param('ClosestObstacle_Y_Map', ClosestObstacle_Y_Map)
    rospy.set_param('obstacle', ObstacleDetected)
def min_range_index(ranges, count):
    i = 0
    index_min = 0
    global min
    while ranges[i] == 0.0:
        i = i + 1

    min = ranges[i]
    index_min = i

    for j in range(i + 1, count - 2):
        if ranges[j] < min and ranges[j] != 0.0:
            min = ranges[j]
            index_min = j

    return min, index_min


def round(float):
    if ((float - int(float)) > 0.5):
        return (int(float) + 1)
    else:
        return int(float)


if __name__ == '__main__':
    rospy.init_node('scan_node', anonymous=True)
    rospy.Subscriber("/scan", LaserScan, scan_callback)  # Use a more relevant topic
    pub = rospy.Publisher("/obstacle_detected", Bool, queue_size=10)
    rospy.spin()
