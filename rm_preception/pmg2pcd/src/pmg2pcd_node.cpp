#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <opencv2/opencv.hpp>

int main()
{
    // 读取PGM文件
    cv::Mat pgmImage = cv::imread("/home/ares_yt/ws_livox/src/rm_navigation/map/map1231.pgm", cv::IMREAD_GRAYSCALE);

    // 创建PCL点云对象
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

    // 将PGM图像转换为点云数据
    for (int row = 0; row < pgmImage.rows; ++row)
    {
        for (int col = 0; col < pgmImage.cols; ++col)
        {
            float intensity = static_cast<float>(pgmImage.at<uchar>(row, col));
            pcl::PointXYZ point;
            point.x = static_cast<float>(col);
            point.y = static_cast<float>(row);
            point.z = intensity;
            cloud->push_back(point);
        }
    }

    // 设置点云参数（可选）
    cloud->width = pgmImage.cols;
    cloud->height = pgmImage.rows;
    cloud->is_dense = true;

    // 保存点云数据为PCD文件
    pcl::io::savePCDFileASCII("/home/ares_yt/ws_livox/src/pmg2pcd/pcd/map.pcd", *cloud);
    std::cout << "PCD file saved." << std::endl;

    return 0;
}
