#include "cameracalib.h"
using namespace std;

CameraCalib::CameraCalib()
{
	CameraNum_c = 0;
	CalibType_c = 0;
	CalibImg_total_c = 0;
	CalibSuccess_c = false;
	CameraMatrix_E_c = Eigen::Matrix3d::Zero();
	CameraMatrix_c = Mat::zeros(3, 3, CV_64F);
	DistCoeffs_E_c = Eigen::Matrix<double, Eigen::Dynamic, 1>();
	DistCoeffs_c = Mat::zeros(7, 1, CV_64F);
	ReproError_c = 0;
}
CameraCalib::CameraCalib(vector<Mat>& calibImgs, const Size CameraResolution_p, const uint8 CalibType_p)
{
	//�ж����ڱ궨��ͼ������
	CHECK(calibImgs.size() > 3) << "pics not enough!";
	CalibImg_total_c = calibImgs.size();
	vec_CalibImage_c = calibImgs;
	CameraResolution_c = CameraResolution_p;
	CalibType_c = CalibType_p;
	CalibSuccess_c = false;
	CameraMatrix_E_c = Eigen::Matrix3d::Zero();
	CameraMatrix_c = Mat::zeros(3, 3, CV_64F);
	DistCoeffs_E_c = Eigen::Matrix<double, Eigen::Dynamic, 1>();
	DistCoeffs_c = Mat::zeros(7, 1, CV_64F);
	ReproError_c = 0;
}

CameraCalib::~CameraCalib()
{

}

bool CameraCalib::RunCalibration()
{	
	ExtractPicInfo();
	return true;
}

bool CameraCalib::ExtractPicInfo()
{	
	Size imgSize(0, 0);
	int  imgScale = 1;
	for (int imgindex = 0; imgindex < CalibImg_total_c; imgindex++)
	{	
		vector<Point3f> centersWorld;
		vector<Point2f> Centers_Camera;
		Mat img = vec_CalibImage_c[imgindex];
		if (img.rows < 1)
		{
			//LOG(ERROR) << "��" << to_string(imgIndex + 1).c_str() << "�ű궨ͼ�����ݴ��󣡣�rows < 1��";
			cout << "��" << to_string(imgindex + 1).c_str() << "�ű궨ͼ�����ݴ��󣡣�rows < 1��" << endl;
			return false;
		}
		if (imgSize.width == 0)
		{   //��ʼ��ͼ��ߴ�
			imgSize = img.size();
			if (imgSize.width >2048)
			{
				imgScale = cvRound(imgSize.width / 2048.0);
			}
		}
		else if (imgSize!= img.size() || img.size() != CameraResolution_c)
		{
			cout << "��" << to_string(imgindex + 1).c_str() << "�ű궨ͼ��ߴ粻ͳһ��" << endl;
			return false;
		}
		cout << "��" << to_string(imgindex + 1).c_str() << "��ͼ����ʼ" << endl;
		Mat resizedimg;
		if (imgScale > 1)
		{
			resize(img, resizedimg, Size(), 1, 1);
		}
		else
		{
			img.copyTo(resizedimg);
		}
		Mat image_incomplete, edge_incomplete;
		Mat image_incomplete0(3, 3, CV_8UC1, Scalar(0));
		bool const found = ExtractCenters(resizedimg, Centers_Camera, image_incomplete);
	}
	return true;
}

bool CameraCalib::ExtractCenters(const Mat& resizedimg_p, vector<Point2f>& Centers_Camera_p, Mat& image_incomplete)
{
	Mat blurimg, binaryimg, binary, edgeimg, morphimg, kernel, ROI;
	return true;
}

bool CameraCalib::FindSubpixContours(const Mat& resizedimg_p, Mat& contours)
{	
	// ����8������ģ��
	Mat kernels[KERNEL_SUM];
	int k = 0;
	kernels[k++] = (Mat_<float>(3, 3) << 1, 2, 1, 0, 0, 0, -1, -2, -1);	// 270��
	kernels[k++] = (Mat_<float>(3, 3) << 2, 1, 0, 1, 0, -1, 0, -1, -2);	// 315��
	kernels[k++] = (Mat_<float>(3, 3) << 1, 0, -1, 2, 0, -2, 1, 0, -1);	// 0��
	kernels[k++] = (Mat_<float>(3, 3) << 0, -1, -2, 1, 0, -1, 2, 1, 0);	// 45��
	flip(kernels[0], kernels[k++], 0);									// 90��
	kernels[k++] = (Mat_<float>(3, 3) << -2, -1, 0, -1, 0, 1, 0, 1, 2);	// 135��
	flip(kernels[2], kernels[k++], 1);									// 180��
	kernels[k++] = (Mat_<float>(3, 3) << 0, 1, 2, -1, 0, 1, -2, -1, 0);	// 225��

	// ����ģ���������ݶ�ͼ��
	Mat gradients[KERNEL_SUM];
	for (k = 0; k < KERNEL_SUM; k++)
	{
		filter2D(resizedimg_p, gradients[k], CV_16S, kernels[k]);
	}

	// �ݶȿ����Ǹ�ֵ, ���һ��������ת���ſ���������ʾ
	Mat imgnormal;
	normalize(gradients[0], imgnormal, 0, 255, NORM_MINMAX);
	imgnormal.convertTo(imgnormal, CV_8UC1);

	// �Ƕ��б�
	const short angle_list[] = { 270, 315, 0, 45, 90, 135, 180, 225 };

	// �ܷ�ֵ����
	Mat amplitude(resizedimg_p.rows, resizedimg_p.cols, CV_16SC1, Scalar::all(0));

	// �ǶȾ���, �����ʼ���� -64 ֻ��Ϊ�˹�һ��֮������ʾ�Ƕ� 0
	Mat angle(resizedimg_p.rows, resizedimg_p.cols, CV_16SC1, Scalar::all(-64));
	for (int r = 0; r < resizedimg_p.rows; r++)
	{
		short* pAmp = amplitude.ptr<short>(r);
		short* pAng = angle.ptr<short>(r);

		short* pGrad[KERNEL_SUM] = { nullptr };

		for (int i = 0; i < KERNEL_SUM; i++)
		{
			pGrad[i] = gradients[i].ptr<short>(r);
		}

		for (int c = 0; c < resizedimg_p.cols; c++)
		{
			// �ҳ����ֵ
			for (int i = 0; i < KERNEL_SUM; i++)
			{
				if (pAmp[c] < pGrad[i][c])
				{
					pAmp[c] = pGrad[i][c];
					pAng[c] = angle_list[i];
				}
			}
		}
	}

	return true;
}

double CameraCalib::GetDistance(Point pt1, Point pt2)
{
	double distance = sqrtf(powf((pt1.x - pt2.x), 2) + powf((pt1.y - pt2.y), 2));
	return distance;
}