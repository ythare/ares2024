#include <ros/ros.h>
#include "../../include/serialport/serialport.hpp"
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>
#include <string>

using namespace std;
using namespace serialport;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "serial_node");
    ros::NodeHandle nh;

    string usart_port = getParam("usart_port", ((string) "/dev/ttyACM0"));
    SerialPort *serial_port = new SerialPort(usart_port); // 如果不填写目标USB，即可搜索所有USB并开启
    
    Receive_Date stm_date;
    Send_Date date_send;
    date_send.header=0x55;
    date_send.data_len0 = 3;
    date_send.wheel_vx = 20;
    date_send.wheel_vy = 10;
    date_send.wheel_wz = 10;


    ros::Rate loop_rate(2);

    unsigned char data1[1] = {0xa1}; // send data
    unsigned char data2[1] = {0xb1};
    uint8_t buffer[1024];
    while (ros::ok())
    {
        // serial_port->serialPortRead(buffer,6);
        // std::cout << std::hex << (buffer[0] & 0xff) << " ";
        // ROS_DEBUG("buffer0 %d", buffer[0]);
        if (serial_port->receiveData(&stm_date))
        {
            // printf("date0:%d", stm_date.header);
            std::cout << std::hex << (stm_date.header & 0xff) << " ";
            std::cout << std::hex << (stm_date.command & 0xff) << " ";
            std::cout << std::hex << (stm_date.data_len0 & 0xff) << " ";
        }
        // serial_port->sendDate(&date_send); 
        ros::spinOnce();
        loop_rate.sleep();
    }
    // close serial port
    serial_port->~SerialPort();

    return 0;
}
