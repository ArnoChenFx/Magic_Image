#include "Image_mix.h"
#include <omp.h>

using namespace cv;

float clamp(float a)
{
	if (a > 1) a = 1;
	if (a < 0) a = 0;
	return a;
}

void Image_test(Mat m, Mat n) {
	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			*data = (*data++ + *data2++) * 10;
		}
	}
}

void Image_add(Mat m, Mat n) {

	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}

	//clock_t startTime, endTime;
	//startTime = clock();
#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			*data = (*data++) + (*data2++);
		}
	}
	/*endTime = clock();
	std::cout << "time: : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;*/
}

void Image_add(Mat m, Mat n, Mat result) {

	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);
		float* data3 = result.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			*data3++ = *data++ + *data2++;
		}
	}
}

void Image_multiply(Mat m, Mat n) {

	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			*data = *data++ * *data2++;
		}
	}
}

void Image_multiply(Mat m, Mat n, Mat result) {

	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);
		float* data3 = result.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			*data3++ = *data++ * *data2++;
		}
	}
}

void Image_substract(Mat m, Mat n) {

	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}

#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			*data = max(*data++ - *data2++,.0f);
		}
	}
}

void Image_substract(Mat m, Mat n, Mat result) {

	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);
		float* data3 = result.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			*data3++ = max(*data++ - *data2++, .0f);
		}
	}
}

void Image_divide(Mat m, Mat n) {

	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			*data = *data++ / *data2++;
		}
	}
}

void Image_divide(Mat m, Mat n, Mat result) {

	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);
		float* data3 = result.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			*data3++ = *data++ / *data2++;
		}
	}
}

void Image_max(Mat m, Mat n) {

	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			*data = max(*data++, *data2++);
		}
	}
}

void Image_min(Mat m, Mat n) {

	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			*data = min(*data++, *data2++);
		}
	}
}

void Image_screen(Mat m, Mat n) {
	//1-(1-a)*(1-b)
	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			*data = 1 - (1 - *data++)*(1 - *data2++);
		}
	}
}

void Image_overlay(Mat m, Mat n) {
	//A <= 0.5 : A * B *2
	//A > 0.5 : 1 - (1 - A) * (1 - B)*2
	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			if (*data <= 0.5) *data = (*data++ * *data2++) * 2;
			else *data = 1 - (1 - *data++) * (1 - *data2++) * 2;
		}
	}
}

void Image_hardLight(Mat m, Mat n) {
	//A <= 0.5 : A * B * 2
	//A > 0.5 : 1 - (1 - A) * (1 - B ) * 2

	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			if (*data <= 0.5) *data = *data++ * *data2++ * 2;
			else *data = 1 - (1 - *data++) * (1 - *data2++) * 2;
			*data = clamp(*data);
		}
	}
}

void Image_softLight(Mat m, Mat n) {
	//A <= 0.5 : (2*A-1)*(B-B*B)+B
	//A > 0.5 : (2*A-1)*(sqrt(B)-B)+B
	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			if (*data <= 0.5) *data = (2 * *data++ - 1) * (*data2 - *data2 * *data2) + *data2++;
			else *data = (2 * *data++ -1) * (sqrt(*data2) - *data2) + *data2++;
			*data = clamp(*data);
		}
	}
}

void Image_vividLight(Mat m, Mat n) {
	//(B<0.5)?ColorBurn(A,(2.0*B)):blendColorDodge(A,(2.0*(B-0.5)));
	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			if (*data2 <= 0.5) *data = max(1 - (1 - *data++) / (*data2++), .0f);
			else *data = min(*data++ / (1 - *data2++), 1.0f);
		}
	}
}

void Image_linearLight(Mat m, Mat n) {
	//A + 2*B - 1
	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			*data = *data++ + 2 * *data2++ - 1;
		}
	}
}

void Image_pinLight(Mat m, Mat n) {
	//B <= 0.5 : min(A,2*B))
	//B > 0.5 : max(A,2*(B-0.5))
	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			if (*data <= 0.5) *data = min(*data++ , 2 * *data2++);
			else *data = max(*data++ , 2 * *data2 - 1);
		}
	}
}

void Image_colorBurn(Mat m, Mat n) {
	//	1 - (1-A) / B    
	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			*data = max(1 - (1 - *data++) / (*data2++),.0f);
		}
	}
}

void Image_linearBurn(Mat m, Mat n) {
	//	A + B - 1
	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			*data = max(*data++ + *data2++  - 1.0 , .0);
		}
	}
}

void Image_colorDodge(Mat m, Mat n) {
	//	A / (1-B)
	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}

#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			*data = min(*data++ / (1 - *data2++),1.0f);
		}
	}
}

void Image_difference(Mat m, Mat n) {
	//	|A-B|
	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			*data = abs(*data++  - *data2++);
		}
	}
}

void Image_exclusion(Mat m, Mat n) {
	//	0.5 - 2*(A-0.5)*(B-0.5)
	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			*data = 0.5 - (*data++ - 0.5)*(*data2++ - 0.5) * 2;
		}
	}
}

void Image_average(Mat m, Mat n) {
	//	0.5 * ( A + B )
	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			*data = (*data++ + *data2++ ) * 0.5;
		}
	}
}

void Image_reflect(Mat m, Mat n) {
	//	min(A*A/(1.0-B),1.0)
	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			if (*data2 == 1) *data++ = *data2++;
			else *data = min(*data * *data++ / (1.0 - *data2++), 1.0);
			
		}
	}
}

void Image_phoenix(Mat m, Mat n) {
	//	min(A,B)-max(A,B)+1;
	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			*data = min(*data, *data2) - max(*data++, *data2++) + 1;

		}
	}
}

void Image_glow(Mat m, Mat n) {
	//	min(B*B/(1.0-A),1.0)
	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			if (*data2 == 1) *data++ = *data2++;
			else *data = min(*data2 * *data2++ / (1.0 - *data++), 1.0);

		}
	}
}

void Image_hardMix(Mat m, Mat n) {
	//
	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			if (*data2 <= 0.5) *data = max(1 - (1 - *data++) / (*data2++), .0f);
			else *data = min(*data++ / (1 - *data2++), 1.0f);

			if (*data < 0.5) *data = 0.0;
			else *data = 1.0;

		}
	}
}

void Image_colorOver(Mat m, Mat n) {
	//B <= 0.5 : A * B *2
	//B > 0.5 : 1 - (1 - A) * (1 - B)*2
	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}


#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		float* data2 = n.ptr<float>(i);

		for (size_t j = 0; j < nc; j++)
		{
			if (*data2 <= 0.5) *data = (*data++ * *data2++) * 2;
			else *data = 1 - (1 - *data++) * (1 - *data2++) * 2;
		}
	}
}

void Image_gamma(Mat m, float gamma) {
	int nr = m.rows;
	int nc = m.cols * m.channels();

	if (m.isContinuous()) {
		nc = nc * nr;
		nr = 1;
	}

#pragma omp parallel for num_threads(16)
	for (int i = 0; i < nr; i++)
	{
		float* data = m.ptr<float>(i);
		for (size_t j = 0; j < nc; j++)
		{
			*data = pow(*data++, gamma);
		}
	}
}