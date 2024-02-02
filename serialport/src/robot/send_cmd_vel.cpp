#include <ros/ros.h>
#include "../..//include/serialport/serialport.hpp"
#include "../../include/robot/robot_start.hpp"
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>
#include <string>
#include <math.h>
#include <move_base_msgs/MoveBaseGoal.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/Twist.h>
#include "std_msgs/String.h" 
#include "std_msgs/Float32.h"
#include <ros/time.h>
#include <boost/asio.hpp>
#include "tf/transform_datatypes.h" 
#include "/home/ythare/ws_livox/devel/include/serialport/Chassis_Control.h"
#include "/home/ythare/ws_livox/devel/include/serialport/RobotDate.h"
#include "/home/ythare/ws_livox/devel/include/serialport/Gimbal_Control.h"
// #include <conio.h>
#include "../../../config.h"

using namespace std;
using namespace serialport;
Receive_Date date_receive;
Send_Date date_send;
serialport::RobotDate  robotdate_msg;
/********************************************************
函数功能：订阅/cmd_vel控制 计算两个轮子的分别速度，计算控制位
入口参数：
出口参数：
********************************************************/  
void cmdCallback(const geometry_msgs::Twist msg)
{  
    // ROS_DEBUG("Received a control speed");
    date_send.wheel_vx = msg.linear.x * 500; //700
    date_send.wheel_vy = msg.linear.y * 500; //? 700
    date_send.wheel_wz = msg.angular.z * 7000; //  12000
    ROS_DEBUG("Received Chassis_Control Message: x_set=%4d, y_set=%4d, z_set=%4d",date_send.wheel_vx, date_send.wheel_vy, date_send.wheel_vy);
} 

void PLIO_Callback(const nav_msgs::Odometry::ConstPtr &msg)
{
    robotdate_msg.x_now = msg->pose.pose.position.x;
    robotdate_msg.y_now = msg->pose.pose.position.y;

    float yaww = msg->pose.pose.orientation.w;
    float yawx = msg->pose.pose.orientation.x;
    float yawy = msg->pose.pose.orientation.y;
    float yawz = msg->pose.pose.orientation.z;
    robotdate_msg.w_now = atan2(2 * (yaww * yawz + yawx * yawy), 1 - 2 * (yawy * yawy + yawz * yawz));
    ROS_INFO("Subcribe: x=%f,y=%f,w=%f", robotdate_msg.x_now, robotdate_msg.y_now, robotdate_msg.w_now); // 提示消息
}

void DLO_Callback(const nav_msgs::Odometry::ConstPtr &msg)
{
    // ROS_DEBUG("Received a Robot Info");
    robotdate_msg.x_now = msg->pose.pose.position.x;
    robotdate_msg.y_now = msg->pose.pose.position.y;
    robotdate_msg.vx = msg->twist.twist.linear.x;
    robotdate_msg.vy = msg->twist.twist.linear.y;
    robotdate_msg.vw = msg->twist.twist.angular.z;

    float yaww = msg->pose.pose.orientation.w;
    float yawx = msg->pose.pose.orientation.x;
    float yawy = msg->pose.pose.orientation.y;
    float yawz = msg->pose.pose.orientation.z;

    robotdate_msg.w_now = atan2(2 * (yaww * yawz + yawx * yawy), 1 - 2 * (yawy * yawy + yawz * yawz));
    // ROS_DEBUG("Subcribe: x=%f,y=%f,w=%f", robotdate_msg.x_now, robotdate_msg.y_now, robotdate_msg.w_now); // 提示消息
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "send_cmdvel_node");
    ros::NodeHandle nh;
    
    string Gimbal_topic = getParam("Gimbal_Control_topic", ((string) "/Gimbal_Control"));

#ifdef serial_enable
        SerialPort *serial_port = new SerialPort(usart_port); // 如果不填写目标USB，即可搜索所有USB并开启
#endif
    
    bool debug_flag = true;
    if (debug_flag)
    {
        ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug);
        ROS_INFO_STREAM("DEBUG has Open\n");
    }
    else
    {
        ROS_INFO_STREAM("DEBUG has Closed\n");
    }
    robot::robot myrobot;
    if (!myrobot.init())
        ROS_ERROR("myrobot start failed.");
    ROS_INFO("myrobot start successful");

    // 订阅imu数据 机器人的姿态
    ros::Subscriber sub_dlo = nh.subscribe("/robot/dlo/odom_node/odom", 10, DLO_Callback);
    //向下位机发送控制消息
    ros::Subscriber sub_cmd = nh.subscribe("/cmd_vel", 1, cmdCallback);

    ROS_INFO("********************start************************* ");
    ros::Rate loop_rate(50); //HZ
    // int ch;
    while (ros::ok())
    {
        try 
        {
            // ch = console.getch();
            // if(ch == 27)
            // {
            //     date_send.wheel_wz = 0;
            //     date_send.wheel_vx = 0;
            //     date_send.wheel_vy = 0;
            //     // serial_port->sendDate(&date_send);
            //     break;
            // }
            // date_send.wheel_vx = 0;
            // date_send.wheel_vy = 0 ;
            // date_send.wheel_wz = 5000;
            // date_send.arrive_flag = 1;
            
#ifdef serial_enable
            // serial_port->receiveData(&date_receive);   
            serial_port->sendDate(&date_send);  
#endif
            // ROS_DEBUG("Rx Control Msg: x_set=%d,   y_set: %d,     z_set=%d, crc1 = %d, crc2 = %d", date_send.wheel_vx, date_send.wheel_vy, date_send.wheel_wz, date_send.crc1, date_send.crc2);
            
            myrobot.task_start(robotdate_msg.x_now, robotdate_msg.y_now, robotdate_msg.w_now, 
                                robotdate_msg.vx, robotdate_msg.vy, robotdate_msg.vw );
        }
        catch (exception e)
        {
            ROS_ERROR_STREAM("Some error!! (serialport is not connected)");
        }
        
        ros::spinOnce();
        loop_rate.sleep();
    }
    // close serial port
        // ROS_INFO_STREAM("Serial has Closed\n");
        // date_send.wheel_wz = 0;
        // date_send.wheel_vx = 0;
        // date_send.wheel_vy = 0;
#ifdef serial_enable
    serial_port->~SerialPort();
#endif

    return 0;
}
