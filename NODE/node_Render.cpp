#include "node_Render.h"
#include <qdebug.h>

node_Render::node_Render(NODE_graphics_view* NODE_v) :
	NODE_item(NODE_v, "Render")
{
	initSocket();
}



void node_Render::cook()
{

}

REGISTER_NODE(node_Render, "Render", "Export", "");
