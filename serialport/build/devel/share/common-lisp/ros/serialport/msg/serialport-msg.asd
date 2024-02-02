
(cl:in-package :asdf)

(defsystem "serialport-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "Chassis_Control" :depends-on ("_package_Chassis_Control"))
    (:file "_package_Chassis_Control" :depends-on ("_package"))
    (:file "Gimbal_Control" :depends-on ("_package_Gimbal_Control"))
    (:file "_package_Gimbal_Control" :depends-on ("_package"))
    (:file "RobotDate" :depends-on ("_package_RobotDate"))
    (:file "_package_RobotDate" :depends-on ("_package"))
  ))