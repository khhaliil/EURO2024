;; Auto-generated. Do not edit!


(when (boundp 'ros_can_interface::lidar_stopSignal)
  (if (not (find-package "ROS_CAN_INTERFACE"))
    (make-package "ROS_CAN_INTERFACE"))
  (shadow 'lidar_stopSignal (find-package "ROS_CAN_INTERFACE")))
(unless (find-package "ROS_CAN_INTERFACE::LIDAR_STOPSIGNAL")
  (make-package "ROS_CAN_INTERFACE::LIDAR_STOPSIGNAL"))

(in-package "ROS")
;;//! \htmlinclude lidar_stopSignal.msg.html


(defclass ros_can_interface::lidar_stopSignal
  :super ros::object
  :slots (_stopSignalState ))

(defmethod ros_can_interface::lidar_stopSignal
  (:init
   (&key
    ((:stopSignalState __stopSignalState) nil)
    )
   (send-super :init)
   (setq _stopSignalState __stopSignalState)
   self)
  (:stopSignalState
   (&optional (__stopSignalState :null))
   (if (not (eq __stopSignalState :null)) (setq _stopSignalState __stopSignalState)) _stopSignalState)
  (:serialization-length
   ()
   (+
    ;; bool _stopSignalState
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _stopSignalState
       (if _stopSignalState (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _stopSignalState
     (setq _stopSignalState (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get ros_can_interface::lidar_stopSignal :md5sum-) "096988a79a296361c0020ef3b05a1428")
(setf (get ros_can_interface::lidar_stopSignal :datatype-) "ros_can_interface/lidar_stopSignal")
(setf (get ros_can_interface::lidar_stopSignal :definition-)
      "bool stopSignalState
")



(provide :ros_can_interface/lidar_stopSignal "096988a79a296361c0020ef3b05a1428")


