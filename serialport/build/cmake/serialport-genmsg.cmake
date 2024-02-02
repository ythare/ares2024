# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "serialport: 10 messages, 0 services")

set(MSG_I_FLAGS "-Iserialport:/home/ares_yt/ws_livox/src/serialport/msg;-Iserialport:/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg;-Iactionlib_msgs:/opt/ros/noetic/share/actionlib_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(serialport_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/msg/Chassis_Control.msg" NAME_WE)
add_custom_target(_serialport_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "serialport" "/home/ares_yt/ws_livox/src/serialport/msg/Chassis_Control.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/msg/RobotDate.msg" NAME_WE)
add_custom_target(_serialport_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "serialport" "/home/ares_yt/ws_livox/src/serialport/msg/RobotDate.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/msg/Gimbal_Control.msg" NAME_WE)
add_custom_target(_serialport_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "serialport" "/home/ares_yt/ws_livox/src/serialport/msg/Gimbal_Control.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseAction.msg" NAME_WE)
add_custom_target(_serialport_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "serialport" "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseAction.msg" "serialport/move_baseActionFeedback:serialport/move_baseFeedback:actionlib_msgs/GoalID:serialport/move_baseActionGoal:serialport/move_baseActionResult:actionlib_msgs/GoalStatus:serialport/move_baseGoal:serialport/move_baseResult:std_msgs/Header"
)

get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionGoal.msg" NAME_WE)
add_custom_target(_serialport_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "serialport" "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionGoal.msg" "serialport/move_baseGoal:actionlib_msgs/GoalID:std_msgs/Header"
)

get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionResult.msg" NAME_WE)
add_custom_target(_serialport_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "serialport" "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionResult.msg" "serialport/move_baseResult:actionlib_msgs/GoalStatus:actionlib_msgs/GoalID:std_msgs/Header"
)

get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionFeedback.msg" NAME_WE)
add_custom_target(_serialport_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "serialport" "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionFeedback.msg" "serialport/move_baseFeedback:actionlib_msgs/GoalStatus:actionlib_msgs/GoalID:std_msgs/Header"
)

get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseGoal.msg" NAME_WE)
add_custom_target(_serialport_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "serialport" "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseGoal.msg" ""
)

get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseResult.msg" NAME_WE)
add_custom_target(_serialport_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "serialport" "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseResult.msg" ""
)

get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseFeedback.msg" NAME_WE)
add_custom_target(_serialport_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "serialport" "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseFeedback.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(serialport
  "/home/ares_yt/ws_livox/src/serialport/msg/Chassis_Control.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/serialport
)
_generate_msg_cpp(serialport
  "/home/ares_yt/ws_livox/src/serialport/msg/RobotDate.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/serialport
)
_generate_msg_cpp(serialport
  "/home/ares_yt/ws_livox/src/serialport/msg/Gimbal_Control.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/serialport
)
_generate_msg_cpp(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseAction.msg"
  "${MSG_I_FLAGS}"
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionFeedback.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseFeedback.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionGoal.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionResult.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseGoal.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseResult.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/serialport
)
_generate_msg_cpp(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseGoal.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/serialport
)
_generate_msg_cpp(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionResult.msg"
  "${MSG_I_FLAGS}"
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseResult.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/serialport
)
_generate_msg_cpp(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseFeedback.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/serialport
)
_generate_msg_cpp(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/serialport
)
_generate_msg_cpp(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/serialport
)
_generate_msg_cpp(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/serialport
)

### Generating Services

