;; Auto-generated. Do not edit!


(when (boundp 'ros_can_interface::navigator_navigationMessage)
  (if (not (find-package "ROS_CAN_INTERFACE"))
    (make-package "ROS_CAN_INTERFACE"))
  (shadow 'navigator_navigationMessage (find-package "ROS_CAN_INTERFACE")))
(unless (find-package "ROS_CAN_INTERFACE::NAVIGATOR_NAVIGATIONMESSAGE")
  (make-package "ROS_CAN_INTERFACE::NAVIGATOR_NAVIGATIONMESSAGE"))

(in-package "ROS")
;;//! \htmlinclude navigator_navigationMessage.msg.html


(defclass ros_can_interface::navigator_navigationMessage
  :super ros::object
  :slots (_nav_currentX _nav_currentY _nav_currentAngle _nav_currentState ))

(defmethod ros_can_interface::navigator_navigationMessage
  (:init
   (&key
    ((:nav_currentX __nav_currentX) 0.0)
    ((:nav_currentY __nav_currentY) 0.0)
    ((:nav_currentAngle __nav_currentAngle) 0.0)
    ((:nav_currentState __nav_currentState) 0)
    )
   (send-super :init)
   (setq _nav_currentX (float __nav_currentX))
   (setq _nav_currentY (float __nav_currentY))
   (setq _nav_currentAngle (float __nav_currentAngle))
   (setq _nav_currentState (round __nav_currentState))
   self)
  (:nav_currentX
   (&optional __nav_currentX)
   (if __nav_currentX (setq _nav_currentX __nav_currentX)) _nav_currentX)
  (:nav_currentY
   (&optional __nav_currentY)
   (if __nav_currentY (setq _nav_currentY __nav_currentY)) _nav_currentY)
  (:nav_currentAngle
   (&optional __nav_currentAngle)
   (if __nav_currentAngle (setq _nav_currentAngle __nav_currentAngle)) _nav_currentAngle)
  (:nav_currentState
   (&optional __nav_currentState)
   (if __nav_currentState (setq _nav_currentState __nav_currentState)) _nav_currentState)
  (:serialization-length
   ()
   (+
    ;; float32 _nav_currentX
    4
    ;; float32 _nav_currentY
    4
    ;; float32 _nav_currentAngle
    4
    ;; int8 _nav_currentState
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _nav_currentX
       (sys::poke _nav_currentX (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _nav_currentY
       (sys::poke _nav_currentY (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _nav_currentAngle
       (sys::poke _nav_currentAngle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int8 _nav_currentState
       (write-byte _nav_currentState s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _nav_currentX
     (setq _nav_currentX (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _nav_currentY
     (setq _nav_currentY (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _nav_currentAngle
     (setq _nav_currentAngle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int8 _nav_currentState
     (setq _nav_currentState (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _nav_currentState 127) (setq _nav_currentState (- _nav_currentState 256)))
   ;;
   self)
  )

(setf (get ros_can_interface::navigator_navigationMessage :md5sum-) "90176a0f60fd26d08c0aaca4ecb268df")
(setf (get ros_can_interface::navigator_navigationMessage :datatype-) "ros_can_interface/navigator_navigationMessage")
(setf (get ros_can_interface::navigator_navigationMessage :definition-)
      "float32 nav_currentX
float32 nav_currentY
float32 nav_currentAngle
int8 nav_currentState
")



(provide :ros_can_interface/navigator_navigationMessage "90176a0f60fd26d08c0aaca4ecb268df")


