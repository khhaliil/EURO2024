; Auto-generated. Do not edit!


(cl:in-package path_planner-srv)


;//! \htmlinclude PathPlan-request.msg.html

(cl:defclass <PathPlan-request> (roslisp-msg-protocol:ros-message)
  ((current_pose
    :reader current_pose
    :initarg :current_pose
    :type geometry_msgs-msg:Pose2D
    :initform (cl:make-instance 'geometry_msgs-msg:Pose2D))
   (target_point
    :reader target_point
    :initarg :target_point
    :type geometry_msgs-msg:Pose2D
    :initform (cl:make-instance 'geometry_msgs-msg:Pose2D))
   (obstacle
    :reader obstacle
    :initarg :obstacle
    :type geometry_msgs-msg:Pose2D
    :initform (cl:make-instance 'geometry_msgs-msg:Pose2D)))
)

(cl:defclass PathPlan-request (<PathPlan-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PathPlan-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PathPlan-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name path_planner-srv:<PathPlan-request> is deprecated: use path_planner-srv:PathPlan-request instead.")))

(cl:ensure-generic-function 'current_pose-val :lambda-list '(m))
(cl:defmethod current_pose-val ((m <PathPlan-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader path_planner-srv:current_pose-val is deprecated.  Use path_planner-srv:current_pose instead.")
  (current_pose m))

(cl:ensure-generic-function 'target_point-val :lambda-list '(m))
(cl:defmethod target_point-val ((m <PathPlan-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader path_planner-srv:target_point-val is deprecated.  Use path_planner-srv:target_point instead.")
  (target_point m))

(cl:ensure-generic-function 'obstacle-val :lambda-list '(m))
(cl:defmethod obstacle-val ((m <PathPlan-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader path_planner-srv:obstacle-val is deprecated.  Use path_planner-srv:obstacle instead.")
  (obstacle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PathPlan-request>) ostream)
  "Serializes a message object of type '<PathPlan-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'current_pose) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'target_point) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'obstacle) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PathPlan-request>) istream)
  "Deserializes a message object of type '<PathPlan-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'current_pose) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'target_point) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'obstacle) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PathPlan-request>)))
  "Returns string type for a service object of type '<PathPlan-request>"
  "path_planner/PathPlanRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PathPlan-request)))
  "Returns string type for a service object of type 'PathPlan-request"
  "path_planner/PathPlanRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PathPlan-request>)))
  "Returns md5sum for a message object of type '<PathPlan-request>"
  "a9186ff1c0833e5c6cc2915c1b9610f7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PathPlan-request)))
  "Returns md5sum for a message object of type 'PathPlan-request"
  "a9186ff1c0833e5c6cc2915c1b9610f7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PathPlan-request>)))
  "Returns full string definition for message of type '<PathPlan-request>"
  (cl:format cl:nil "# Current robot position and angle~%geometry_msgs/Pose2D current_pose~%~%# Target point~%geometry_msgs/Pose2D target_point~%~%# Presented obstacle position~%geometry_msgs/Pose2D obstacle~%~%~%================================================================================~%MSG: geometry_msgs/Pose2D~%# Deprecated~%# Please use the full 3D pose.~%~%# In general our recommendation is to use a full 3D representation of everything and for 2D specific applications make the appropriate projections into the plane for their calculations but optimally will preserve the 3D information during processing.~%~%# If we have parallel copies of 2D datatypes every UI and other pipeline will end up needing to have dual interfaces to plot everything. And you will end up with not being able to use 3D tools for 2D use cases even if they're completely valid, as you'd have to reimplement it with different inputs and outputs. It's not particularly hard to plot the 2D pose or compute the yaw error for the Pose message and there are already tools and libraries that can do this for you.~%~%~%# This expresses a position and orientation on a 2D manifold.~%~%float64 x~%float64 y~%float64 theta~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PathPlan-request)))
  "Returns full string definition for message of type 'PathPlan-request"
  (cl:format cl:nil "# Current robot position and angle~%geometry_msgs/Pose2D current_pose~%~%# Target point~%geometry_msgs/Pose2D target_point~%~%# Presented obstacle position~%geometry_msgs/Pose2D obstacle~%~%~%================================================================================~%MSG: geometry_msgs/Pose2D~%# Deprecated~%# Please use the full 3D pose.~%~%# In general our recommendation is to use a full 3D representation of everything and for 2D specific applications make the appropriate projections into the plane for their calculations but optimally will preserve the 3D information during processing.~%~%# If we have parallel copies of 2D datatypes every UI and other pipeline will end up needing to have dual interfaces to plot everything. And you will end up with not being able to use 3D tools for 2D use cases even if they're completely valid, as you'd have to reimplement it with different inputs and outputs. It's not particularly hard to plot the 2D pose or compute the yaw error for the Pose message and there are already tools and libraries that can do this for you.~%~%~%# This expresses a position and orientation on a 2D manifold.~%~%float64 x~%float64 y~%float64 theta~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PathPlan-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'current_pose))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'target_point))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'obstacle))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PathPlan-request>))
  "Converts a ROS message object to a list"
  (cl:list 'PathPlan-request
    (cl:cons ':current_pose (current_pose msg))
    (cl:cons ':target_point (target_point msg))
    (cl:cons ':obstacle (obstacle msg))
))
;//! \htmlinclude PathPlan-response.msg.html

(cl:defclass <PathPlan-response> (roslisp-msg-protocol:ros-message)
  ((new_path
    :reader new_path
    :initarg :new_path
    :type (cl:vector geometry_msgs-msg:Pose2D)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:Pose2D :initial-element (cl:make-instance 'geometry_msgs-msg:Pose2D))))
)

(cl:defclass PathPlan-response (<PathPlan-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PathPlan-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PathPlan-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name path_planner-srv:<PathPlan-response> is deprecated: use path_planner-srv:PathPlan-response instead.")))

(cl:ensure-generic-function 'new_path-val :lambda-list '(m))
(cl:defmethod new_path-val ((m <PathPlan-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader path_planner-srv:new_path-val is deprecated.  Use path_planner-srv:new_path instead.")
  (new_path m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PathPlan-response>) ostream)
  "Serializes a message object of type '<PathPlan-response>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'new_path))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'new_path))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PathPlan-response>) istream)
  "Deserializes a message object of type '<PathPlan-response>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'new_path) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'new_path)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Pose2D))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PathPlan-response>)))
  "Returns string type for a service object of type '<PathPlan-response>"
  "path_planner/PathPlanResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PathPlan-response)))
  "Returns string type for a service object of type 'PathPlan-response"
  "path_planner/PathPlanResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PathPlan-response>)))
  "Returns md5sum for a message object of type '<PathPlan-response>"
  "a9186ff1c0833e5c6cc2915c1b9610f7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PathPlan-response)))
  "Returns md5sum for a message object of type 'PathPlan-response"
  "a9186ff1c0833e5c6cc2915c1b9610f7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PathPlan-response>)))
  "Returns full string definition for message of type '<PathPlan-response>"
  (cl:format cl:nil "~%# Array of intermediate points for the new path~%geometry_msgs/Pose2D[] new_path~%~%================================================================================~%MSG: geometry_msgs/Pose2D~%# Deprecated~%# Please use the full 3D pose.~%~%# In general our recommendation is to use a full 3D representation of everything and for 2D specific applications make the appropriate projections into the plane for their calculations but optimally will preserve the 3D information during processing.~%~%# If we have parallel copies of 2D datatypes every UI and other pipeline will end up needing to have dual interfaces to plot everything. And you will end up with not being able to use 3D tools for 2D use cases even if they're completely valid, as you'd have to reimplement it with different inputs and outputs. It's not particularly hard to plot the 2D pose or compute the yaw error for the Pose message and there are already tools and libraries that can do this for you.~%~%~%# This expresses a position and orientation on a 2D manifold.~%~%float64 x~%float64 y~%float64 theta~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PathPlan-response)))
  "Returns full string definition for message of type 'PathPlan-response"
  (cl:format cl:nil "~%# Array of intermediate points for the new path~%geometry_msgs/Pose2D[] new_path~%~%================================================================================~%MSG: geometry_msgs/Pose2D~%# Deprecated~%# Please use the full 3D pose.~%~%# In general our recommendation is to use a full 3D representation of everything and for 2D specific applications make the appropriate projections into the plane for their calculations but optimally will preserve the 3D information during processing.~%~%# If we have parallel copies of 2D datatypes every UI and other pipeline will end up needing to have dual interfaces to plot everything. And you will end up with not being able to use 3D tools for 2D use cases even if they're completely valid, as you'd have to reimplement it with different inputs and outputs. It's not particularly hard to plot the 2D pose or compute the yaw error for the Pose message and there are already tools and libraries that can do this for you.~%~%~%# This expresses a position and orientation on a 2D manifold.~%~%float64 x~%float64 y~%float64 theta~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PathPlan-response>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'new_path) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PathPlan-response>))
  "Converts a ROS message object to a list"
  (cl:list 'PathPlan-response
    (cl:cons ':new_path (new_path msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'PathPlan)))
  'PathPlan-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'PathPlan)))
  'PathPlan-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PathPlan)))
  "Returns string type for a service object of type '<PathPlan>"
  "path_planner/PathPlan")