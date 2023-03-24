#include "head.h"
#include "cameracalib.h"
#include <gflags/gflags.h>

int main()
{
	CameraCalib cameracalib;
	vector<String> paths;
	vector<Mat> calibimgs;
	uint8 CalibType = 1;
	uint8 InputImgNum = 5;
	uint8 CameraNum = 1;
	Size resolution = Size(2448,2048);
	string path1 = "resources\\";
	string path2 = ".bmp";
	for (int i = 0; i < InputImgNum; i++)
	{
		string path = path1 + to_string(CameraNum).c_str()+to_string(i + 1).c_str() + path2;
		cout << path << endl;
		Mat img = imread(path, IMREAD_GRAYSCALE);
		calibimgs.push_back(img);
	}
	cameracalib = CameraCalib(calibimgs, resolution, CalibType);
	cameracalib.RunCalibration();

	waitKey(0);
}