#pragma once
#include "head.h"

class CameraCalib
{
public:

	/**
	 * \brief Ĭ�Ϲ��캯��
	 */
	CameraCalib();

	/**
	 * \brief ���캯��
	 * \param calibImgs ��������궨�ı궨��ͼ��
	 * \param CameraResolution_p ����ֱ���
	 * \param CalibType_p �궨����
	 */
	CameraCalib(vector<Mat>& calibImgs, const Size CameraResolution_p,const uint8 CalibType_p);


	/**
	 * \brief ��������
	 */
	~CameraCalib();

	/**
	* \brief ��������궨����
	* \return ���궨�ɹ�������true�����򷵻�false
	 */
	bool RunCalibration();

private:
	/**
	* ��ȡ�������
	*/
	double GetDistance(Point pt1, Point pt2);

	/**
	 * \brief ��ȡͼ����Ϣ
	 * \return ��ȫ����ȡ�ɹ�������true�����򷵻�false
	 */
	bool ExtractPicInfo();

	/**
	* \brief ����ͼ�񣬻��ͼ���Բ������������
	* \return ��ȫ������ɹ�������true�����򷵻�false
	*/
	bool ExtractCenters(const Mat& resizedImg, vector<Point2f>& Centers_Camera_p, Mat& image_incomplete);

	/**
	* \brief ����ͼ�񣬻��ͼ���Բ������������
	* \return ��ȫ������ɹ�������true�����򷵻�false
	*/
	bool FindSubpixContours(const Mat& resizedImg, Mat& contours);



	uint8 CameraNum_c;											//������
	int CalibImg_total_c;										//�ܵı궨ͼ����
	uint8 CalibType_c;											//�궨����ѡ��
	bool CalibSuccess_c;										//�궨�Ƿ�ɹ�
	double ReproError_c;										//��ͶӰ���
	Size CameraResolution_c;									//����ֱ���
	vector<Mat> vec_CalibImage_c;								//����ı궨ͼ��
	vector<Eigen::MatrixXd> vec_Extrinsics_Zhang_c;			//�ŷ�����������
	vector<vector<Point3f>> vec2_Centers_World_Zhang_c;		//�ŷ�����Բ����������
	vector<vector<Point3f>> vec2_Centers_World_c;				//Բ����������
	vector<vector<Point2f>> vec2_Centers_Camera_c;			//������Բ����������
	Eigen::Matrix3d CameraMatrix_E_c;							//����ڲ�
	Mat CameraMatrix_c;										
	Eigen::VectorXd DistCoeffs_E_c;							//����ϵ��
	Mat DistCoeffs_c;
};