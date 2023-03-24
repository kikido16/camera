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
	 * \param cameraResolution ����ֱ���
	 */
	CameraCalib(vector<Mat>& calibImgs, Size cameraResolution);
	//CameraCalib(vector<Mat> &calibImgs, Size cameraResolution);

	/**
	 * \brief ��������
	 */
	~CameraCalib();

private:
	int CameraNum;											//������
	int CalibImg_total;										//�ܵı궨ͼ����
	int Calibtype;											//�궨����ѡ��
	bool CalibSuccess;										//�궨�Ƿ�ɹ�
	double ReproError;										//��ͶӰ���
	Size CameraResolution;									//����ֱ���
	vector<Mat> vec_CalibImage;								//����ı궨ͼ��
	vector<Eigen::MatrixXd> vec_Extrinsics_Zhang;			//�ŷ�����������
	vector<vector<Point3f>> vec2_Centers_World_Zhang;		//�ŷ�����Բ����������
	vector<vector<Point3f>> vec2_Centers_World;				//Բ����������
	vector<vector<Point2f>> vec2_Centers_Camera;			//������Բ����������
	Eigen::Matrix3d CameraMatrix_E;							//����ڲ�
	Mat CameraMatrix;										
	Eigen::VectorXd DistCoeffs_E;							//����ϵ��
	Mat DistCoeffs;
};