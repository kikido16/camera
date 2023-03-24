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
	 * \param CameraResolution_p 相机分辨率
	 * \param CalibType_p 标定方法
	 */
	CameraCalib(vector<Mat>& calibImgs, const Size CameraResolution_p,const uint8 CalibType_p);


	/**
	 * \brief 析构函数
	 */
	~CameraCalib();

	/**
	* \brief 运行相机标定程序
	* \return 若标定成功，返回true，否则返回false
	 */
	bool RunCalibration();

private:
	/**
	* 获取两点距离
	*/
	double GetDistance(Point pt1, Point pt2);

	/**
	 * \brief 提取图像信息
	 * \return 若全部提取成功，返回true，否则返回false
	 */
	bool ExtractPicInfo();

	/**
	* \brief 处理图像，获得图像的圆心亚像素坐标
	* \return 若全部处理成功，返回true，否则返回false
	*/
	bool ExtractCenters(const Mat& resizedImg, vector<Point2f>& Centers_Camera_p, Mat& image_incomplete);

	/**
	* \brief 处理图像，获得图像的圆心亚像素坐标
	* \return 若全部处理成功，返回true，否则返回false
	*/
	bool FindSubpixContours(const Mat& resizedImg, Mat& contours);



	uint8 CameraNum_c;											//相机编号
	int CalibImg_total_c;										//总的标定图像数
	uint8 CalibType_c;											//标定方法选择
	bool CalibSuccess_c;										//标定是否成功
	double ReproError_c;										//重投影误差
	Size CameraResolution_c;									//相机分辨率
	vector<Mat> vec_CalibImage_c;								//输入的标定图像
	vector<Eigen::MatrixXd> vec_Extrinsics_Zhang_c;			//张方法的相机外参
	vector<vector<Point3f>> vec2_Centers_World_Zhang_c;		//张方法的圆心世界坐标
	vector<vector<Point3f>> vec2_Centers_World_c;				//圆心世界坐标
	vector<vector<Point2f>> vec2_Centers_Camera_c;			//检测出的圆心像素坐标
	Eigen::Matrix3d CameraMatrix_E_c;							//相机内参
	Mat CameraMatrix_c;										
	Eigen::VectorXd DistCoeffs_E_c;							//畸变系数
	Mat DistCoeffs_c;
};