#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include <iostream>
#include <vector>

struct Point2D {
    double x;
    double y;
    double w;
};
struct Turn_angle {
    double angle1;
    double angle2;
    double angle3;
    double angle4;
};

// 导航目标点
std::vector<Point2D> tarPoints = {
    {0.145, -0.077, 1.0}, //
    {1.151, -2.889, 1.0},  //右侧挡板处 1
    {1.699, 2.620, 1.0}, //左侧挡板处  2
    {-1.575, 3.242, 1.0}, //补给区   3
    {3.255, -0.688, 1.0}, //增益区  4
    {3.817, -3.272, 1.0}, //右侧深入  5
    {0.145, -0.077, 1.0}, //原点  6
    {1.0, 2.0, 1.0},
};
#define pi  3.1415
float Tar_angle_mat[4][4] = {
           /*原点   右侧挡板   左侧挡板  补给区*/  //逆时针为+  左侧为+  右侧为-
/*原点*/    { 0,      -pi/4,   pi/4,   pi},
/*右侧*/    { pi/2,      0,   pi/4,   pi/2},
/*左侧*/    { -pi/2 ,  -pi/4,   0,    pi},
/*补给区*/  { -pi/4,      -pi/4,   0,   0},
};

#define serial_enable   //串口开关 调试时屏蔽
uint8_t Targoal_without_serial = 0;

#define two_point_patrol  //两点巡逻，关闭则由下位机控制目标点

