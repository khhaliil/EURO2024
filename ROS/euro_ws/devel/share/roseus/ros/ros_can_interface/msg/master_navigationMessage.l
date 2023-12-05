;; Auto-generated. Do not edit!


(when (boundp 'ros_can_interface::master_navigationMessage)
  (if (not (find-package "ROS_CAN_INTERFACE"))
    (make-package "ROS_CAN_INTERFACE"))
  (shadow 'master_navigationMessage (find-package "ROS_CAN_INTERFACE")))
(unless (find-package "ROS_CAN_INTERFACE::MASTER_NAVIGATIONMESSAGE")
  (make-package "ROS_CAN_INTERFACE::MASTER_NAVIGATIONMESSAGE"))

(in-package "ROS")
;;//! \htmlinclude master_navigationMessage.msg.html


(defclass ros_can_interface::master_navigationMessage
  :super ros::object
  :slots (_nav_targetX _nav_targetY _nav_targetAngle _nav_isForward ))

(defmethod ros_can_interface::master_navigationMessage
  (:init
   (&key
    ((:nav_targetX __nav_targetX) 0.0)
    ((:nav_targetY __nav_targetY) 0.0)
    ((:nav_targetAngle __nav_targetAngle) 0.0)
    ((:nav_isForward __nav_isForward) nil)
    )
   (send-super :init)
   (setq _nav_targetX (float __nav_targetX))
   (setq _nav_targetY (float __nav_targetY))
   (setq _nav_targetAngle (float __nav_targetAngle))
   (setq _nav_isForward __nav_isForward)
   self)
  (:nav_targetX
   (&optional __nav_targetX)
   (if __nav_targetX (setq _nav_targetX __nav_targetX)) _nav_targetX)
  (:nav_targetY
   (&optional __nav_targetY)
   (if __nav_targetY (setq _nav_targetY __nav_targetY)) _nav_targetY)
  (:nav_targetAngle
   (&optional __nav_targetAngle)
   (if __nav_targetAngle (setq _nav_targetAngle __nav_targetAngle)) _nav_targetAngle)
  (:nav_isForward
   (&optional (__nav_isForward :null))
   (if (not (eq __nav_isForward :null)) (setq _nav_isForward __nav_isForward)) _nav_isForward)
  (:serialization-length
   ()
   (+
    ;; float32 _nav_targetX
    4
    ;; float32 _nav_targetY
    4
    ;; float32 _nav_targetAngle
    4
    ;; bool _nav_isForward
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _nav_targetX
       (sys::poke _nav_targetX (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _nav_targetY
       (sys::poke _nav_targetY (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _nav_targetAngle
       (sys::poke _nav_targetAngle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; bool _nav_isForward
       (if _nav_isForward (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _nav_targetX
     (setq _nav_targetX (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _nav_targetY
     (setq _nav_targetY (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _nav_targetAngle
     (setq _nav_targetAngle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; bool _nav_isForward
     (setq _nav_isForward (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get ros_can_interface::master_navigationMessage :md5sum-) "fe1a2421738fe61ce953bf0c9b6e4f00")
(setf (get ros_can_interface::master_navigationMessage :datatype-) "ros_can_interface/master_navigationMessage")
(setf (get ros_can_interface::master_navigationMessage :definition-)
      "float32 nav_targetX
float32 nav_targetY
float32 nav_targetAngle
bool nav_isForward

")



(provide :ros_can_interface/master_navigationMessage "fe1a2421738fe61ce953bf0c9b6e4f00")


