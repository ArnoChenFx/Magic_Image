#pragma once
#include <node_global.h>
#include <Register.h>

class NODE_EXPORT node_Merge :public NODE_item
{
public:
	node_Merge(NODE_graphics_view* NODE_v = nullptr);

	virtual void initSocket() override;
	virtual void updateParamUI() override;

	virtual void cook() override;

private:
	int index;
	void computeMix();

	cv::Mat ColorA;
	cv::Mat ColorB;
	cv::Mat Mask;

	bool hasMask;
	void getImage();
};