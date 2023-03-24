#pragma once

#define GOOGLE_GLOG_DLL_DECL
#define GLOG_NO_ABBREVIATED_SEVERITIES

#include <opencv2/opencv.hpp>
#include <iostream>
#include <Eigen\Dense>
#include <math.h> 
#include <Windows.h>
#include <ceres/ceres.h>


#define pi acos(-1)
#define KERNEL_SUM 8


typedef int8_t			sint8;		// 有符号8位整数
typedef uint8_t			uint8;		// 无符号8位整数
typedef int16_t			sint16;		// 有符号16位整数
typedef uint16_t		uint16;		// 无符号16位整数
typedef int32_t			sint32;		// 有符号32位整数
typedef uint32_t		uint32;		// 无符号32位整数
typedef int64_t			sint64;		// 有符号64位整数
typedef uint64_t		uint64;		// 无符号64位整数

/** \brief cvMat
	CV_8U	8位无符号整数			uchar
	CV_8S	8位有符号整数			char
	CV_16U	16位无符号整数			ushort
	CV_16S	16位有符号整数			short
	CV_32U	32位无符号整数			uint
	CV_32S	32位有符号整数			int
	CV_32F	32位浮点数				float
	CV_64F	64位浮点数				double
*/

using namespace std;
using namespace cv;
