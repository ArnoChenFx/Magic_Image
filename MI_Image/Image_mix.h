#pragma once
//#include <SDKDDKVer.h>
#include <opencv.hpp>

__declspec(dllexport) void Image_test(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_add(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_add(cv::Mat m, cv::Mat n, cv::Mat result);

__declspec(dllexport) void Image_multiply(cv::Mat m, cv::Mat n);
	
__declspec(dllexport) void Image_multiply(cv::Mat m, cv::Mat n, cv::Mat result);

__declspec(dllexport) void Image_substract(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_substract(cv::Mat m, cv::Mat n, cv::Mat result);

__declspec(dllexport) void Image_divide(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_divide(cv::Mat m, cv::Mat n, cv::Mat result);

__declspec(dllexport) void Image_max(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_min(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_screen(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_overlay(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_hardLight(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_softLight(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_vividLight(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_linearLight(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_pinLight(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_colorBurn(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_linearBurn(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_colorDodge(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_difference(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_exclusion(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_average(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_reflect(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_phoenix(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_glow(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_colorOver(cv::Mat m, cv::Mat n);

__declspec(dllexport) void Image_Mask(cv::Mat m, cv::Mat n, cv::Mat mask);

__declspec(dllexport) void Image_gamma(cv::Mat m, float gamma);