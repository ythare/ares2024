#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/GetMap.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/io/pcd_io.h>
#include <pcl_conversions/pcl_conversions.h>
#include <cmath>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/features/normal_3d.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/transform_broadcaster.h>
#include <pcl/surface/mls.h>
#include <Eigen/Core>

#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/radius_outlier_removal.h>   //半径滤波器头文件
#include <pcl/filters/statistical_outlier_removal.h> //统计滤波器头文件
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/filters/crop_box.h>
std::string file_directory;
std::string file_name;
std::string pcd_file;
std::string map_topic_name;
const std::string pcd_format = ".pcd";
nav_msgs::OccupancyGrid map_topic_msg;

double thre_z_min = -0.01;
double thre_z_max = 2.5;
int flag_pass_through = 0;

double radious = 0.05;
double thre_count = 50;

double grid_x = 0.1;
double grid_y = 0.1;
double grid_z = 0.1;

double map_resolution = 0.05;

double thre_radius = 0.1;

pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_after_PassThrough(new pcl::PointCloud<pcl::PointXYZ>);
pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_after_Radius(new pcl::PointCloud<pcl::PointXYZ>);
pcl::PointCloud<pcl::PointXYZ>::Ptr pcd_cloud(new pcl::PointCloud<pcl::PointXYZ>);
pcl::PointCloud<pcl::PointXYZ>::Ptr pcl_out(new pcl::PointCloud<pcl::PointXYZ>);

void PassThroughFilter(const double& thre_low, const double& thre_high, const bool& flag_in);

void RadiusOutlierFilter(const pcl::PointCloud<pcl::PointXYZ>::Ptr& pcd_cloud, const double &radius, const int &thre_count);

void SetMapTopicMsg(const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, nav_msgs::OccupancyGrid& msg);

void VotexFilter(const pcl::PointCloud<pcl::PointXYZ>::Ptr& pcd_cloud0, const double &radius, const int &thre_count);

int main(int argc, char** argv)
{
   ros::init(argc, argv, "pcl_filters");
   ros::NodeHandle nh;
   ros::NodeHandle private_nh("~");
   ros::Rate loop_rate(1.0);
   private_nh.param("file_directory", file_directory, std::string("/home/ares_yt/ws_livox/src/Lidar_SLAM/Point-LIO/PCD/"));
   ROS_INFO("*** file_directory = %s ***\n", file_directory.c_str());
   private_nh.param("file_name", file_name, std::string("scans"));
   ROS_INFO("*** file_name = %s ***\n", file_name.c_str());
   pcd_file = file_directory + file_name + pcd_format;
   ROS_INFO("*** pcd_file = %s ***\n", pcd_file.c_str());
   private_nh.param("map_topic_name", map_topic_name, std::string("map"));
   ros::Publisher map_topic_pub = nh.advertise<nav_msgs::OccupancyGrid>(map_topic_name, 1);

   if (pcl::io::loadPCDFile<pcl::PointXYZ> (pcd_file, *pcd_cloud) == -1)
   {
     PCL_ERROR ("Couldn't read file: %s \n", pcd_file.c_str());
     return (-1);
   }
    std::cout << "初始点云数据点数：" << pcd_cloud->points.size() << std::endl;

    PassThroughFilter(thre_z_min, thre_z_max, bool(flag_pass_through));
    RadiusOutlierFilter(cloud_after_PassThrough, radious, thre_count);

    pcl::CropBox<pcl::PointXYZ> box_filter;//滤波器对象
    box_filter.setMin(Eigen::Vector4f(-7, -10, -0.2, 1.0));//Min和Max是指立方体的两个对角点。每个点由一个四维向量表示，通常最后一个是1.（不知道为什么要有四个，大神知道的给解答一下下）
    box_filter.setMax(Eigen::Vector4f(24, 10, 2, 1.0));
    box_filter.setNegative(false);//是保留立方体内的点而去除其他点，还是反之。false是将盒子内的点去除，默认为false
    box_filter.setInputCloud(cloud_after_Radius);//输入源
    // box_filter.setInputCloud(cloud_after_PassThrough);//输入源
    box_filter.filter(*cloud_after_PassThrough);

  //   pcl::PointXYZ minPt, maxPt;
  //   pcl::getMinMax3D(*cloud_after_PassThrough, minPt, maxPt);

  //   float leafsize = 0.05;
  //   float lx = maxPt.x - minPt.x;
	//   float ly = maxPt.y - minPt.y;
	//   float lz = maxPt.z - minPt.z;
	//   int nx = lx / leafsize + 1;
	//   int ny = ly / leafsize + 1;
	//   int nz = lz / leafsize + 1;
  //   std::cout<< "vector size"<<nx * ny * nz<<std::endl;
  //   std::vector<pcl::PointCloud<pcl::PointXYZ>> v(nx * ny * nz);

  //   for(auto &p: *cloud_after_PassThrough)
  //   {
  //       int ix = (p.x - minPt.x) / leafsize;
	// 	int iy = (p.y - minPt.y) / leafsize;
	// 	int iz = (p.z - minPt.z) / leafsize;
  //       v[ix + iy * nx + iz * nx * ny].push_back(p);
  //   }
  //       // for (int i = 0; i < v.size(); ++i)
  //   for(auto &p : v)
	// {
  //       int point_size = p.size();
	// 	if (point_size > 3)
	// 	{
	// 		Eigen::Vector4f centroid;
	// 		pcl::compute3DCentroid(p, centroid);
	// 		Eigen::MatrixXf points_near(3, point_size);
  //           for(int j = 0 ; j < point_size; j ++)
  //           {
  //               points_near(0,j) = p.points[j].x;
  //               points_near(1,j) = p.points[j].y;
  //               points_near(2,j) = p.points[j].z;
  //           }
  //           Eigen::Vector3f favec = ((points_near*(points_near.transpose())).inverse() * points_near).rowwise().sum();
            
  //           double shoot = favec.dot(Eigen::Vector3f(0,0,1)) / favec.norm();
  //           if(abs(shoot) < 0.7)
  //           {
  //               pcl_out->points.push_back(pcl::PointXYZ(centroid.x(), centroid.y(), centroid.z()));
  //           }
	// 	}
	// }
  //  SetMapTopicMsg(pcl_out, map_topic_msg);
   SetMapTopicMsg(cloud_after_Radius, map_topic_msg);

   pcl::visualization::PCLVisualizer viewer("cloud_viwer");
   pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZ> handle(cloud_after_Radius,"z");
   
   

    while(ros::ok())
    {
        map_topic_pub.publish(map_topic_msg);
        loop_rate.sleep();
        ros::spinOnce();

        viewer.addPointCloud<pcl::PointXYZ>(cloud_after_Radius,handle);
        viewer.spin();
    }

    

   return 0;
}


