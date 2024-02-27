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
// 导航目标点
std::vector<Point2D> tarPoints = {
    {6.21, -4.09, 1.0},
    {7.21, -4.09, 1.0},
    {1.0, 2.0, 1.0},
    {1.0, 2.0, 1.0},
    {1.0, 2.0, 1.0},
    {1.0, 2.0, 1.0},
};


// #define serial_enable   //串口开关
uint8_t Targoal_without_serial = 0;

#define two_point_patrol  //两点巡逻，关闭则由下位机控制目标点

