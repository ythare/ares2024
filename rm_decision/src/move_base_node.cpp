#include <ros/ros.h>
// #include "../include/serialport/serialport.hpp"
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
#include <geometry_msgs/PoseStamped.h>
#include "std_msgs/String.h" 
#include "std_msgs/Float32.h"
#include <ros/time.h>
#include <boost/asio.hpp>
#include "tf/transform_datatypes.h" 
#include "/home/ares_yt/ares/devel/include/serialport/Chassis_Control.h"
#include "/home/ares_yt/ares/devel/include/serialport/RobotDate.h"
#include "/home/ares_yt/ares/devel/include/serialport/Gimbal_Control.h"
#include "math.h"
#include "../../../config.h"

using namespace std;
using namespace serialport;

Receive_Date date_receive_;
Send_Date date_send_;
serialport::RobotDate  robotdate_msg;
// 创建一个 geometry_msgs::PoseStamped 消息对象
geometry_msgs::PoseStamped goal;
// move_base_msgs::MoveBaseGoal goal;

enum move_base_state_{
    PENDING = 0, //目标已被接受，但还没有开始执行。
    ACTIVE,  //目标正在执行中。
    PREEMPTED, // 目标被取消（例如，通过调用 cancelGoal()）。
    SUCCEEDED, //目标已成功完成。
    ABORTED,  //目标由于某种原因而无法完成。
    REJECTED,  // 目标被拒绝，可能是由于目标无法实现。
    PREEMPTING,  //目标正在被取消。
    RECALLING, //目标已经被取消，但是底层动作服务器正在执行撤销操作。
    RECALLED,  //目标已被取消，并且底层动作服务器已经成功执行撤销操作。
    LOST,  //与目标关联的动作服务器已经丢失，这可能是由于与服务器的连接丢失引起的。
} move_base_state;
uint8_t Status = 10;
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

void rviz_goal_callback(geometry_msgs::PoseStamped goal){
//   ROS_INFO("\n\n\n rviz_goal: goal_x=%f, goal_y=%f\n\n", goal.pose.position.x, goal.pose.position.y);
}
void DLO_Callback(const nav_msgs::Odometry::ConstPtr &msg)
{
    robotdate_msg.x_now = msg->pose.pose.position.x;
    robotdate_msg.y_now = msg->pose.pose.position.y;
}
void State_Callback(const actionlib_msgs::GoalStatusArray::ConstPtr& status_msg)
{
    for (const auto& status : status_msg->status_list) {
        // 可以访问 status 对象的各种信息，例如状态、目标 ID 等
        Status = status.status;
        // ROS_INFO("Status: %d",status.status);
    }
}
uint16_t timer_xs = 0;
float timer_count = 20.0;
void timerCallback(const ros::TimerEvent& event) {
    timer_xs = 1;
}

int main(int argc, char **argv)
{
    // 初始化ROS节点
    ros::init(argc, argv, "move_base_");
    ros::NodeHandle nh("~");

    bool debug_flag = false;
    
    if (debug_flag)
    {
        ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug);
        ROS_INFO_STREAM("DEBUG has Open\n");
    }
    else
    {
        ROS_INFO_STREAM("DEBUG has Closed\n");
    }

    goal.header.frame_id = "map";
    // goal.header.stamp = ros::Time::now();
    // 创建定时器，设置定时器周期为1秒，回调函数为timerCallback
    ros::Timer timer = nh.createTimer(ros::Duration(timer_count), timerCallback);

    ros::Subscriber goal_sub = nh.subscribe("/move_base_simple/goal", 10, rviz_goal_callback);
    // 创建一个订阅者，订阅 /move_base/status 主题
    ros::Subscriber status_sub = nh.subscribe("/move_base/status", 10, State_Callback);

    ros::Subscriber sub_dlo = nh.subscribe("/robot/dlo/odom_node/odom", 10, DLO_Callback);
    
    // 创建一个发布者，发布目标点到 /move_base_simple/goal 话题
    ros::Publisher goal_pub = nh.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1);
    // 创建一个发布者，发布取消请求到 /move_base/cancel 话题
    ros::Publisher cancel_pub = nh.advertise<actionlib_msgs::GoalID>("/move_base/cancel", 1);


    // 初始化串口
#ifdef serial_enable
    // string usart_port = getParam("usart_port", ((string) "/dev/ttyACM0"));
    SerialPort *serial_ports = new SerialPort(usart_port); // 如果不填写目标USB，即可搜索所有USB并开启
    ROS_INFO("serial_port ok!");
#endif
    date_receive_.goal=0;

    bool GOAL_ENABLE = 1;

#ifdef two_point_patrol
    char flag_goal = 1;
#else 
    char flag_goal = 0;
