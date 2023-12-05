#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Pose2D
from path_planner.srv import PathPlan, PathPlanResponse

def handle_path_planning(req):
    # Extract parameters from the service request
    current_pose = req.current_pose
    target_point = req.target_point
    obstacle_point = req.obstacle
    
    # Implement your path planning algorithm here
    # For simplicity, let's assume a straight line path with one intermediate point
    intermediate_point = Pose2D()
    intermediate_point.x = (current_pose.x + target_point.x + obstacle_point.x) / 2.0
    intermediate_point.y = (current_pose.y + target_point.y + obstacle_point.y) / 2.0

    # Return the planned path    
    return PathPlanResponse([current_pose, intermediate_point, target_point])

def path_planner_server():
    rospy.init_node('path_planner_server')
    service = rospy.Service('path_planner/path_planning', PathPlan, handle_path_planning)
    rospy.loginfo("Path Planner Server has been started.")
    rospy.spin()

if __name__ == "__main__":
    path_planner_server()
