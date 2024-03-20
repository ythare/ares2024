#include <ros/ros.h>
#include "../include/serialport.hpp"
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>
#include <string>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include "/home/ares_yt/ares/devel/include/rm_robotmsg/Stmdate.h"
#include "/home/ares_yt/ares/devel/include/rm_robotmsg/RobotState.h"
#include "../../config.h"
#include <thread>
#include <mutex>

class serial_start
{
private:
    ros::NodeHandle nh;
    ros::Subscriber sub_cmd;
public:

};