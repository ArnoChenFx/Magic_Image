#include "test.h"
//#include <QtWidgets/QApplication>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <QtDebug>
#include <string>
#include <omp.h>
#include <time.h>  
#include <Image_mix.h>
using namespace cv;
using namespace std;




void testCV()
{
	//读取图片（使用图片的绝对路径）
	Mat src = imread("F:/FFOutput/Download/Plant2.png");
	//显示图片
	imshow("Output", src);
	//显示灰度图
	Mat Gray;
	cvtColor(src, Gray, 6);
	imshow("Gray", Gray);

	//不加此语句图片会一闪而过
	waitKey(0);
}


void testCUDA() {
	Mat m1 = imread("F:/FFOutput/Download/Plant2.png");
	//cvtColor(m1, m1, COLOR_BGR2RGB);
	Mat m2 = imread("F:/FFOutput/Pictures/04.My_work/mountain.png");
	Mat m3 = imread("F:/FFOutput/Download/Compressed/RS/07.Car/B.png");
	Mat image1, image2,image3;

	//Mat<float> s;
	m1.convertTo(image1, CV_32FC3, 1 / 255.0);
	m2.convertTo(image2, CV_32FC3, 1 / 255.0);
	m3.convertTo(image3, CV_32FC3, 1 / 255.0);
	m1.release();
	m2.release();
	m3.release();

	

	//Mat image1 = imread("F:/FFOutput/Download/Plant2.png", IMREAD_UNCHANGED);
	//Mat image2 = imread("F:/FFOutput/Download/Plant2.png", IMREAD_UNCHANGED);
	//cuda::GpuMat DEVICEresult, DEVICEimage1,DEVICEimage2;
	//Mat result;
	//DEVICEimage1.upload(image1);
	//DEVICEimage2.upload(image2);

	//cuda::add(DEVICEimage1,DEVICEimage2,DEVICEresult);
	//DEVICEresult.download(result);
	
	//cvtColor(result, image1, 3);

	Image_add(image1,image2);
	//Image_gamma(image1, 1);

	imshow("CUDA ADD", image1);
	Vec3f rgb_f = image1.at<Vec3f>(100, 100);
	cout << rgb_f<<endl;//rgb_f.val[2]
	waitKey(0);
}


int main(int argc, char *argv[])
{
	//std::cout << "hello cv!" << std::endl;
	//qDebug() << "hello cv!!";
	testCUDA();
	
	//testKDtree();
	//system("pause");
	return 0;
}
