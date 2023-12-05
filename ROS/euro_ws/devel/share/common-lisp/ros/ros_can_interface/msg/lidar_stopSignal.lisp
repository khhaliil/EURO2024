; Auto-generated. Do not edit!


(cl:in-package ros_can_interface-msg)


;//! \htmlinclude lidar_stopSignal.msg.html

(cl:defclass <lidar_stopSignal> (roslisp-msg-protocol:ros-message)
  ((stopSignalState
    :reader stopSignalState
    :initarg :stopSignalState
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass lidar_stopSignal (<lidar_stopSignal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <lidar_stopSignal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'lidar_stopSignal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_can_interface-msg:<lidar_stopSignal> is deprecated: use ros_can_interface-msg:lidar_stopSignal instead.")))

(cl:ensure-generic-function 'stopSignalState-val :lambda-list '(m))
(cl:defmethod stopSignalState-val ((m <lidar_stopSignal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_can_interface-msg:stopSignalState-val is deprecated.  Use ros_can_interface-msg:stopSignalState instead.")
  (stopSignalState m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <lidar_stopSignal>) ostream)
  "Serializes a message object of type '<lidar_stopSignal>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'stopSignalState) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <lidar_stopSignal>) istream)
  "Deserializes a message object of type '<lidar_stopSignal>"
    (cl:setf (cl:slot-value msg 'stopSignalState) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<lidar_stopSignal>)))
  "Returns string type for a message object of type '<lidar_stopSignal>"
  "ros_can_interface/lidar_stopSignal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'lidar_stopSignal)))
  "Returns string type for a message object of type 'lidar_stopSignal"
  "ros_can_interface/lidar_stopSignal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<lidar_stopSignal>)))
  "Returns md5sum for a message object of type '<lidar_stopSignal>"
  "096988a79a296361c0020ef3b05a1428")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'lidar_stopSignal)))
  "Returns md5sum for a message object of type 'lidar_stopSignal"
  "096988a79a296361c0020ef3b05a1428")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<lidar_stopSignal>)))
  "Returns full string definition for message of type '<lidar_stopSignal>"
  (cl:format cl:nil "bool stopSignalState~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'lidar_stopSignal)))
  "Returns full string definition for message of type 'lidar_stopSignal"
  (cl:format cl:nil "bool stopSignalState~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <lidar_stopSignal>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <lidar_stopSignal>))
  "Converts a ROS message object to a list"
  (cl:list 'lidar_stopSignal
    (cl:cons ':stopSignalState (stopSignalState msg))
))
