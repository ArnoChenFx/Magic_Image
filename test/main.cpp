#include "test.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <QtDebug>

#include <my_node1.h>
#include <my_node2.h>
#include <string>

using namespace cv;

void testCV()
{
	//��ȡͼƬ��ʹ��ͼƬ�ľ���·����
	Mat src = imread("F:/FFOutput/Download/Plant2.png");
	//��ʾͼƬ
	imshow("Output", src);
	//��ʾ�Ҷ�ͼ
	Mat Gray;
	cvtColor(src, Gray, 6);
	imshow("Gray", Gray);

	//���Ӵ����ͼƬ��һ������
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


void test_Fac() {
	my_node1 *n1 = new my_node1;
	qDebug() << n1->name;

	auto *n2 = static_cast<my_node1*>(FACTORY_NODE::produce("my_node1"));
	qDebug() << n2->name;

	string aa = "my_node2";
	auto n3 = factory::get().produce("NODE2");
	qDebug() << QString::fromStdString(n3->getName());

}
int main(int argc, char *argv[])
{
	//std::cout << "hello cv!" << std::endl;
	//qDebug() << "hello cv!!";
	//testCUDA();
	

	test_Fac();
	system("pause");
	return 0;
}
