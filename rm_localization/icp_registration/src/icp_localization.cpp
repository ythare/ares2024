#include "../include/icp_localization.h"
#include <Eigen/src/Geometry/Quaternion.h>
#include <Eigen/src/Geometry/Transform.h>
#include <chrono>
#include <iostream>
#include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl_conversions/pcl_conversions.h>

#include <stdexcept>
#include <tf2/LinearMath/Quaternion.h>

