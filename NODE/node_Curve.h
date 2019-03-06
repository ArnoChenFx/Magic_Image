#pragma once
#include "node_global.h"
#include <Register.h>

class NODE_EXPORT node_Curve :public NODE_item
{
public:
	node_Curve(NODE_graphics_view* NODE_v = nullptr);

	virtual void updateParamUI() override;
	virtual void cook() override;

};
