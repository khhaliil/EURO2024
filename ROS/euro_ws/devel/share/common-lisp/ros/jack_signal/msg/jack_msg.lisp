; Auto-generated. Do not edit!


(cl:in-package jack_signal-msg)


;//! \htmlinclude jack_msg.msg.html

(cl:defclass <jack_msg> (roslisp-msg-protocol:ros-message)
  ((jack_state
    :reader jack_state
    :initarg :jack_state
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass jack_msg (<jack_msg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <jack_msg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'jack_msg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name jack_signal-msg:<jack_msg> is deprecated: use jack_signal-msg:jack_msg instead.")))

(cl:ensure-generic-function 'jack_state-val :lambda-list '(m))
(cl:defmethod jack_state-val ((m <jack_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jack_signal-msg:jack_state-val is deprecated.  Use jack_signal-msg:jack_state instead.")
  (jack_state m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <jack_msg>) ostream)
  "Serializes a message object of type '<jack_msg>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'jack_state) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <jack_msg>) istream)
  "Deserializes a message object of type '<jack_msg>"
    (cl:setf (cl:slot-value msg 'jack_state) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<jack_msg>)))
  "Returns string type for a message object of type '<jack_msg>"
  "jack_signal/jack_msg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'jack_msg)))
  "Returns string type for a message object of type 'jack_msg"
  "jack_signal/jack_msg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<jack_msg>)))
  "Returns md5sum for a message object of type '<jack_msg>"
  "452828b561eb89702df2b017469a83ed")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'jack_msg)))
  "Returns md5sum for a message object of type 'jack_msg"
  "452828b561eb89702df2b017469a83ed")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<jack_msg>)))
  "Returns full string definition for message of type '<jack_msg>"
  (cl:format cl:nil "bool jack_state~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'jack_msg)))
  "Returns full string definition for message of type 'jack_msg"
  (cl:format cl:nil "bool jack_state~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <jack_msg>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <jack_msg>))
  "Converts a ROS message object to a list"
  (cl:list 'jack_msg
    (cl:cons ':jack_state (jack_state msg))
))