### Generating Module File
_generate_module_cpp(serialport
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/serialport
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(serialport_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(serialport_generate_messages serialport_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/msg/Chassis_Control.msg" NAME_WE)
add_dependencies(serialport_generate_messages_cpp _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/msg/RobotDate.msg" NAME_WE)
add_dependencies(serialport_generate_messages_cpp _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/msg/Gimbal_Control.msg" NAME_WE)
add_dependencies(serialport_generate_messages_cpp _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseAction.msg" NAME_WE)
add_dependencies(serialport_generate_messages_cpp _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionGoal.msg" NAME_WE)
add_dependencies(serialport_generate_messages_cpp _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionResult.msg" NAME_WE)
add_dependencies(serialport_generate_messages_cpp _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionFeedback.msg" NAME_WE)
add_dependencies(serialport_generate_messages_cpp _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseGoal.msg" NAME_WE)
add_dependencies(serialport_generate_messages_cpp _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseResult.msg" NAME_WE)
add_dependencies(serialport_generate_messages_cpp _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseFeedback.msg" NAME_WE)
add_dependencies(serialport_generate_messages_cpp _serialport_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(serialport_gencpp)
add_dependencies(serialport_gencpp serialport_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS serialport_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(serialport
  "/home/ares_yt/ws_livox/src/serialport/msg/Chassis_Control.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/serialport
)
_generate_msg_eus(serialport
  "/home/ares_yt/ws_livox/src/serialport/msg/RobotDate.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/serialport
)
_generate_msg_eus(serialport
  "/home/ares_yt/ws_livox/src/serialport/msg/Gimbal_Control.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/serialport
)
_generate_msg_eus(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseAction.msg"
  "${MSG_I_FLAGS}"
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionFeedback.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseFeedback.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionGoal.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionResult.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseGoal.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseResult.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/serialport
)
_generate_msg_eus(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseGoal.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/serialport
)
_generate_msg_eus(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionResult.msg"
  "${MSG_I_FLAGS}"
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseResult.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/serialport
)
_generate_msg_eus(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseFeedback.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/serialport
)
_generate_msg_eus(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/serialport
)
_generate_msg_eus(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/serialport
)
_generate_msg_eus(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/serialport
)

### Generating Services

### Generating Module File
_generate_module_eus(serialport
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/serialport
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(serialport_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(serialport_generate_messages serialport_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/msg/Chassis_Control.msg" NAME_WE)
add_dependencies(serialport_generate_messages_eus _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/msg/RobotDate.msg" NAME_WE)
add_dependencies(serialport_generate_messages_eus _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/msg/Gimbal_Control.msg" NAME_WE)
add_dependencies(serialport_generate_messages_eus _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseAction.msg" NAME_WE)
add_dependencies(serialport_generate_messages_eus _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionGoal.msg" NAME_WE)
add_dependencies(serialport_generate_messages_eus _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionResult.msg" NAME_WE)
add_dependencies(serialport_generate_messages_eus _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionFeedback.msg" NAME_WE)
add_dependencies(serialport_generate_messages_eus _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseGoal.msg" NAME_WE)
add_dependencies(serialport_generate_messages_eus _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseResult.msg" NAME_WE)
add_dependencies(serialport_generate_messages_eus _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseFeedback.msg" NAME_WE)
add_dependencies(serialport_generate_messages_eus _serialport_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(serialport_geneus)
add_dependencies(serialport_geneus serialport_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS serialport_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(serialport
  "/home/ares_yt/ws_livox/src/serialport/msg/Chassis_Control.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/serialport
)
_generate_msg_lisp(serialport
  "/home/ares_yt/ws_livox/src/serialport/msg/RobotDate.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/serialport
)
_generate_msg_lisp(serialport
  "/home/ares_yt/ws_livox/src/serialport/msg/Gimbal_Control.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/serialport
)
_generate_msg_lisp(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseAction.msg"
  "${MSG_I_FLAGS}"
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionFeedback.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseFeedback.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionGoal.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionResult.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseGoal.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseResult.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/serialport
)
_generate_msg_lisp(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseGoal.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/serialport
)
_generate_msg_lisp(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionResult.msg"
  "${MSG_I_FLAGS}"
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseResult.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/serialport
)
_generate_msg_lisp(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseFeedback.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/serialport
)
_generate_msg_lisp(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/serialport
)
_generate_msg_lisp(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/serialport
)
_generate_msg_lisp(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/serialport
)

### Generating Services

### Generating Module File
_generate_module_lisp(serialport
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/serialport
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(serialport_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(serialport_generate_messages serialport_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/msg/Chassis_Control.msg" NAME_WE)
add_dependencies(serialport_generate_messages_lisp _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/msg/RobotDate.msg" NAME_WE)
add_dependencies(serialport_generate_messages_lisp _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/msg/Gimbal_Control.msg" NAME_WE)
add_dependencies(serialport_generate_messages_lisp _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseAction.msg" NAME_WE)
add_dependencies(serialport_generate_messages_lisp _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionGoal.msg" NAME_WE)
add_dependencies(serialport_generate_messages_lisp _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionResult.msg" NAME_WE)
add_dependencies(serialport_generate_messages_lisp _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionFeedback.msg" NAME_WE)
add_dependencies(serialport_generate_messages_lisp _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseGoal.msg" NAME_WE)
add_dependencies(serialport_generate_messages_lisp _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseResult.msg" NAME_WE)
add_dependencies(serialport_generate_messages_lisp _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseFeedback.msg" NAME_WE)
add_dependencies(serialport_generate_messages_lisp _serialport_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(serialport_genlisp)
add_dependencies(serialport_genlisp serialport_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS serialport_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(serialport
  "/home/ares_yt/ws_livox/src/serialport/msg/Chassis_Control.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/serialport
)
_generate_msg_nodejs(serialport
  "/home/ares_yt/ws_livox/src/serialport/msg/RobotDate.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/serialport
)
_generate_msg_nodejs(serialport
  "/home/ares_yt/ws_livox/src/serialport/msg/Gimbal_Control.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/serialport
)
_generate_msg_nodejs(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseAction.msg"
  "${MSG_I_FLAGS}"
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionFeedback.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseFeedback.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionGoal.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionResult.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseGoal.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseResult.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/serialport
)
_generate_msg_nodejs(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseGoal.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/serialport
)
_generate_msg_nodejs(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionResult.msg"
  "${MSG_I_FLAGS}"
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseResult.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/serialport
)
_generate_msg_nodejs(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseFeedback.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/serialport
)
_generate_msg_nodejs(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/serialport
)
_generate_msg_nodejs(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/serialport
)
_generate_msg_nodejs(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/serialport
)

### Generating Services

### Generating Module File
_generate_module_nodejs(serialport
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/serialport
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(serialport_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(serialport_generate_messages serialport_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/msg/Chassis_Control.msg" NAME_WE)
add_dependencies(serialport_generate_messages_nodejs _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/msg/RobotDate.msg" NAME_WE)
add_dependencies(serialport_generate_messages_nodejs _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/msg/Gimbal_Control.msg" NAME_WE)
add_dependencies(serialport_generate_messages_nodejs _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseAction.msg" NAME_WE)
add_dependencies(serialport_generate_messages_nodejs _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionGoal.msg" NAME_WE)
add_dependencies(serialport_generate_messages_nodejs _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionResult.msg" NAME_WE)
add_dependencies(serialport_generate_messages_nodejs _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionFeedback.msg" NAME_WE)
add_dependencies(serialport_generate_messages_nodejs _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseGoal.msg" NAME_WE)
add_dependencies(serialport_generate_messages_nodejs _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseResult.msg" NAME_WE)
add_dependencies(serialport_generate_messages_nodejs _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseFeedback.msg" NAME_WE)
add_dependencies(serialport_generate_messages_nodejs _serialport_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(serialport_gennodejs)
add_dependencies(serialport_gennodejs serialport_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS serialport_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(serialport
  "/home/ares_yt/ws_livox/src/serialport/msg/Chassis_Control.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/serialport
)
_generate_msg_py(serialport
  "/home/ares_yt/ws_livox/src/serialport/msg/RobotDate.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/serialport
)
_generate_msg_py(serialport
  "/home/ares_yt/ws_livox/src/serialport/msg/Gimbal_Control.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/serialport
)
_generate_msg_py(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseAction.msg"
  "${MSG_I_FLAGS}"
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionFeedback.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseFeedback.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionGoal.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionResult.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseGoal.msg;/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseResult.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/serialport
)
_generate_msg_py(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseGoal.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/serialport
)
_generate_msg_py(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionResult.msg"
  "${MSG_I_FLAGS}"
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseResult.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/serialport
)
_generate_msg_py(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseFeedback.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/serialport
)
_generate_msg_py(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/serialport
)
_generate_msg_py(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/serialport
)
_generate_msg_py(serialport
  "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/serialport
)

### Generating Services

### Generating Module File
_generate_module_py(serialport
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/serialport
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(serialport_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(serialport_generate_messages serialport_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/msg/Chassis_Control.msg" NAME_WE)
add_dependencies(serialport_generate_messages_py _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/msg/RobotDate.msg" NAME_WE)
add_dependencies(serialport_generate_messages_py _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/msg/Gimbal_Control.msg" NAME_WE)
add_dependencies(serialport_generate_messages_py _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseAction.msg" NAME_WE)
add_dependencies(serialport_generate_messages_py _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionGoal.msg" NAME_WE)
add_dependencies(serialport_generate_messages_py _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionResult.msg" NAME_WE)
add_dependencies(serialport_generate_messages_py _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseActionFeedback.msg" NAME_WE)
add_dependencies(serialport_generate_messages_py _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseGoal.msg" NAME_WE)
add_dependencies(serialport_generate_messages_py _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseResult.msg" NAME_WE)
add_dependencies(serialport_generate_messages_py _serialport_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/ares_yt/ws_livox/src/serialport/build/devel/share/serialport/msg/move_baseFeedback.msg" NAME_WE)
add_dependencies(serialport_generate_messages_py _serialport_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(serialport_genpy)
add_dependencies(serialport_genpy serialport_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS serialport_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/serialport)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/serialport
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(serialport_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET actionlib_msgs_generate_messages_cpp)
  add_dependencies(serialport_generate_messages_cpp actionlib_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/serialport)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/serialport
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(serialport_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET actionlib_msgs_generate_messages_eus)
  add_dependencies(serialport_generate_messages_eus actionlib_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/serialport)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/serialport
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(serialport_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET actionlib_msgs_generate_messages_lisp)
  add_dependencies(serialport_generate_messages_lisp actionlib_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/serialport)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/serialport
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(serialport_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET actionlib_msgs_generate_messages_nodejs)
  add_dependencies(serialport_generate_messages_nodejs actionlib_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/serialport)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/serialport\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/serialport
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(serialport_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET actionlib_msgs_generate_messages_py)
  add_dependencies(serialport_generate_messages_py actionlib_msgs_generate_messages_py)
endif()
