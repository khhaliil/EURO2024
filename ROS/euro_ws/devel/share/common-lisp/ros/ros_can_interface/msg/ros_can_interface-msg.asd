
(cl:in-package :asdf)

(defsystem "ros_can_interface-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "lidar_stopSignal" :depends-on ("_package_lidar_stopSignal"))
    (:file "_package_lidar_stopSignal" :depends-on ("_package"))
    (:file "master_acknowledgSignal" :depends-on ("_package_master_acknowledgSignal"))
    (:file "_package_master_acknowledgSignal" :depends-on ("_package"))
    (:file "master_navigationMessage" :depends-on ("_package_master_navigationMessage"))
    (:file "_package_master_navigationMessage" :depends-on ("_package"))
    (:file "navigator_navigationMessage" :depends-on ("_package_navigator_navigationMessage"))
    (:file "_package_navigator_navigationMessage" :depends-on ("_package"))
  ))