#endif

    robotdate_msg.goal_x = 0;
    robotdate_msg.goal_y = 0;
    robotdate_msg.goal_w = 1;
    
    // 循环运行
    ros::Rate loop_rate(5);
    while (ros::ok())
    {
        try
        {
#ifdef serial_enable

            // date_send_.arrive_flag = 1;
            // date_send_.restart_flag = 1;
            serial_ports->sendDate(&date_send_);
            serial_ports->receiveData(&date_receive_);
            // if (!serial_ports->receiveData(&date_receive_))
            {
                // serial_ports->serial_close();
                // ROS_INFO("Restart Serialport");
                // serial_ports->serial_open();
            };
#endif
            if (debug_flag){
            printf("arrive_flag:%d , resive_date_from_stm: %d \n",date_send_.arrive_flag, date_receive_.goal);}
#ifdef two_point_patrol  //两点巡逻，控制是否导航
            int a = date_receive_.goal;
            if (a==1) 
            {
                GOAL_ENABLE = 1;
                flag_goal = 2;
                date_send_.arrive_flag = 2;
                // date_send_.restart_flag = 1;
            }
#else
            flag_goal = date_receive_.goal;
#endif
            if (GOAL_ENABLE)
            {
                if(flag_goal==1)
                {
                    date_send_.arrive_flag = 0;
                    robotdate_msg.goal_x = 9.01;
                    robotdate_msg.goal_y = 0.12;
                    goal.pose.position.x = robotdate_msg.goal_x;
                    goal.pose.position.y = robotdate_msg.goal_y;
                    goal.pose.orientation.w = 1.0;
                    
                    if (debug_flag)
                    {
                        // ROS_INFO("GOAL1: goal_x=%f, goal_y=%f", goal.pose.position.x, goal.pose.position.y);
                    }

                    if((fabs(robotdate_msg.x_now-robotdate_msg.goal_x)<0.2) && (fabs(robotdate_msg.y_now-robotdate_msg.goal_y)<0.2) && (Status == SUCCEEDED))
                    {
                        date_send_.arrive_flag=1;
#ifdef two_point_patrol
                        flag_goal = 0;
#else
                        flag_goal = 0;
#endif
                        GOAL_ENABLE = 0;
                        
                        ROS_INFO("reach goal successful!");
                        goal.pose.position.x = std::numeric_limits<double>::quiet_NaN();
                        goal.pose.position.y = std::numeric_limits<double>::quiet_NaN();
                        goal_pub.publish(goal);//取消目标
                    }
                    else
                    {
                        date_send_.arrive_flag=0;
                        goal_pub.publish(goal);
                        //等10s到达那里
                        if (timer_xs = 1 && Status == ABORTED) //无法到达
                        {
                            timer_xs = 0;
                            goal.pose.position.x = std::numeric_limits<double>::quiet_NaN();
                            goal.pose.position.y = std::numeric_limits<double>::quiet_NaN();
                            goal_pub.publish(goal);//取消目标
                            flag_goal = 1;
                            ROS_INFO("Timed out achieving goal");
                        }
                    }
                }

                if(flag_goal==2)
                {
                    // date_send_.arrive_flag=0;
                    robotdate_msg.goal_x = 1.57;
                    robotdate_msg.goal_y = 0.015;
                    goal.pose.position.x = robotdate_msg.goal_x;
                    goal.pose.position.y = robotdate_msg.goal_y;
                    goal.pose.orientation.w = 0.02;

                    if (debug_flag)
                    {
                        ROS_INFO("GOAL2: goal_x=%f, goal_y=%f", goal.pose.position.x, goal.pose.position.y);
                    }
                    //到达目标
                    if((fabs(robotdate_msg.x_now-robotdate_msg.goal_x)<0.2) && (fabs(robotdate_msg.y_now-robotdate_msg.goal_y)<0.2) && (Status == SUCCEEDED))
                    {
                        date_send_.arrive_flag=1;
#ifdef two_point_patrol
                        flag_goal = 1;
#else
                        flag_goal = 0;
#endif                        
                        ROS_INFO("reach goal successful!");
                        goal.pose.position.x = std::numeric_limits<double>::quiet_NaN();
                        goal.pose.position.y = std::numeric_limits<double>::quiet_NaN();
                        goal_pub.publish(goal);//取消目标
                    }
                    else
                    {
                        // date_send_.arrive_flag=0;
                        goal_pub.publish(goal);

                        //等10s到达那里
                        if (timer_xs = 1 && Status == ABORTED)//无法到达
                        {
                            // if (Status == ACTIVE);
                            timer_xs = 0;
                            goal.pose.position.x = std::numeric_limits<double>::quiet_NaN();
                            goal.pose.position.y = std::numeric_limits<double>::quiet_NaN();
                            goal_pub.publish(goal);//取消目标
                            flag_goal = 2;
                            ROS_INFO("Timed out achieving goal");
                        }
                    }

                }

            }

        }
        catch(exception & e)
        {
            ROS_ERROR_STREAM("Some error in pub_node file ");
        }
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
