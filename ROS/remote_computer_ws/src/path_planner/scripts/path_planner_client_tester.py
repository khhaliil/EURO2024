#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Pose2D
from path_planner.srv import PathPlan, PathPlanRequest

def test_path_planner():
    # Initialize ROS node
    rospy.init_node('path_planner_client')

    # Create service client
    path_planning_client = rospy.ServiceProxy('path_planner/path_planning', PathPlan)

    # Define current pose, target point, and obstacle position
    current_pose = Pose2D()
    current_pose.x = 1.0
    current_pose.y = 2.0
    current_pose.theta = 0.0

    target_point = Pose2D()
    target_point.x = 5.0
    target_point.y = 4.0

    obstacle_point = Pose2D()
    obstacle_point.x = 3.0
    obstacle_point.y = 3.5

    # Create service request
    req = PathPlanRequest()
    req.current_pose = current_pose
    req.target_point = target_point
    req.obstacle = obstacle_point

    # Send request and wait for response
    rospy.loginfo("Sending path planning request...")
    try:
        response = path_planning_client(req)
    except rospy.ServiceException as e:
        rospy.logerr("Service call failed: %s", e)
        return

    # Check if path planning successful
    new_path = response.new_path  # Access the correct field
    if new_path:
        rospy.loginfo("Path planning successful!")
        
        # Print the new path
        print("New Path:")
        for i, pose in enumerate(new_path):
            print(f"Point {i+1}: x={pose.x}, y={pose.y}, theta={pose.theta}")
    else:
        rospy.logerr("Path planning failed")

if __name__ == "__main__":
    test_path_planner()
