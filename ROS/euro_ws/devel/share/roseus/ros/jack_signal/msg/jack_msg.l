;; Auto-generated. Do not edit!


(when (boundp 'jack_signal::jack_msg)
  (if (not (find-package "JACK_SIGNAL"))
    (make-package "JACK_SIGNAL"))
  (shadow 'jack_msg (find-package "JACK_SIGNAL")))
(unless (find-package "JACK_SIGNAL::JACK_MSG")
  (make-package "JACK_SIGNAL::JACK_MSG"))

(in-package "ROS")
;;//! \htmlinclude jack_msg.msg.html


(defclass jack_signal::jack_msg
  :super ros::object
  :slots (_jack_state ))

(defmethod jack_signal::jack_msg
  (:init
   (&key
    ((:jack_state __jack_state) nil)
    )
   (send-super :init)
   (setq _jack_state __jack_state)
   self)
  (:jack_state
   (&optional (__jack_state :null))
   (if (not (eq __jack_state :null)) (setq _jack_state __jack_state)) _jack_state)
  (:serialization-length
   ()
   (+
    ;; bool _jack_state
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _jack_state
       (if _jack_state (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _jack_state
     (setq _jack_state (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get jack_signal::jack_msg :md5sum-) "452828b561eb89702df2b017469a83ed")
(setf (get jack_signal::jack_msg :datatype-) "jack_signal/jack_msg")
(setf (get jack_signal::jack_msg :definition-)
      "bool jack_state

")



(provide :jack_signal/jack_msg "452828b561eb89702df2b017469a83ed")


