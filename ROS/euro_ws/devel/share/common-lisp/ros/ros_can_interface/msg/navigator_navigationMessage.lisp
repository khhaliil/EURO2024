; Auto-generated. Do not edit!


(cl:in-package ros_can_interface-msg)


;//! \htmlinclude navigator_navigationMessage.msg.html

(cl:defclass <navigator_navigationMessage> (roslisp-msg-protocol:ros-message)
  ((nav_currentX
    :reader nav_currentX
    :initarg :nav_currentX
    :type cl:float
    :initform 0.0)
   (nav_currentY
    :reader nav_currentY
    :initarg :nav_currentY
    :type cl:float
    :initform 0.0)
   (nav_currentAngle
    :reader nav_currentAngle
    :initarg :nav_currentAngle
    :type cl:float
    :initform 0.0)
   (nav_currentState
    :reader nav_currentState
    :initarg :nav_currentState
    :type cl:fixnum
    :initform 0))
)

(cl:defclass navigator_navigationMessage (<navigator_navigationMessage>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <navigator_navigationMessage>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'navigator_navigationMessage)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_can_interface-msg:<navigator_navigationMessage> is deprecated: use ros_can_interface-msg:navigator_navigationMessage instead.")))

(cl:ensure-generic-function 'nav_currentX-val :lambda-list '(m))
(cl:defmethod nav_currentX-val ((m <navigator_navigationMessage>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_can_interface-msg:nav_currentX-val is deprecated.  Use ros_can_interface-msg:nav_currentX instead.")
  (nav_currentX m))

(cl:ensure-generic-function 'nav_currentY-val :lambda-list '(m))
(cl:defmethod nav_currentY-val ((m <navigator_navigationMessage>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_can_interface-msg:nav_currentY-val is deprecated.  Use ros_can_interface-msg:nav_currentY instead.")
  (nav_currentY m))

(cl:ensure-generic-function 'nav_currentAngle-val :lambda-list '(m))
(cl:defmethod nav_currentAngle-val ((m <navigator_navigationMessage>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_can_interface-msg:nav_currentAngle-val is deprecated.  Use ros_can_interface-msg:nav_currentAngle instead.")
  (nav_currentAngle m))

(cl:ensure-generic-function 'nav_currentState-val :lambda-list '(m))
(cl:defmethod nav_currentState-val ((m <navigator_navigationMessage>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_can_interface-msg:nav_currentState-val is deprecated.  Use ros_can_interface-msg:nav_currentState instead.")
  (nav_currentState m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <navigator_navigationMessage>) ostream)
  "Serializes a message object of type '<navigator_navigationMessage>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'nav_currentX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'nav_currentY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'nav_currentAngle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'nav_currentState)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <navigator_navigationMessage>) istream)
  "Deserializes a message object of type '<navigator_navigationMessage>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'nav_currentX) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'nav_currentY) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'nav_currentAngle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'nav_currentState) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<navigator_navigationMessage>)))
  "Returns string type for a message object of type '<navigator_navigationMessage>"
  "ros_can_interface/navigator_navigationMessage")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'navigator_navigationMessage)))
  "Returns string type for a message object of type 'navigator_navigationMessage"
  "ros_can_interface/navigator_navigationMessage")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<navigator_navigationMessage>)))
  "Returns md5sum for a message object of type '<navigator_navigationMessage>"
  "90176a0f60fd26d08c0aaca4ecb268df")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'navigator_navigationMessage)))
  "Returns md5sum for a message object of type 'navigator_navigationMessage"
  "90176a0f60fd26d08c0aaca4ecb268df")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<navigator_navigationMessage>)))
  "Returns full string definition for message of type '<navigator_navigationMessage>"
  (cl:format cl:nil "float32 nav_currentX~%float32 nav_currentY~%float32 nav_currentAngle~%int8 nav_currentState~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'navigator_navigationMessage)))
  "Returns full string definition for message of type 'navigator_navigationMessage"
  (cl:format cl:nil "float32 nav_currentX~%float32 nav_currentY~%float32 nav_currentAngle~%int8 nav_currentState~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <navigator_navigationMessage>))
  (cl:+ 0
     4
     4
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <navigator_navigationMessage>))
  "Converts a ROS message object to a list"
  (cl:list 'navigator_navigationMessage
    (cl:cons ':nav_currentX (nav_currentX msg))
    (cl:cons ':nav_currentY (nav_currentY msg))
    (cl:cons ':nav_currentAngle (nav_currentAngle msg))
    (cl:cons ':nav_currentState (nav_currentState msg))
))
