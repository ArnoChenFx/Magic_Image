#include "node_Viewport.h"
#include <qdebug.h>
#include <opencv.hpp>
#include <Image_basic.h>
#include <Image_convert.h>
#include <time.h>
#include <Thread_node.h>

using namespace cv;

node_Viewport::node_Viewport(NODE_graphics_view* NODE_v):
	NODE_item(NODE_v, "Viewport")
{
	initSocket();
	viewerState_item->setState(true);
	setScale(200, 200);
}

void node_Viewport::initSocket()
{
	//socket input
	NODE_socket *s0 = new NODE_socket(this, 0);
	input_sockets.append(s0);
}

void node_Viewport::cook()
{
	//if (!checkActive()) return;
	qDebug() << "cook viewport";
	getPreImage();
	updateImage(true);
}

REGISTER_NODE(node_Viewport, "Viewport","Export","V");
