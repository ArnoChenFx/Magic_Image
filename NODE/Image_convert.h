#pragma once
#include <opencv.hpp>
#include <qimage.h>
#include "node_global.h"

NODE_EXPORT QImage cvMat2QImage(const cv::Mat& mat);

NODE_EXPORT cv::Mat QImage2cvMat(QImage image);