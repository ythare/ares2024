#include "../include/icp_localization.h"

pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in_(new pcl::PointCloud<pcl::PointXYZ>);

namespace icp
{
    IcpNode::IcpNode() : rough_iter_(10), refine_iter_(5), first_scan_(true)
    {
        is_ready_ = false;
        ROS_INFO_STREAM("\033[1;32m----> IcpNode started....\033[0m");

        double rough_leaf_size = 0.00;
        double refine_leaf_size = 0.00;
        nh.param<double>("rough_leaf_size", rough_leaf_size, 0.4);
        nh.param<double>("refine_leaf_size", refine_leaf_size, 0.1);
        nh.param<std::string>("pcd_path", pcd_path_, "/home/ythare/ws_livox/src/rm_bringup/PCD/RMUC3.pcd");
        ROS_INFO("*** file_path = %s ***\n", pcd_path_.c_str());

        voxel_rough_filter_.setLeafSize(rough_leaf_size, rough_leaf_size, rough_leaf_size);
        voxel_refine_filter_.setLeafSize(refine_leaf_size, refine_leaf_size, refine_leaf_size);

        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
        if (pcl::io::loadPCDFile<pcl::PointXYZ>(pcd_path_, *cloud) == -1)
        {
            ROS_ERROR("Couldn't read file");
        }
        std::cout << "pcl初始点云数据点数:" << cloud->points.size() << std::endl;
        voxel_refine_filter_.setInputCloud(cloud);
        voxel_refine_filter_.filter(*cloud);

        // Add normal to the pointcloud
        refine_map_ = addNorm(cloud);
        pcl::PointCloud<pcl::PointXYZ>::Ptr point_rough(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::PointCloud<pcl::PointXYZ>::Ptr filterd_point_rough(new pcl::PointCloud<pcl::PointXYZ>); //滤波后
        pcl::copyPointCloud(*refine_map_, *point_rough);
        voxel_rough_filter_.setInputCloud(point_rough);
        voxel_rough_filter_.filter(*filterd_point_rough);
        rough_map_ = addNorm(filterd_point_rough);

        icp_rough_.setMaximumIterations(rough_iter_);  //滤波后
        icp_rough_.setInputTarget(rough_map_);

        icp_refine_.setMaximumIterations(refine_iter_);  //滤波前
        icp_refine_.setInputTarget(refine_map_);
        std::cout << "------>pcd point size" << "before filter"<<refine_map_->points.size() << " ,filtered   "
                  << rough_map_->points.size()<< std::endl;

        //load Parameters
        nh.param<std::string>("map_frame_id", map_frame_id_, "map");
        nh.param<std::string>("odom_frame_id", odom_frame_id_, "odom");
        nh.param<std::string>("laser_frame_id", laser_frame_id_, "livox_frame");
        nh.param<double>("thresh", thresh_, 0.15);
        nh.param<double>("xy_offset", xy_offset_, 2.0);
        nh.param<double>("yaw_offset", yaw_offset_, 30 * M_PI / 180);
        nh.param<double>("yaw_resolution", yaw_resolution_, 10* M_PI / 180);
        nh.param<std::vector<double>>("initial_pose_vec", initial_pose_vec, std::vector<double>());
        std::vector<double> initial_pose_vec = std::vector<double>{0, 0, 0, 0, 0, 0};
        nh.param<std::string>("pointcloud_topic", pointcloud_topic, "/livox/lidar/pointcloud2");

        pointcloud_sub_ = nh.subscribe(pointcloud_topic.c_str(), 1, &IcpNode::pointcloudCallback, this);
        initial_pose_sub_ = nh.subscribe("/initialpose", 10, &IcpNode::initialPoseCallback, this);
        
        try
        {
            initial_pose_.position.x = initial_pose_vec.at(0);
            initial_pose_.position.y = initial_pose_vec.at(1);
            initial_pose_.position.z = initial_pose_vec.at(2);
            tf2::Quaternion q;
            q.setRPY(initial_pose_vec.at(3), initial_pose_vec.at(4),
                     initial_pose_vec.at(5));
        }
        catch (const std::out_of_range &ex)
        {
            ROS_ERROR("initial_pose is not a vector with 6 elements, what():%s", ex.what());
        }
          // Set up the transform broadcaster

        tf_publisher_thread_ = std::thread(&IcpNode::pub_tf_thread, this);
    }
    IcpNode::~IcpNode(){}

    void IcpNode::pub_tf_thread()
    {
        ros::Rate rate(100);
        while (ros::ok())
        {
            if(is_ready_)
            {
                // std::cout<<"----------Publishing tf"<< map_to_odom_.transform.translation.x<<" "
                //          <<map_to_odom_.transform.translation.y<<" "
                //          <<map_to_odom_.transform.translation.z<<std::endl;
                map_to_odom_.header.stamp = ros::Time::now();
                map_to_odom_.header.frame_id = map_frame_id_;
                map_to_odom_.child_frame_id = odom_frame_id_;
                tf_broadcaster_.sendTransform(map_to_odom_);
            }
        rate.sleep();
        }
        
    }

    IcpNode::PointCloudXYZN::Ptr IcpNode::addNorm(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
    {
        pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
        pcl::search::KdTree<pcl::PointXYZ>::Ptr searchTree(
            new pcl::search::KdTree<pcl::PointXYZ>);
        searchTree->setInputCloud(cloud);

        pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> normalEstimator;
        normalEstimator.setInputCloud(cloud);
        normalEstimator.setSearchMethod(searchTree);
        normalEstimator.setKSearch(15);
        normalEstimator.compute(*normals);
        PointCloudXYZN::Ptr out(new PointCloudXYZN);
        pcl::concatenateFields(*cloud, *normals, *out);
        return out;
    }
    void IcpNode::pointcloudCallback(const sensor_msgs::PointCloud2::ConstPtr msg)
    {
        
        pcl::fromROSMsg(*msg, *cloud_in_);
        if (first_scan_)
        {
            geometry_msgs::PoseWithCovarianceStamped pose_msg;
            boost::shared_ptr<geometry_msgs::PoseWithCovarianceStamped> pose_msg_ptr = boost::make_shared<geometry_msgs::PoseWithCovarianceStamped>(pose_msg);
            pose_msg_ptr->header = msg->header;
            pose_msg_ptr->pose.pose = initial_pose_;
            initialPoseCallback(pose_msg_ptr);
            first_scan_ = false;
        }
    }

    void IcpNode::initialPoseCallback(const geometry_msgs::PoseWithCovarianceStampedConstPtr msg)
    {
        // Set the initial pose
        Eigen::Vector3d pos(msg->pose.pose.position.x, msg->pose.pose.position.y,
                            msg->pose.pose.position.z);
        Eigen::Quaterniond q(
            msg->pose.pose.orientation.w, msg->pose.pose.orientation.x,
            msg->pose.pose.orientation.y, msg->pose.pose.orientation.z);
        Eigen::Matrix4d initial_guess;
        initial_guess.block<3, 3>(0, 0) = q.toRotationMatrix();
        initial_guess.block<3, 1>(0, 3) = pos;
        initial_guess(3, 3) = 1;

        // Align the pointcloud
        ROS_INFO("Aligning the pointcloud");
        Eigen::Matrix4d map_to_laser = multiAlignSync(cloud_in_, initial_guess);
        // Eigen::Matrix4d result = align(cloud_in_, initial_guess);
        if (!success_)
        {
            map_to_laser = initial_guess;
            ROS_ERROR("ICP-failed");
        }
        // Eigen::Isometry3d laser_to_odom;
        Eigen::Matrix4d laser_to_odom = Eigen::Matrix4d::Identity();
        try
        {
            // Get odom to laser transform
            tf2_ros::TransformListener tfListener(tfBuffer);
            geometry_msgs::TransformStamped transform;
            if(tfBuffer.canTransform(laser_frame_id_, odom_frame_id_, ros::Time(0), ros::Duration(0.5)))
            transform = tfBuffer.lookupTransform( laser_frame_id_, odom_frame_id_, ros::Time::now(), ros::Duration(1));

            Eigen::Vector3d t(transform.transform.translation.x,
                              transform.transform.translation.y,
                              transform.transform.translation.z);
            Eigen::Quaterniond q(
                transform.transform.rotation.w, transform.transform.rotation.x,
                transform.transform.rotation.y, transform.transform.rotation.z);
            // laser_to_odom.prerotate(q);
            // laser_to_odom.translate(t);
            laser_to_odom.block<3, 3>(0, 0) = q.toRotationMatrix();
            laser_to_odom.block<3, 1>(0, 3) = t;
        }
        catch (tf2::TransformException &ex)
        {
            std::lock_guard<std::mutex> lock(mutex_);
            ROS_WARN("tf error::: %s", ex.what());
            is_ready_ = false;
            return;
        }
        Eigen::Matrix4d result = map_to_laser * laser_to_odom.matrix().cast<double>();
        {
            std::lock_guard<std::mutex> lock(mutex_);
            map_to_odom_.transform.translation.x = result(0, 3);
            map_to_odom_.transform.translation.y = result(1, 3);
            map_to_odom_.transform.translation.z = result(2, 3);

            Eigen::Matrix3d rotation = result.block<3, 3>(0, 0);
            q = Eigen::Quaterniond(rotation);

            map_to_odom_.transform.rotation.w = q.w();
            map_to_odom_.transform.rotation.x = q.x();
            map_to_odom_.transform.rotation.y = q.y();
            map_to_odom_.transform.rotation.z = q.z();
            is_ready_ = true;
        }
    }

    Eigen::Matrix4d IcpNode::multiAlignSync(PointCloudXYZ::Ptr source, const Eigen::Matrix4d &init_guess)
    {
        static auto rotate2rpy = [](Eigen::Matrix3d &rot) -> Eigen::Vector3d
        {
            double roll = std::atan2(rot(2, 1), rot(2, 2));
            double pitch = asin(-rot(2, 0));
            double yaw = std::atan2(rot(1, 0), rot(0, 0));
            return Eigen::Vector3d(roll, pitch, yaw);
        };

        success_ = false;
        Eigen::Vector3d xyz = init_guess.block<3, 1>(0, 3);
        Eigen::Matrix3d rotation = init_guess.block<3, 3>(0, 0);
        Eigen::Vector3d rpy = rotate2rpy(rotation);
        Eigen::AngleAxisf rollAngle(rpy(0), Eigen::Vector3f::UnitX());
        Eigen::AngleAxisf pitchAngle(rpy(1), Eigen::Vector3f::UnitY());
        std::vector<Eigen::Matrix4f> candidates;
        Eigen::Matrix4f temp_pose;
        std::cout<<"******>>initial guess:" << xyz(0)<<" "<<xyz(1)<<" "<< xyz(2)
                << " "<< rpy(0)<< ""  << rpy(1)<< " " << rpy(2)<<std::endl;

        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                for (int k = -yaw_offset_; k <= yaw_offset_; k++)
                {
                    Eigen::Vector3f pos(xyz(0) + i * xy_offset_, xyz(1) + j * xy_offset_,
                                        xyz(2));
                    Eigen::AngleAxisf yawAngle(rpy(2) + k * yaw_resolution_,
                                               Eigen::Vector3f::UnitZ());
                    temp_pose.setIdentity();
                    temp_pose.block<3, 3>(0, 0) =
                        (rollAngle * pitchAngle * yawAngle).toRotationMatrix();
                    temp_pose.block<3, 1>(0, 3) = pos;
                    candidates.push_back(temp_pose);
                }
            }
        }
        pcl::PointCloud<pcl::PointXYZ>::Ptr rough_source(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::PointCloud<pcl::PointXYZ>::Ptr refine_source(new pcl::PointCloud<pcl::PointXYZ>);

        voxel_rough_filter_.setInputCloud(source);
        voxel_rough_filter_.filter(*rough_source);
        voxel_refine_filter_.setInputCloud(source);
        voxel_refine_filter_.filter(*refine_source);

        PointCloudXYZN::Ptr rough_source_norm = addNorm(rough_source);
        PointCloudXYZN::Ptr refine_source_norm = addNorm(refine_source);
        PointCloudXYZN::Ptr align_point(new PointCloudXYZN);

        Eigen::Matrix4f best_rough_transform;
        double best_rough_score = 10.0;
        bool rough_converge = false;
        auto tic = std::chrono::system_clock::now();
        for (Eigen::Matrix4f &init_pose : candidates)
        {
            icp_rough_.setInputSource(rough_source_norm);
            icp_rough_.align(*align_point, init_pose);
            if (!icp_rough_.hasConverged())
                continue;
            double rough_score = icp_rough_.getFitnessScore();
            if (rough_score > 2 * thresh_)
                continue;
            if (rough_score < best_rough_score)
            {
                best_rough_score = rough_score;
                rough_converge = true;
                best_rough_transform = icp_rough_.getFinalTransformation();
            }
        }

        if (!rough_converge)
            return Eigen::Matrix4d::Zero();

        icp_refine_.setInputSource(refine_source_norm);
        icp_refine_.align(*align_point, best_rough_transform);
        score_ = icp_refine_.getFitnessScore();

        if (!icp_refine_.hasConverged())
            return Eigen::Matrix4d::Zero();
        if (score_ > thresh_)
            return Eigen::Matrix4d::Zero();
        success_ = true;
        auto toc = std::chrono::system_clock::now();
        std::chrono::duration<double> duration = toc - tic;

        std::cout<<"-------->align used: " << duration.count()*1000 <<std::endl;
        std::cout<<"------->score: " << score_ <<std::endl;

        return icp_refine_.getFinalTransformation().cast<double>();
    }
} // namespace icp

int main (int argc, char** argv)
{
  // ROS init
  ros::init (argc, argv, "icp_localize__node");

  icp::IcpNode IcpNode;
  ros::spin ();
  return (0);
}