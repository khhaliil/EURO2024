
(cl:in-package :asdf)

(defsystem "jack_signal-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "jack_msg" :depends-on ("_package_jack_msg"))
    (:file "_package_jack_msg" :depends-on ("_package"))
  ))