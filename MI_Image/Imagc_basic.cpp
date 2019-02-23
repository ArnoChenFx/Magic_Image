#include "Imagc_basic.h"

using namespace cv;

Mat loadImage(std::string path)
{
	Mat m = imread(path);
	Mat image = Mat::zeros(m.rows, m.cols, CV_32FC3) ;
	//m.convertTo(image, CV_32F, 1 / 255.0);
	//cvtColor(image, image, COLOR_BGR2RGB);
	
	int nr = m.rows;
	int nc = m.cols;

#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = image.ptr<float>(i);
		uchar* data2 = m.ptr<uchar>(i);
		for (size_t j = 0; j < nc; j++)
		{
			float b = (float)*data2++;
			float g = (float)*data2++;
			float r = (float)*data2++;
			*data++ = r / 255.0;
			*data++ = g / 255.0;
			*data++ = b / 255.0;
		}
	}

	m.release();
	return image;
}

Mat floatTo8U(cv::Mat m)
{
	Mat image = Mat::zeros(m.rows, m.cols, CV_8UC3);

	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}

#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		uchar* data = image.ptr<uchar>(i);
		float* data2 = m.ptr<float>(i);
		for (size_t j = 0; j < nc; j++)
		{
			*data++ = (uchar)(*data2++ * 255);
		}
	}
	return image;
}