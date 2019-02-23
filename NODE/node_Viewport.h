#pragma once
#include "node_global.h"
#include <Register.h>
#include <VI_image_viever.h>

class NODE_EXPORT node_Viewport:public NODE_item
{
public:
	node_Viewport(NODE_graphics_view* NODE_v = nullptr);

	virtual void initSocket() override;
	virtual void cook() override;
	
};

