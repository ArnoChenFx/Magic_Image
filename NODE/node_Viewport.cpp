#include "node_Viewport.h"
#include <NODE_graphics_view.h>
#include <NODE_item.h>
#include <Register.h>
#include <qdebug.h>

node_Viewport::node_Viewport(NODE_graphics_view* NODE_v):
	NODE_item(NODE_v)
{
	qDebug() << "start";
}


node_Viewport::~node_Viewport()
{
}

json node_Viewport::getMenuSet()
{
	json a;
	//menu.hotKey
	return a;
}
//REGISTER_NODE(node_Viewport, "Viewport", 2);
REGISTER_NODE(node_Viewport, "Viewport","Export","V");