void PassThroughFilter(const double &thre_low, const double &thre_high, const bool &flag_in)
{
    /*方法一：直通滤波器对点云进行处理。*/
    pcl::PassThrough<pcl::PointXYZ> passthrough;
    passthrough.setInputCloud(pcd_cloud);//输入点云
    passthrough.setFilterFieldName("z");//对z轴进行操作
    passthrough.setFilterLimits(thre_low, thre_high);//设置直通滤波器操作范围
    passthrough.setFilterLimitsNegative(flag_in);//true表示保留范围外，false表示保留范围内
    passthrough.filter(*cloud_after_PassThrough);//执行滤波，过滤结果保存在 cloud_after_PassThrough
    std::cout << "直通滤波后点云数据点数：" << cloud_after_PassThrough->points.size() << std::endl;
}

void RadiusOutlierFilter(const pcl::PointCloud<pcl::PointXYZ>::Ptr& pcd_cloud0, const double &radius, const int &thre_count)
{
    pcl::RadiusOutlierRemoval<pcl::PointXYZ> radiusoutlier;  //创建滤波器

    radiusoutlier.setInputCloud(pcd_cloud0);    //设置输入点云
    radiusoutlier.setRadiusSearch(radius);     //设置半径为100的范围内找临近点
    radiusoutlier.setMinNeighborsInRadius(thre_count); //设置查询点的邻域点集数小于2的删除

    radiusoutlier.filter(*cloud_after_Radius);
    std::cout << "半径滤波后点云数据点数：" << cloud_after_Radius->points.size() << std::endl;
}



void SetMapTopicMsg(const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, nav_msgs::OccupancyGrid& msg)
{
  msg.header.seq = 0;
  msg.header.stamp = ros::Time::now();
  msg.header.frame_id = "map";

  msg.info.map_load_time = ros::Time::now();
  msg.info.resolution = map_resolution;

  double x_min, x_max, y_min, y_max;
  double z_max_grey_rate = 0.05;
  double z_min_grey_rate = 0.95;
  double k_line = (z_max_grey_rate - z_min_grey_rate) / (thre_z_max - thre_z_min);
  double b_line = (thre_z_max * z_min_grey_rate - thre_z_min * z_max_grey_rate) / (thre_z_max - thre_z_min);

  if(cloud->points.empty())
  {
    ROS_WARN("pcd is empty!\n");

    return;
  }

  for(int i = 0; i < cloud->points.size() - 1; i++)
  {
    if(i == 0)
    {
      x_min = x_max = cloud->points[i].x;
      y_min = y_max = cloud->points[i].y;
    }

    double x = cloud->points[i].x;
    double y = cloud->points[i].y;

    if(x < x_min) x_min = x;
    if(x > x_max) x_max = x;

    if(y < y_min) y_min = y;
    if(y > y_max) y_max = y;
  }

  msg.info.origin.position.x = x_min;
  msg.info.origin.position.y = y_min;
  msg.info.origin.position.z = 0.0;
  msg.info.origin.orientation.x = 0.0;
  msg.info.origin.orientation.y = 0.0;
  msg.info.origin.orientation.z = 0.0;
  msg.info.origin.orientation.w = 1.0;

  msg.info.width = int((x_max - x_min) / map_resolution) ;
  msg.info.height = int((y_max - y_min) / map_resolution);

  msg.data.resize(msg.info.width * msg.info.height);
  msg.data.assign(msg.info.width * msg.info.height, 0);

  ROS_INFO("data size = %ld\n", msg.data.size());

  for(int iter = 0; iter < cloud->points.size(); iter++)
  {
    int i = int((cloud->points[iter].x - x_min) / map_resolution);
    if(i < 1 || i >= msg.info.width) continue;

    int j = int((cloud->points[iter].y - y_min) / map_resolution);
    if(j < 1 || j >= msg.info.height - 1) continue;

    msg.data[i + j * msg.info.width] = 100;
    // msg.data[i+1 + j * msg.info.width] = 100;
    // msg.data[i-1 + j * msg.info.width] = 100;
    // msg.data[i + (j+1) * msg.info.width] = 100;
    // msg.data[i+1 + (j+1) * msg.info.width] = 100;
    // msg.data[i-1 + (j+1) * msg.info.width] = 100;
    // msg.data[i + (j-1) * msg.info.width] = 100;
    // msg.data[i+1 + (j-1) * msg.info.width] = 100;
    // msg.data[i-1 + (j-1) * msg.info.width] = 100;
  //  msg.data[i + j * msg.info.width] = int(255 * (cloud->points[iter].z * k_line + b_line)) % 255;
  }
}

