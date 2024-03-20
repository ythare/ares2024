#include <ros/ros.h>
#include "../include/serialport.hpp"
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>
#include <string>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include "rm_robotmsg/Stmdate.h"
#include "rm_robotmsg/RobotState.h"
#include "../../config.h"
#include <thread>
#include <mutex>
#include <unistd.h>
using namespace serialport;
using namespace std;

#ifdef serial_enable
    SerialPort serialPort("/dev/stm");
#endif

class serial_start
{
private:
    ros::NodeHandle nh;
    ros::Subscriber sub_cmd;
    ros::Subscriber sub_robotstate;
    ros::Publisher STMdate_pub;

    std::thread receive_STM;
    std::thread send_STM;

    Receive_Date receive_date;
    Send_Date date_send;

    rm_robotmsg::Stmdate STM_date;
    rm_robotmsg::RobotState Robotdate_msg_;

public:

    serial_start()
    {
        ROS_INFO_STREAM("\033[1;32m----> Serialport started....\033[0m");


        sub_cmd = nh.subscribe("/cmd_vel_", 1, &serial_start::cmdCallback, this);
        sub_robotstate = nh.subscribe("/Robotstate", 1, &serial_start::robotstateCallback, this);
        STMdate_pub = nh.advertise<rm_robotmsg::Stmdate>("/STM_Date", 10);

        receive_STM = std::thread(&serial_start::receivefromSTM, this);
        send_STM = std::thread(&serial_start::send2STM, this);

        date_send.wheel_vx = 0;
        date_send.wheel_vy = 0;
        date_send.wheel_wz = 0;
   
    }
    ~serial_start()
    {
    }


    void cmdCallback(const geometry_msgs::Twist msg)
    {
        date_send.wheel_vx = msg.linear.x * 1000;  // 600
        date_send.wheel_vy = msg.linear.y * 1000;  //? 700
        date_send.wheel_wz = msg.angular.z * 1200; //  900

        printf("vel_x= %f, vel_y = %f, vel_w= %f, arrive_flag= %d \n", msg.linear.x, msg.linear.y, msg.angular.z, date_send.arrive_flag);
    }

    void robotstateCallback(const rm_robotmsg::RobotState &robotdate_msg)
    {
        Robotdate_msg_.arrive_flag = robotdate_msg.arrive_flag;
        Robotdate_msg_.arrive_flag_last = robotdate_msg.arrive_flag_last;
        // printf("\033[1;3;32m ------->flag: %f , flag_last: %f \033[0m\n ", Robotdate_msg_.arrive_flag, Robotdate_msg_.arrive_flag_last);
    }

    void receivefromSTM()
    {
        while (1)
        {
#ifdef serial_enable
            // printf("1111 \n");
            serialPort.receiveData(&receive_date);
            STM_date.goal = receive_date.goal;
            STM_date.date1 = receive_date.date1;
            STM_date.date2 = receive_date.date2;
            STM_date.date4 = receive_date.date4;
            STM_date.date5 = receive_date.date5;
            STM_date.date6 = receive_date.date6;
            STM_date.date7 = receive_date.date7;
            

#else
            if (Robotdate_msg_.arrive_flag - Robotdate_msg_.arrive_flag_last == 1)
            {
                Targoal_without_serial += 1; // 目标+1
                date_send.arrive_flag += 1;
                Robotdate_msg_.arrive_flag_last += 1;
                printf("\033[1;3;32m ------->arrive_flag: %d \033[0m\n ", date_send.arrive_flag);
            }
            STM_date.goal = Targoal_without_serial;
            STM_date.date1 = receive_date.date1;
            STM_date.date2 = receive_date.date2;
            STM_date.date4 = receive_date.date4;
            STM_date.date5 = receive_date.date5;
            STM_date.date6 = receive_date.date6;
            STM_date.date7 = receive_date.date7;
#endif
            STMdate_pub.publish(STM_date);
        }
    }

    void send2STM()
    {
        while (1)
        {
#ifdef serial_enable
            if (Robotdate_msg_.arrive_flag - Robotdate_msg_.arrive_flag_last == 1)
            {
                date_send.arrive_flag += 1;
                Robotdate_msg_.arrive_flag_last += 1;
                printf("\033[1;3;32m ------->arrive_flag: %d \033[0m\n ", date_send.arrive_flag);
            }
            // date_send.wheel_vx = 0;
            // date_send.wheel_vy = 0;
            // date_send.wheel_wz = 700;
            // printf("vel_x= %d, vel_y = %d, vel_w= %d, arrive_flag= %d \n", date_send.wheel_vx, date_send.wheel_vy, date_send.wheel_wz, date_send.arrive_flag);
            usleep(10000);  //延时 否则莫名抖动
            serialPort.sendDate(&date_send);
#endif
        }
    }

};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "serial_node");
    serial_start serial_Start_;
    ros::spin();
    return 0;
}
