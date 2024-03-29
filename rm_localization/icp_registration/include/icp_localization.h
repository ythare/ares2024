#pragma once
// std
#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <boost/shared_ptr.hpp> // 添加boost头文件
//ros
#include <ros/ros.h>
#include <ros/timer.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/point_cloud_conversion.h>
#include <nav_msgs/OccupancyGrid.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/TransformStamped.h>
#include <nav_msgs/Odometry.h>
// tf2
#include <tf/transform_listener.h>
#include <tf2/utils.h>
#include <tf2/LinearMath/Transform.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_listener.h>
#include "tf2_ros/transform_broadcaster.h"
// pcl
#include <pcl/io/pcd_io.h>  //PCD文件输入输出操作
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_cloud.h>
#include <pcl/registration/icp.h>
#include <pcl/registration/ndt.h>

#include <pcl/features/normal_3d.h>


// #include <tf2_geometry_msgs/tf2_geometry_msgs.h>

// #include <tf2_ros/buffer.h>

#include <Eigen/src/Geometry/Quaternion.h>
#include <Eigen/src/Geometry/Transform.h>


// #include <stdexcept>

namespace icp {


class IcpNode{
public:

  IcpNode();
  ~IcpNode();
private:
  ros::NodeHandle nh;
  ros::NodeHandle private_nh;
  // ROS1 part
  ros::Subscriber initial_pose_sub_;        //声明一个Subscriber
  ros::Subscriber pointcloud_sub_;

  typedef   pcl::PointNormal   PointType;
  typedef   pcl::PointCloud<pcl::PointXYZ>  PointCloudXYZ;
  typedef   pcl::PointCloud<pcl::PointNormal> PointCloudXYZN;

  void pointcloudCallback(const sensor_msgs::PointCloud2::ConstPtr msg);
  void initialPoseCallback(const geometry_msgs::PoseWithCovarianceStampedConstPtr msg);

  static PointCloudXYZN::Ptr addNorm(PointCloudXYZ::Ptr cloud);
  // Eigen::Matrix4d align(PointCloudXYZI::Ptr source,
  //                       const Eigen::Matrix4d &init_guess);

  Eigen::Matrix4d multiAlignSync(PointCloudXYZ::Ptr source, const Eigen::Matrix4d &init_guess);
  void pub_tf_thread();

  // rclcpp::TimerBase::SharedPtr timer_;
  // std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  tf2_ros::TransformBroadcaster tf_broadcaster_;
  std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
  tf2_ros::Buffer tfBuffer;

  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

  std::mutex mutex_;
  std::thread tf_publisher_thread_;

  // Voxelfilter used to downsample the pointcloud
  pcl::VoxelGrid<pcl::PointXYZ> voxel_rough_filter_;
  pcl::VoxelGrid<pcl::PointXYZ> voxel_refine_filter_;

  // ICP
  int rough_iter_;
  int refine_iter_;
  pcl::IterativeClosestPoint<PointType, PointType> icp_rough_;
  pcl::IterativeClosestPoint<PointType, PointType> icp_refine_;

  // Store

  PointCloudXYZN::Ptr refine_map_;
  PointCloudXYZN::Ptr rough_map_;
  geometry_msgs::TransformStamped map_to_odom_;
  std::string pcd_path_;
  std::string map_frame_id_, odom_frame_id_, laser_frame_id_;
  std::string pointcloud_topic;
  std::vector<double> initial_pose_vec;
  bool success_;
  double score_;
  double thresh_;
  double xy_offset_;
  double yaw_offset_;
  double yaw_resolution_;
  geometry_msgs::Pose initial_pose_;

  bool is_ready_;
  bool first_scan_;
};


}