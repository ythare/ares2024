#include <ros/ros.h>
#include "livox_ros_driver2/CustomMsg.h"
#include <sensor_msgs/PointCloud2.h>
#include "lidar_data.h"
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/TwistStamped.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
// 显示的头文件
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/filters/crop_box.h>

#include "tf/transform_datatypes.h"
#include <tf/transform_listener.h>



ros::Publisher pub_livox_points;
ros::Publisher pub_livox_points_filtered;
pcl::PointCloud<PointXYZIRT>::Ptr raw_cloud_;


float pose_x = 0.00;
float pose_y = 0.00;
float pose_z = 0.00;
// 点云2的数据格式

double thre_low = 0.3;
double thre_high = 0.3;

void livox_raw_callback(livox_ros_driver2::CustomMsgConstPtr lidar_msg)
{
    raw_cloud_->clear();
    for(const auto& p : lidar_msg->points){
        RTPoint point;
        int line_num = (int)p.line;
        point.x = p.x;
        point.y = p.y;
        point.z = p.z;
        point.intensity = p.reflectivity;
        point.time = p.offset_time/1e9;
        point.ring = (line_num);

        Eigen::Vector3d epoint(p.x,p.y,p.z);
        raw_cloud_->push_back(point);
        
    }
    sensor_msgs::PointCloud2 pcl2_msg;
    
    pcl::toROSMsg(*raw_cloud_,pcl2_msg);
    pcl2_msg.header.stamp = lidar_msg->header.stamp;
    pcl2_msg.header.frame_id = "livox_frame";

    pub_livox_points.publish(pcl2_msg);

}

void odom_callback(const nav_msgs::Odometry::ConstPtr &msg)
{
    pose_x = msg->pose.pose.position.x;
    pose_y = msg->pose.pose.position.y;
    pose_z = msg->pose.pose.position.z;
    // printf("pose_x:%f, pose_y:%f, pose_z:%f \n", pose_x, pose_y, pose_z);
}


void point2filter_callback(const sensor_msgs::PointCloud2ConstPtr &msg)
{
    pcl::PCLPointCloud2* pcl_pointcloud2 = new pcl::PCLPointCloud2;
    pcl::PCLPointCloud2ConstPtr pcl_pointcloud2Ptr(pcl_pointcloud2);

    pcl::PCLPointCloud2* cloud_after_PassThrough = new pcl::PCLPointCloud2;
    pcl::PCLPointCloud2ConstPtr cloud_after_PassThroughPtr(cloud_after_PassThrough);
    // 转化为PCL中的点云的数据格式
    pcl_conversions::toPCL(*msg, *pcl_pointcloud2);

        /*方法一：直通滤波器对点云进行处理。*/
    // pcl::PassThrough<pcl::PCLPointCloud2> passthrough_x;
    // passthrough_x.setInputCloud(pcl_pointcloud2Ptr);//输入点云
    // passthrough_x.setFilterFieldName("x");//对z轴进行操作
    // passthrough_x.setFilterLimits(pose_x - thre_low, pose_x + thre_high);//设置直通滤波器操作范围
    // passthrough_x.setFilterLimitsNegative(true);//true表示保留范围外，false表示保留范围内
    // passthrough_x.filter(*cloud_after_PassThrough);//执行滤波，过滤结果保存在 cloud_after_PassThrough

    // pcl::PassThrough<pcl::PCLPointCloud2> passthrough_y;
    // passthrough_y.setInputCloud(cloud_after_PassThroughPtr);//输入点云
    // passthrough_y.setFilterFieldName("y");//对z轴进行操作
    // passthrough_y.setFilterLimits(pose_y - thre_low, pose_y + thre_high);//设置直通滤波器操作范围
    // passthrough_y.setFilterLimitsNegative(true);//true表示保留范围外，false表示保留范围内
    // passthrough_y.filter(*cloud_after_PassThrough);//执行滤波，过滤结果保存在 cloud_after_PassThrough

    // pcl::PassThrough<pcl::PCLPointCloud2> passthrough_z;
    // passthrough_z.setInputCloud(cloud_after_PassThroughPtr);//输入点云
    // passthrough_z.setFilterFieldName("z");//对z轴进行操作
    // passthrough_z.setFilterLimits(pose_z - thre_low, pose_z + thre_high);//设置直通滤波器操作范围
    // passthrough_z.setFilterLimitsNegative(true);//true表示保留范围外，false表示保留范围内
    // passthrough_z.filter(*cloud_after_PassThrough);//执行滤波，过滤结果保存在 cloud_after_PassThrough

    //  /*方法二：box filter对点云进行处理。*/


    // printf("pose_x:%f, pose_y:%f, pose_z:%f \n", pose_x, pose_y, pose_z);

    pcl::CropBox<pcl::PCLPointCloud2> box_filter;//滤波器对象
    box_filter.setMin(Eigen::Vector4f(0 - thre_low, 0 - thre_low, 0 - thre_low, 1.0));//Min和Max是指立方体的两个对角点。每个点由一个四维向量表示，通常最后一个是1.（不知道为什么要有四个，大神知道的给解答一下下）
    box_filter.setMax(Eigen::Vector4f(0 + thre_high, 0 + thre_high, 0 + thre_high+thre_high, 1.0));
    box_filter.setNegative(true);//是保留立方体内的点而去除其他点，还是反之。false是将盒子内的点去除，默认为false
    box_filter.setInputCloud(pcl_pointcloud2Ptr);//输入源
    box_filter.filter(*cloud_after_PassThrough);

    
    sensor_msgs::PointCloud2 sensor_pointcloud2;
    pcl_conversions::moveFromPCL(*cloud_after_PassThrough, sensor_pointcloud2);

    pub_livox_points_filtered.publish(sensor_pointcloud2);

}



