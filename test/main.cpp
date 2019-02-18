#include "test.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <QtDebug>

using namespace cv;

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
	Mat image1 = imread("F:/FFOutput/Download/Plant2.png");
	Mat image2 = imread("F:/FFOutput/Download/Plant2.png");
	cuda::GpuMat DEVICEresult, DEVICEimage1,DEVICEimage2;
	Mat result;
	DEVICEimage1.upload(image1);
	DEVICEimage2.upload(image2);

	cuda::add(DEVICEimage1,DEVICEimage2,DEVICEresult);
	DEVICEresult.download(result);
	
	cvtColor(result, image1, 3);
	//imshow("CUDA ADD", result);
	Vec3f rgb_f = image1.at<Vec3b>(100, 100);
	qDebug() << rgb_f.val[2];
	//waitKey(0);
	
}

int main(int argc, char *argv[])
{
	std::cout << "hello cv!" << std::endl;
	qDebug() << "hello cv!!";
	//testCUDA();
	//system("pause");
	return 0;
}
