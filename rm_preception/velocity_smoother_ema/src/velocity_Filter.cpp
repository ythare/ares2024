#include <Eigen/Dense>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <vector>

// 卡尔曼滤波
// 卡尔曼滤波器类
// 卡尔曼滤波器类
// class KalmanFilter {
// public:
//     KalmanFilter(){};
//     void init(double dt) {
//         // 状态转移矩阵 A
//         A << 1, dt, 
//              0, 1;
//         // 状态协方差矩阵 P
//         P << 1, 0, 
//              0, 1;
//         //输入矩阵
//         B << pow(dt, 2)/2, dt;
        
//         // 测量矩阵 H
//         H << 1, 0,
//              0, 1;
//         // 测量噪声协方差矩阵 R
//         R << 0.1, 0,
//              0, 0.1;
//         // 状态噪声协方差矩阵 Q
//         Q << pow(dt, 4) / 4.0, pow(dt, 3) / 2.0, 
//              pow(dt, 3) / 2.0, pow(dt, 2);
//         // 初始状态估计
//         x << 0, 0;
//     }

//     double filter(double position, double vel) {
//         // 预测
//         x_hat = A * x + u * B;
//         P_hat = A * P * A.transpose() + Q;
//         // 更新
//         K = P_hat * H.transpose() * (H * P_hat * H.transpose() + R).inverse();
//         Measure << position, vel;
//         x = x_hat + K * (Measure - H * x_hat);
//         P = (Eigen::Matrix2d::Identity() - K * H) * P_hat;
//         return x(1);
//     }

// private:
//     double dt;          // 采样时间间隔
//     double u = 0.01;       //输入向量
//     Eigen::Matrix2d A;         // 状态转移矩阵
//     Eigen::Matrix2d P;         // 状态协方差矩阵
//     Eigen::Matrix<double, 2, 1> B;  // 测量矩阵
//     Eigen::Matrix2d H;  // 测量矩阵
//     Eigen::Matrix2d R;  // 测量噪声协方差矩阵
//     Eigen::Matrix2d Q;         // 状态噪声协方差矩阵
//     Eigen::Vector2d x;         // 状态估计
//     Eigen::Vector2d x_hat;     // 预测状态估计
//     Eigen::Matrix2d P_hat;     // 预测状态协方差矩阵
//     Eigen::Matrix<double, 2, 1> K;  // 卡尔曼增益矩阵
//     Eigen::Vector2d Measure;  //测量结果矩阵
// };

// 滑动窗口滤波
// 滑动平均滤波器类
class MovingAverageFilter {
public:
    MovingAverageFilter(){};
    void init(int size) {
        m_size = size;
        m_sum = 0;
        m_data.reserve(size);
    }

    double filter(double value) {
        if (m_data.size() == m_size) {
            m_sum -= m_data.front();
            m_data.erase(m_data.begin());

        }
        m_data.push_back(value);
        
        m_sum += value;
        if (value == 0 && value_last == 0)  return 0;

        value_last = value;
        return m_sum / m_data.size();

    }

private:
    int m_size;                // 滤波器窗口大小
    std::vector<double> m_data;     // 数据存储数组
    double m_sum;              // 数据累加和
    double value_last = 0;
};

// 速度滤波类
class VelFilter {
    private: 
        ros::NodeHandle nh_;

        ros::Subscriber subSpeed = nh_.subscribe<geometry_msgs::Twist> ("/cmd_vel", 5, &VelFilter::speedHandler, this);
        ros::Publisher pubSpeed = nh_.advertise<geometry_msgs::Twist> ("/cmd_vel_", 5);
        geometry_msgs::Twist now_vel_;
        MovingAverageFilter filter_x;
        MovingAverageFilter filter_y;
        MovingAverageFilter filter_z;
        // KalmanFilter kal_filter_x;
        // KalmanFilter kal_filter_y;
        // KalmanFilter kal_filter_z;

    public:
        VelFilter()
        {
            // 创建滤波器
            filter_x.init(5);
            filter_y.init(5);
            filter_z.init(3);
            // kal_filter_x.init(0.01);
            // kal_filter_y.init(0.01);
            // kal_filter_z.init(0.01);
        }
        void speedHandler(const geometry_msgs::Twist::ConstPtr& speed)
        {
            now_vel_.linear.x = filter_x.filter(speed->linear.x);
            now_vel_.linear.y = filter_y.filter(speed->linear.y);
            now_vel_.angular.z = filter_z.filter(speed->angular.z);
            // now_vel_.linear.x = kal_filter_x.filter(speed->linear.x, speed->angular.x);
            // now_vel_.linear.y = kal_filter_y.filter(speed->linear.y, speed->angular.x);
            // now_vel_.angular.z = kal_filter_z.filter(speed->angular.z);
            // now_vel_.angular.z = speed->angular.z;
            pubSpeed.publish(now_vel_);
        }

}; 




int main(int argc, char** argv)
{
  ros::init(argc, argv, "vel_filter");

  VelFilter velfilter;
  ros::Rate rate(100);
  bool status = ros::ok();
  while (status) {
    ros::spinOnce();
  }
}
