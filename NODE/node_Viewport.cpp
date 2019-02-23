#include "node_Viewport.h"
#include <qdebug.h>
#include <opencv.hpp>
#include <Imagc_basic.h>
#include <Image_convert.h>
using namespace cv;

node_Viewport::node_Viewport(NODE_graphics_view* NODE_v):
	NODE_item(NODE_v, "Viewport")
{
	initSocket();
	updateImage();
}

void node_Viewport::initSocket()
{
	//socket input
	NODE_socket *s0 = new NODE_socket(this, 0);
	input_sockets.append(s0);
}


void node_Viewport::cook()
{
	resultImage.release();
	//F:/FFOutput/Download/1.jpg
	//F:/FFOutput/Download/Compressed/RS/07.Car/B.png

	resultImage = loadImage("F:/FFOutput/Download/Compressed/RS/07.Car/B.png");
	if (viewerState_item->state) {
		updateImage();
		emit cookImage();
	}
	updateUI();
}

REGISTER_NODE(node_Viewport, "Viewport","Export","V");
