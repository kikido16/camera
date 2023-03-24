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


typedef int8_t			sint8;		// �з���8λ����
typedef uint8_t			uint8;		// �޷���8λ����
typedef int16_t			sint16;		// �з���16λ����
typedef uint16_t		uint16;		// �޷���16λ����
typedef int32_t			sint32;		// �з���32λ����
typedef uint32_t		uint32;		// �޷���32λ����
typedef int64_t			sint64;		// �з���64λ����
typedef uint64_t		uint64;		// �޷���64λ����

/** \brief cvMat
	CV_8U	8λ�޷�������			uchar
	CV_8S	8λ�з�������			char
	CV_16U	16λ�޷�������			ushort
	CV_16S	16λ�з�������			short
	CV_32U	32λ�޷�������			uint
	CV_32S	32λ�з�������			int
	CV_32F	32λ������				float
	CV_64F	64λ������				double
*/

using namespace std;
using namespace cv;
