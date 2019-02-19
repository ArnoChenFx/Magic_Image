#include "node_Viewport.h"
#include <qdebug.h>

node_Viewport::node_Viewport(NODE_graphics_view* NODE_v):
	NODE_item(NODE_v, "Viewport")
{
	initSocket();
}

void node_Viewport::initSocket()
{
	//socket input
	NODE_socket *s0 = new NODE_socket(this, 0);
	input_sockets.append(s0);
}
void node_Viewport::cook()
{

}

REGISTER_NODE(node_Viewport, "Viewport","Export","V");
