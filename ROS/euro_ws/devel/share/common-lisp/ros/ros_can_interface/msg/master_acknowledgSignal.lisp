; Auto-generated. Do not edit!


(cl:in-package ros_can_interface-msg)


;//! \htmlinclude master_acknowledgSignal.msg.html

(cl:defclass <master_acknowledgSignal> (roslisp-msg-protocol:ros-message)
  ((master_acknowledgeSignal
    :reader master_acknowledgeSignal
    :initarg :master_acknowledgeSignal
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass master_acknowledgSignal (<master_acknowledgSignal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <master_acknowledgSignal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'master_acknowledgSignal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_can_interface-msg:<master_acknowledgSignal> is deprecated: use ros_can_interface-msg:master_acknowledgSignal instead.")))

(cl:ensure-generic-function 'master_acknowledgeSignal-val :lambda-list '(m))
(cl:defmethod master_acknowledgeSignal-val ((m <master_acknowledgSignal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_can_interface-msg:master_acknowledgeSignal-val is deprecated.  Use ros_can_interface-msg:master_acknowledgeSignal instead.")
  (master_acknowledgeSignal m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <master_acknowledgSignal>) ostream)
  "Serializes a message object of type '<master_acknowledgSignal>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'master_acknowledgeSignal) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <master_acknowledgSignal>) istream)
  "Deserializes a message object of type '<master_acknowledgSignal>"
    (cl:setf (cl:slot-value msg 'master_acknowledgeSignal) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<master_acknowledgSignal>)))
  "Returns string type for a message object of type '<master_acknowledgSignal>"
  "ros_can_interface/master_acknowledgSignal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'master_acknowledgSignal)))
  "Returns string type for a message object of type 'master_acknowledgSignal"
  "ros_can_interface/master_acknowledgSignal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<master_acknowledgSignal>)))
  "Returns md5sum for a message object of type '<master_acknowledgSignal>"
  "db74e876059988b41de2c46733c73690")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'master_acknowledgSignal)))
  "Returns md5sum for a message object of type 'master_acknowledgSignal"
  "db74e876059988b41de2c46733c73690")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<master_acknowledgSignal>)))
  "Returns full string definition for message of type '<master_acknowledgSignal>"
  (cl:format cl:nil "bool master_acknowledgeSignal~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'master_acknowledgSignal)))
  "Returns full string definition for message of type 'master_acknowledgSignal"
  (cl:format cl:nil "bool master_acknowledgeSignal~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <master_acknowledgSignal>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <master_acknowledgSignal>))
  "Converts a ROS message object to a list"
  (cl:list 'master_acknowledgSignal
    (cl:cons ':master_acknowledgeSignal (master_acknowledgeSignal msg))
))
