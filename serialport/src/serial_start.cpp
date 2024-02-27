#include <ros/ros.h>
#include "../include/serialport.hpp"
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>
#include <string>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include "/home/ythare/ws_livox/devel/include/rm_robotmsg/Stmdate.h"
#include "../../config.h"
using namespace std;
using namespace serialport;

Receive_Date receive_date;
rm_robotmsg::Stmdate STM_date;
Send_Date date_send;
#ifdef serial_enable
    SerialPort serialPort("/dev/stm");
#endif

void cmdCallback(const geometry_msgs::Twist msg)
{  
    date_send.wheel_vx = msg.linear.x * 500; //700
    date_send.wheel_vy = msg.linear.y * 500; //? 700
    date_send.wheel_wz = msg.angular.z * 7000; //  12000
    date_send.arrive_flag = 0;

    printf("vel_x= %f, vel_y = %f, vel_w= %f \n", msg.linear.x, msg.linear.y, msg.angular.z);
} 

int main(int argc, char **argv)
{
    ROS_INFO_STREAM("\033[1;32m----> Serialport started.\033[0m");
    ros::init(argc, argv, "serial_node");
    ros::NodeHandle nh;

    ros::Subscriber sub_cmd = nh.subscribe("/cmd_vel", 1, cmdCallback);
    ros::Publisher STMdate_pub = nh.advertise<rm_robotmsg::Stmdate>("/STM_Date", 10);

    // ros::MultiThreadedSpinner spinner(1); // Use 2 threads
    ros::Rate loop_rate(50);

    while (ros::ok())
    {
        // printf("--->vel_x= %d, vel_y = %d, vel_w= %d \n", date_send.wheel_vx, date_send.wheel_vy, date_send.wheel_wz);
#ifdef serial_enable
        serialPort.sendDate(&date_send);
        serialPort.receiveData(&receive_date);
        STM_date.goal = receive_date.goal;
        STM_date.date1 = receive_date.date1;
        STM_date.date3 = receive_date.date3;
        STM_date.date4 = receive_date.date4;
        STM_date.date5 = receive_date.date5;
        STM_date.date6 = receive_date.date6;
        STM_date.date7 = receive_date.date7;
#else
        STM_date.goal = Targoal_without_serial;
        STM_date.date1 = receive_date.date1;
        STM_date.date3 = receive_date.date3;
        STM_date.date4 = receive_date.date4;
        STM_date.date5 = receive_date.date5;
        STM_date.date6 = receive_date.date6;
        STM_date.date7 = receive_date.date7;
#endif
        STMdate_pub.publish(STM_date);

        ros::spinOnce();
        loop_rate.sleep();
    }
    // close serial port
#ifdef serial_enable
    serialPort.~SerialPort();
#endif
    return 0;
}
