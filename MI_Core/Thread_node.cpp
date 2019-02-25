#include "Thread_node.h"
#include <opencv.hpp>
#include <NODE_item.h>
#include <qdebug.h>


Thread_node::Thread_node(NODE_item *nd):QObject()
{
	node = nd;
	stop = false;
}


Thread_node::~Thread_node()
{
}

void Thread_node::stopImmediately()
{
	QMutexLocker locker(&m_lock);
	m_isCanRun = false;
}

void Thread_node::setStop(bool flag)
{
	stop = true;
}
void Thread_node::updateImage()
{
	clock_t startTime, endTime;

	startTime = clock();

	//-------------------
	cv::Mat m = cv::Mat::zeros(node->resultImage.rows, node->resultImage.cols, CV_8UC3);

	qDebug() << "node image size" <<node->resultImage.rows<< node->resultImage.cols;

	int nr = node->resultImage.rows;
	int nc = node->resultImage.cols * node->resultImage.channels();

	if (node->resultImage.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}

	cv::Mat imag = node->resultImage;

#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		uchar* data = m.ptr<uchar>(i);
		float* data2 = imag.ptr<float>(i);
		for (size_t j = 0; j < nc; j++)
		{
			*data++ = (uchar)(*data2++ * 255);
		}
	}
	//-------------------
	endTime = clock();
	qDebug() << "convert to 8UC3 : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s";
	startTime = clock();

	QImage *img = new  QImage((uchar*)m.data, m.cols, m.rows, m.step, QImage::Format_RGB888);
	node->image = new QImage(img->width(), img->height(), img->format());
	*(node->image) = img->copy();
	delete img;

	endTime = clock();
	qDebug() << "convert to QImage : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s";

	//QRectF rect = QRectF(8, node->title_height + 5, node->width - 16, node->height - node->title_height - 16);
	emit done();
}

void Thread_node::run()
{
	updateImage();

	//QMutexLocker locker(&m_lock);
	//return;
	//while (1) {
	//	QMutexLocker locker(&m_lock);
	//	if (!m_isCanRun) return;
	//}
	return;
	while (stop) return;
}
