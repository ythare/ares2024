# generated from catkin/cmake/template/pkg.context.pc.in
CATKIN_PACKAGE_PREFIX = ""
PROJECT_PKG_CONFIG_INCLUDE_DIRS = "${prefix}/include".split(';') if "${prefix}/include" != "" else []
PROJECT_CATKIN_DEPENDS = "roscpp;rospy;serial;std_msgs;geometry_msgs;nav_msgs;sensor_msgs;tf;tf2_geometry_msgs;message_runtime;actionlib_msgs;actionlib".replace(';', ' ')
PKG_CONFIG_LIBRARIES_WITH_PREFIX = "-lserialport".split(';') if "-lserialport" != "" else []
PROJECT_NAME = "serialport"
PROJECT_SPACE_DIR = "/usr/local"
PROJECT_VERSION = "0.0.0"
