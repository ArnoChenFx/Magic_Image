#pragma once
#include <NODE_item.h>
#include "node_global.h"
#include <Register.h>


class NODE_EXPORT node_Viewport:public NODE_item
{
public:
	node_Viewport(NODE_graphics_view* NODE_v = nullptr);
	~node_Viewport();

	virtual json getMenuSet() override;
};

