#include "cameracalib.h"
using namespace std;

CameraCalib::CameraCalib()
{
	CameraNum = 0;
	Calibtype = 0;
	CalibImg_total = 0;
	CalibSuccess = false;
	CameraMatrix_E = Eigen::Matrix3d::Zero();
	CameraMatrix = Mat::zeros(3, 3, CV_64F);
	DistCoeffs_E = Eigen::Matrix<double, Eigen::Dynamic, 1>();
	DistCoeffs = Mat::zeros(7, 1, CV_64F);
	ReproError = 0;
}

CameraCalib::~CameraCalib()
{

}