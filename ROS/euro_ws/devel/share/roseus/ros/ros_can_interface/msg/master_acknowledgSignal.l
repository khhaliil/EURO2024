;; Auto-generated. Do not edit!


(when (boundp 'ros_can_interface::master_acknowledgSignal)
  (if (not (find-package "ROS_CAN_INTERFACE"))
    (make-package "ROS_CAN_INTERFACE"))
  (shadow 'master_acknowledgSignal (find-package "ROS_CAN_INTERFACE")))
(unless (find-package "ROS_CAN_INTERFACE::MASTER_ACKNOWLEDGSIGNAL")
  (make-package "ROS_CAN_INTERFACE::MASTER_ACKNOWLEDGSIGNAL"))

(in-package "ROS")
;;//! \htmlinclude master_acknowledgSignal.msg.html


(defclass ros_can_interface::master_acknowledgSignal
  :super ros::object
  :slots (_master_acknowledgeSignal ))

(defmethod ros_can_interface::master_acknowledgSignal
  (:init
   (&key
    ((:master_acknowledgeSignal __master_acknowledgeSignal) nil)
    )
   (send-super :init)
   (setq _master_acknowledgeSignal __master_acknowledgeSignal)
   self)
  (:master_acknowledgeSignal
   (&optional (__master_acknowledgeSignal :null))
   (if (not (eq __master_acknowledgeSignal :null)) (setq _master_acknowledgeSignal __master_acknowledgeSignal)) _master_acknowledgeSignal)
  (:serialization-length
   ()
   (+
    ;; bool _master_acknowledgeSignal
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _master_acknowledgeSignal
       (if _master_acknowledgeSignal (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _master_acknowledgeSignal
     (setq _master_acknowledgeSignal (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get ros_can_interface::master_acknowledgSignal :md5sum-) "db74e876059988b41de2c46733c73690")
(setf (get ros_can_interface::master_acknowledgSignal :datatype-) "ros_can_interface/master_acknowledgSignal")
(setf (get ros_can_interface::master_acknowledgSignal :definition-)
      "bool master_acknowledgeSignal
")



(provide :ros_can_interface/master_acknowledgSignal "db74e876059988b41de2c46733c73690")


