#pragma once
#include "node_global.h"
#include <Register.h>


class NODE_EXPORT noed_Image :public NODE_item
{
public:
	noed_Image(NODE_graphics_view* NODE_v = nullptr);

	virtual void initSocket() override;
	virtual void cook() override;
};

