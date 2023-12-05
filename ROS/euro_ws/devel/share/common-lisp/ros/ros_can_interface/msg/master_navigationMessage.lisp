; Auto-generated. Do not edit!


(cl:in-package ros_can_interface-msg)


;//! \htmlinclude master_navigationMessage.msg.html

(cl:defclass <master_navigationMessage> (roslisp-msg-protocol:ros-message)
  ((nav_targetX
    :reader nav_targetX
    :initarg :nav_targetX
    :type cl:float
    :initform 0.0)
   (nav_targetY
    :reader nav_targetY
    :initarg :nav_targetY
    :type cl:float
    :initform 0.0)
   (nav_targetAngle
    :reader nav_targetAngle
    :initarg :nav_targetAngle
    :type cl:float
    :initform 0.0)
   (nav_isForward
    :reader nav_isForward
    :initarg :nav_isForward
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass master_navigationMessage (<master_navigationMessage>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <master_navigationMessage>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'master_navigationMessage)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_can_interface-msg:<master_navigationMessage> is deprecated: use ros_can_interface-msg:master_navigationMessage instead.")))

(cl:ensure-generic-function 'nav_targetX-val :lambda-list '(m))
(cl:defmethod nav_targetX-val ((m <master_navigationMessage>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_can_interface-msg:nav_targetX-val is deprecated.  Use ros_can_interface-msg:nav_targetX instead.")
  (nav_targetX m))

(cl:ensure-generic-function 'nav_targetY-val :lambda-list '(m))
(cl:defmethod nav_targetY-val ((m <master_navigationMessage>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_can_interface-msg:nav_targetY-val is deprecated.  Use ros_can_interface-msg:nav_targetY instead.")
  (nav_targetY m))

(cl:ensure-generic-function 'nav_targetAngle-val :lambda-list '(m))
(cl:defmethod nav_targetAngle-val ((m <master_navigationMessage>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_can_interface-msg:nav_targetAngle-val is deprecated.  Use ros_can_interface-msg:nav_targetAngle instead.")
  (nav_targetAngle m))

(cl:ensure-generic-function 'nav_isForward-val :lambda-list '(m))
(cl:defmethod nav_isForward-val ((m <master_navigationMessage>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_can_interface-msg:nav_isForward-val is deprecated.  Use ros_can_interface-msg:nav_isForward instead.")
  (nav_isForward m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <master_navigationMessage>) ostream)
  "Serializes a message object of type '<master_navigationMessage>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'nav_targetX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'nav_targetY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'nav_targetAngle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'nav_isForward) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <master_navigationMessage>) istream)
  "Deserializes a message object of type '<master_navigationMessage>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'nav_targetX) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'nav_targetY) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'nav_targetAngle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:slot-value msg 'nav_isForward) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<master_navigationMessage>)))
  "Returns string type for a message object of type '<master_navigationMessage>"
  "ros_can_interface/master_navigationMessage")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'master_navigationMessage)))
  "Returns string type for a message object of type 'master_navigationMessage"
  "ros_can_interface/master_navigationMessage")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<master_navigationMessage>)))
  "Returns md5sum for a message object of type '<master_navigationMessage>"
  "fe1a2421738fe61ce953bf0c9b6e4f00")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'master_navigationMessage)))
  "Returns md5sum for a message object of type 'master_navigationMessage"
  "fe1a2421738fe61ce953bf0c9b6e4f00")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<master_navigationMessage>)))
  "Returns full string definition for message of type '<master_navigationMessage>"
  (cl:format cl:nil "float32 nav_targetX~%float32 nav_targetY~%float32 nav_targetAngle~%bool nav_isForward~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'master_navigationMessage)))
  "Returns full string definition for message of type 'master_navigationMessage"
  (cl:format cl:nil "float32 nav_targetX~%float32 nav_targetY~%float32 nav_targetAngle~%bool nav_isForward~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <master_navigationMessage>))
  (cl:+ 0
     4
     4
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <master_navigationMessage>))
  "Converts a ROS message object to a list"
  (cl:list 'master_navigationMessage
    (cl:cons ':nav_targetX (nav_targetX msg))
    (cl:cons ':nav_targetY (nav_targetY msg))
    (cl:cons ':nav_targetAngle (nav_targetAngle msg))
    (cl:cons ':nav_isForward (nav_isForward msg))
))
