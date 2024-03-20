#include "rm_robotmsg/Stmdate.h"
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/PointCloud.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/TwistStamped.h>
#include <ros/ros.h>
// tf

#include <tf/transform_broadcaster.h>
class odom_repub
{
public:
    odom_repub()
    {
        ros::Time::init();
        current_time = ros::Time::now();
        last_time = ros::Time::now();
        odom_pub_ = nh.advertise<nav_msgs::Odometry>("/Odometry_ptz", 1);
        odom_subscriber_ = nh.subscribe("/Odometry", 20, &odom_repub::OdomCallback, this);
        yaw_subscriber_ = nh.subscribe("/STM_Date", 20, &odom_repub::yaw_Callback, this);
    }
    void OdomCallback(const nav_msgs::Odometry::ConstPtr &msg)
    {
        current_time = ros::Time::now();

        geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(w);

        geometry_msgs::TransformStamped odom_trans;

        odom_trans.header.stamp = current_time;
        odom_trans.header.frame_id = "odom";
        odom_trans.child_frame_id = "base_link";
    
        odom_trans.transform.translation.x = msg->pose.pose.position.x;;
        odom_trans.transform.translation.y = msg->pose.pose.position.y;
        odom_trans.transform.translation.z = msg->pose.pose.position.z;
        odom_trans.transform.rotation = odom_quat;

        // odom_trans.transform.rotation.x = msg->pose.pose.orientation.x;
        // odom_trans.transform.rotation.y = msg->pose.pose.orientation.y;
        // odom_trans.transform.rotation.z = msg->pose.pose.orientation.z;
        // odom_trans.transform.rotation.w = msg->pose.pose.orientation.w;

        odom_broadcaster.sendTransform(odom_trans);

        nav_msgs::Odometry odom_;
        odom_.header.stamp = current_time;
        odom_.header.frame_id = "odom";
        odom_.pose.pose.position.x = msg->pose.pose.position.x;
        odom_.pose.pose.position.y = msg->pose.pose.position.y;
        odom_.pose.pose.position.z = msg->pose.pose.position.z;
        odom_.pose.pose.orientation = odom_quat;

        
        odom_.child_frame_id = "base_link";

        odom_.twist.twist.linear.x = msg->twist.twist.linear.x;
        odom_.twist.twist.linear.y = msg->twist.twist.linear.y;
        odom_.twist.twist.angular.z = msg->twist.twist.angular.z;
        // publish we message
        odom_pub_.publish(odom_);
    }
    void yaw_Callback(const rm_robotmsg::Stmdate &msg)
    {
        w =(double)( ((int16_t) ((msg.date1 << 8 | msg.date2)) * 0.001f)  );
        // w = -0.41;
        // printf("date1: %d, date2: %d \n", msg.date1, msg.date2);
        printf("angle: %f \n" , w);
    }

private:
    double x;
    double y;
    double w = 0;

    double vx;
    double vy;
    double vw;

    ros::NodeHandle nh;
    ros::Subscriber odom_subscriber_;
    ros::Subscriber yaw_subscriber_;
    ros::Publisher odom_pub_;


    ros::Time current_time, last_time; //时间
    tf::TransformBroadcaster odom_broadcaster;
};

int main(int argc, char **argv)
{
    // 初始化ROS节点
    ros::init(argc, argv, "repub_odom");
    odom_repub repub_odom_;

    ros::spin();
    return 0;
}