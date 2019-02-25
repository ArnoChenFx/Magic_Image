#pragma once
#include <opencv.hpp>
#include <string>

__declspec(dllexport) cv::Mat loadImage(std::string path);

__declspec(dllexport) cv::Mat floatTo8U(cv::Mat m);