#pragma once
#include "head.h"

class CameraCalib
{
public:

	/**
	 * \brief 默认构造函数
	 */
	CameraCalib();

	/**
	 * \brief 构造函数
	 * \param calibImgs 用于相机标定的标定板图像
	 * \param cameraResolution 相机分辨率
	 */
	CameraCalib(vector<Mat>& calibImgs, Size cameraResolution);
	//CameraCalib(vector<Mat> &calibImgs, Size cameraResolution);

	/**
	 * \brief 析构函数
	 */
	~CameraCalib();

private:
	int CameraNum;											//相机编号
	int CalibImg_total;										//总的标定图像数
	int Calibtype;											//标定方法选择
	bool CalibSuccess;										//标定是否成功
	double ReproError;										//重投影误差
	Size CameraResolution;									//相机分辨率
	vector<Mat> vec_CalibImage;								//输入的标定图像
	vector<Eigen::MatrixXd> vec_Extrinsics_Zhang;			//张方法的相机外参
	vector<vector<Point3f>> vec2_Centers_World_Zhang;		//张方法的圆心世界坐标
	vector<vector<Point3f>> vec2_Centers_World;				//圆心世界坐标
	vector<vector<Point2f>> vec2_Centers_Camera;			//检测出的圆心像素坐标
	Eigen::Matrix3d CameraMatrix_E;							//相机内参
	Mat CameraMatrix;										
	Eigen::VectorXd DistCoeffs_E;							//畸变系数
	Mat DistCoeffs;
};