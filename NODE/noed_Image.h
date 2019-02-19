#pragma once
#include <NODE_item.h>
#include "node_global.h"
#include <Register.h>


class NODE_EXPORT noed_Image :public NODE_item
{
public:
	noed_Image(NODE_graphics_view* NODE_v = nullptr);
	~noed_Image();

	virtual json getMenuSet() override;
};

