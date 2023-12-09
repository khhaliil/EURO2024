;; Auto-generated. Do not edit!


(when (boundp 'path_planner::PathPlan)
  (if (not (find-package "PATH_PLANNER"))
    (make-package "PATH_PLANNER"))
  (shadow 'PathPlan (find-package "PATH_PLANNER")))
(unless (find-package "PATH_PLANNER::PATHPLAN")
  (make-package "PATH_PLANNER::PATHPLAN"))
(unless (find-package "PATH_PLANNER::PATHPLANREQUEST")
  (make-package "PATH_PLANNER::PATHPLANREQUEST"))
(unless (find-package "PATH_PLANNER::PATHPLANRESPONSE")
  (make-package "PATH_PLANNER::PATHPLANRESPONSE"))

(in-package "ROS")

(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass path_planner::PathPlanRequest
  :super ros::object
  :slots (_current_pose _target_point _obstacle ))

(defmethod path_planner::PathPlanRequest
  (:init
   (&key
    ((:current_pose __current_pose) (instance geometry_msgs::Pose2D :init))
    ((:target_point __target_point) (instance geometry_msgs::Pose2D :init))
    ((:obstacle __obstacle) (instance geometry_msgs::Pose2D :init))
    )
   (send-super :init)
   (setq _current_pose __current_pose)
   (setq _target_point __target_point)
   (setq _obstacle __obstacle)
   self)
  (:current_pose
   (&rest __current_pose)
   (if (keywordp (car __current_pose))
       (send* _current_pose __current_pose)
     (progn
       (if __current_pose (setq _current_pose (car __current_pose)))
       _current_pose)))
  (:target_point
   (&rest __target_point)
   (if (keywordp (car __target_point))
       (send* _target_point __target_point)
     (progn
       (if __target_point (setq _target_point (car __target_point)))
       _target_point)))
  (:obstacle
   (&rest __obstacle)
   (if (keywordp (car __obstacle))
       (send* _obstacle __obstacle)
     (progn
       (if __obstacle (setq _obstacle (car __obstacle)))
       _obstacle)))
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Pose2D _current_pose
    (send _current_pose :serialization-length)
    ;; geometry_msgs/Pose2D _target_point
    (send _target_point :serialization-length)
    ;; geometry_msgs/Pose2D _obstacle
    (send _obstacle :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Pose2D _current_pose
       (send _current_pose :serialize s)
     ;; geometry_msgs/Pose2D _target_point
       (send _target_point :serialize s)
     ;; geometry_msgs/Pose2D _obstacle
       (send _obstacle :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Pose2D _current_pose
     (send _current_pose :deserialize buf ptr-) (incf ptr- (send _current_pose :serialization-length))
   ;; geometry_msgs/Pose2D _target_point
     (send _target_point :deserialize buf ptr-) (incf ptr- (send _target_point :serialization-length))
   ;; geometry_msgs/Pose2D _obstacle
     (send _obstacle :deserialize buf ptr-) (incf ptr- (send _obstacle :serialization-length))
   ;;
   self)
  )

(defclass path_planner::PathPlanResponse
  :super ros::object
  :slots (_new_path ))

(defmethod path_planner::PathPlanResponse
  (:init
   (&key
    ((:new_path __new_path) ())
    )
   (send-super :init)
   (setq _new_path __new_path)
   self)
  (:new_path
   (&rest __new_path)
   (if (keywordp (car __new_path))
       (send* _new_path __new_path)
     (progn
       (if __new_path (setq _new_path (car __new_path)))
       _new_path)))
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Pose2D[] _new_path
    (apply #'+ (send-all _new_path :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Pose2D[] _new_path
     (write-long (length _new_path) s)
     (dolist (elem _new_path)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Pose2D[] _new_path
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _new_path (let (r) (dotimes (i n) (push (instance geometry_msgs::Pose2D :init) r)) r))
     (dolist (elem- _new_path)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(defclass path_planner::PathPlan
  :super ros::object
  :slots ())

(setf (get path_planner::PathPlan :md5sum-) "a9186ff1c0833e5c6cc2915c1b9610f7")
(setf (get path_planner::PathPlan :datatype-) "path_planner/PathPlan")
(setf (get path_planner::PathPlan :request) path_planner::PathPlanRequest)
(setf (get path_planner::PathPlan :response) path_planner::PathPlanResponse)

(defmethod path_planner::PathPlanRequest
  (:response () (instance path_planner::PathPlanResponse :init)))

(setf (get path_planner::PathPlanRequest :md5sum-) "a9186ff1c0833e5c6cc2915c1b9610f7")
(setf (get path_planner::PathPlanRequest :datatype-) "path_planner/PathPlanRequest")
(setf (get path_planner::PathPlanRequest :definition-)
      "# Current robot position and angle
geometry_msgs/Pose2D current_pose

# Target point
geometry_msgs/Pose2D target_point

# Presented obstacle position
geometry_msgs/Pose2D obstacle


================================================================================
MSG: geometry_msgs/Pose2D
# Deprecated
# Please use the full 3D pose.

# In general our recommendation is to use a full 3D representation of everything and for 2D specific applications make the appropriate projections into the plane for their calculations but optimally will preserve the 3D information during processing.

# If we have parallel copies of 2D datatypes every UI and other pipeline will end up needing to have dual interfaces to plot everything. And you will end up with not being able to use 3D tools for 2D use cases even if they're completely valid, as you'd have to reimplement it with different inputs and outputs. It's not particularly hard to plot the 2D pose or compute the yaw error for the Pose message and there are already tools and libraries that can do this for you.


# This expresses a position and orientation on a 2D manifold.

float64 x
float64 y
float64 theta
---

# Array of intermediate points for the new path
geometry_msgs/Pose2D[] new_path

================================================================================
MSG: geometry_msgs/Pose2D
# Deprecated
# Please use the full 3D pose.

# In general our recommendation is to use a full 3D representation of everything and for 2D specific applications make the appropriate projections into the plane for their calculations but optimally will preserve the 3D information during processing.

# If we have parallel copies of 2D datatypes every UI and other pipeline will end up needing to have dual interfaces to plot everything. And you will end up with not being able to use 3D tools for 2D use cases even if they're completely valid, as you'd have to reimplement it with different inputs and outputs. It's not particularly hard to plot the 2D pose or compute the yaw error for the Pose message and there are already tools and libraries that can do this for you.


# This expresses a position and orientation on a 2D manifold.

float64 x
float64 y
float64 theta
")

(setf (get path_planner::PathPlanResponse :md5sum-) "a9186ff1c0833e5c6cc2915c1b9610f7")
(setf (get path_planner::PathPlanResponse :datatype-) "path_planner/PathPlanResponse")
(setf (get path_planner::PathPlanResponse :definition-)
      "# Current robot position and angle
geometry_msgs/Pose2D current_pose

# Target point
geometry_msgs/Pose2D target_point

# Presented obstacle position
geometry_msgs/Pose2D obstacle


================================================================================
MSG: geometry_msgs/Pose2D
# Deprecated
# Please use the full 3D pose.

# In general our recommendation is to use a full 3D representation of everything and for 2D specific applications make the appropriate projections into the plane for their calculations but optimally will preserve the 3D information during processing.

# If we have parallel copies of 2D datatypes every UI and other pipeline will end up needing to have dual interfaces to plot everything. And you will end up with not being able to use 3D tools for 2D use cases even if they're completely valid, as you'd have to reimplement it with different inputs and outputs. It's not particularly hard to plot the 2D pose or compute the yaw error for the Pose message and there are already tools and libraries that can do this for you.


# This expresses a position and orientation on a 2D manifold.

float64 x
float64 y
float64 theta
---

# Array of intermediate points for the new path
geometry_msgs/Pose2D[] new_path

================================================================================
MSG: geometry_msgs/Pose2D
# Deprecated
# Please use the full 3D pose.

# In general our recommendation is to use a full 3D representation of everything and for 2D specific applications make the appropriate projections into the plane for their calculations but optimally will preserve the 3D information during processing.

# If we have parallel copies of 2D datatypes every UI and other pipeline will end up needing to have dual interfaces to plot everything. And you will end up with not being able to use 3D tools for 2D use cases even if they're completely valid, as you'd have to reimplement it with different inputs and outputs. It's not particularly hard to plot the 2D pose or compute the yaw error for the Pose message and there are already tools and libraries that can do this for you.


# This expresses a position and orientation on a 2D manifold.

float64 x
float64 y
float64 theta
")



(provide :path_planner/PathPlan "a9186ff1c0833e5c6cc2915c1b9610f7")


