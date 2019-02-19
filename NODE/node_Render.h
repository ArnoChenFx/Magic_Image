#pragma once
#include "node_global.h"
#include <Register.h>


class NODE_EXPORT node_Render :public NODE_item
{
public:
	node_Render(NODE_graphics_view* NODE_v = nullptr);

	virtual void cook() override;
};

