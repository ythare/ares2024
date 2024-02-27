#include "../include/move_base_nav.h"

using namespace std;

rm_nav::rm_nav()
{
    ROS_INFO_STREAM("\033[1;32m----> Move_Base Navigation started.\033[0m");
    ros::service::waitForService("/move_base/make_plan");
    ROS_INFO("\033[1;32m----> move_base init OK \033[0m");

    goal_publisher_ = nh.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1);
    
    goal_subscriber_ = nh.subscribe("/move_base_simple/goal", 10, &rm_nav::rviz_goal_callback, this);
    mvStatus_subscriber_ = nh.subscribe("/move_base/status", 10, &rm_nav::State_Callback, this);
    odom_subscriber_ = nh.subscribe("/Odometry", 10, &rm_nav::Odom_Callback, this);
    TargetLocation_subscriber_ = nh.subscribe("/STM_Date", 10, &rm_nav::GetLocation_callback, this);
}

rm_nav::~rm_nav()
{
    ROS_INFO("Destroying Movebase Navigation");
}

void rm_nav::rviz_goal_callback(geometry_msgs::PoseStamped goal)
{
    // ROS_INFO("\n\n\n rviz_goal: goal_x=%f, goal_y=%f\n\n", goal.pose.position.x, goal.pose.position.y);
    goal_received = true;
}

void rm_nav::State_Callback(const actionlib_msgs::GoalStatusArray::ConstPtr &status_msg)
{
    for (const auto &status : status_msg->status_list)
    {
        // 可以访问 status 对象的各种信息，例如状态、目标 ID 等
        MoveBase_Status = status.status;
        // ROS_INFO("Status: %d",status.status);
    }
}

void rm_nav::Odom_Callback(const nav_msgs::Odometry::ConstPtr &msg)
{
    robotdate_msg.x_now = msg->pose.pose.position.x;
    robotdate_msg.y_now = msg->pose.pose.position.y;

    float yaww = msg->pose.pose.orientation.w;
    float yawx = msg->pose.pose.orientation.x;
    float yawy = msg->pose.pose.orientation.y;
    float yawz = msg->pose.pose.orientation.z;

    robotdate_msg.w_now = atan2(2 * (yaww * yawz + yawx * yawy), 1 - 2 * (yawy * yawy + yawz * yawz));
}

void rm_nav::GetLocation_callback(const rm_robotmsg::Stmdate &msg)
{
    this->nav_goal = msg.goal;
    
    if ((this->nav_goal_last != this->nav_goal) && (goal_received == false) )  
        this->goal_pub_flag = true;

    this->nav_goal_last = this->nav_goal;

    goal.header.frame_id = "map";
    goal.pose.position.x = tarPoints[nav_goal].x;
    goal.pose.position.y = tarPoints[nav_goal].y;
    goal.pose.orientation.w = tarPoints[nav_goal].w;

    if (MoveBase_Status == SUCCEEDED )
    {
        goal.pose.position.x = std::numeric_limits<double>::quiet_NaN();
        goal.pose.position.y = std::numeric_limits<double>::quiet_NaN();
        goal_publisher_.publish(goal); // 取消目标
        goal_received = false;
        ROS_INFO("\033[1;32m----> Arrived OK \033[0m");
    }
    else
    {
        if (this->goal_pub_flag)
        {
            goal_publisher_.publish(goal);
            this->goal_pub_flag = false;
        }

        if (MoveBase_Status == ABORTED)
        {
            goal.pose.position.x = std::numeric_limits<double>::quiet_NaN();
            goal.pose.position.y = std::numeric_limits<double>::quiet_NaN();
            goal_publisher_.publish(goal); // 取消目标
            ROS_INFO("UNable arrive goal");
        }
    }
    
}

void rm_nav::decision()
{
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "move_base_navigation"); // 节点的名字

    rm_nav rm_navigation;

    ros::MultiThreadedSpinner spinner(3); // Use 3 threads
    spinner.spin();                       // spin() will not return until the node has been shutdown
    return 0;
}