int main(int argc, char** argv)
{
    ros::init(argc, argv, "livox_repub_node");
    ros::NodeHandle nh("~");

    std::string livox_raw_message_name;
    nh.param<std::string>("livox_raw_message_name", livox_raw_message_name, "/livox/lidar");
    std::string livox_pointcloud2_message_name;
    nh.param<std::string>("livox_points_message_name", livox_pointcloud2_message_name, "/livox/lidar/pointcloud2");
    nh.param<double>("thre_low", thre_low, 0.3);
    nh.param<double>("thre_high", thre_high, 0.3);
    printf("thre_low: %f , thre_high:%f \n", thre_low, thre_high);

    tf::TransformListener listener;
    listener.waitForTransform("/map", "/base_footprint", ros::Time(), ros::Duration(1.0));

    raw_cloud_ = boost::make_shared<pcl::PointCloud<PointXYZIRT>>();
    pub_livox_points_filtered = nh.advertise<sensor_msgs::PointCloud2>(livox_pointcloud2_message_name.c_str(), 10);
    pub_livox_points = nh.advertise<sensor_msgs::PointCloud2>("/livox/lidar/pointcloud2_", 10);
    ros::Subscriber sub_livox_raw = nh.subscribe(livox_raw_message_name.c_str(),1000,livox_raw_callback);
    ros::Subscriber odom_sub = nh.subscribe("/Odometry", 10, odom_callback);
    ros::Subscriber pointcloud2_sub = nh.subscribe("/livox/lidar/pointcloud2_", 10, point2filter_callback);

    // pcl::visualization::PCLVisualizer viewer("cloud_viwer");
    // boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("viewer"));
    // viewer.addCoordinateSystem();  

    ros::Rate rate(100);
    while (ros::ok())
    {
        // tf::StampedTransform transform;
        // try
        // {
            // 监听小车在基坐标下的相对坐标 /slamware_map  /map
            //  listener.lookupTransform("/odom", "/base_link", ros::Time(0), transform);
            // listener.lookupTransform("/map", "/base_footprint", ros::Time(0), transform);

            // pose_x = transform.getOrigin().getX();
            // pose_y = transform.getOrigin().getY();
            // pose_z = transform.getOrigin().getZ();
            // printf("pose_x:%f, pose_y:%f, pose_z:%f \n", pose_x, pose_y, pose_z);
        // }
        // catch (tf::TransformException &ex)
        // {
            // ROS_WARN("tf error: %s", ex.what());
        // }
        ros::spinOnce();
        rate.sleep();
    }
    return 1;
}