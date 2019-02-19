#include "noed_Image.h"
#include <qdebug.h>

noed_Image::noed_Image(NODE_graphics_view* NODE_v) :
	NODE_item(NODE_v, "Image")
{
	initSocket();
}

void noed_Image::initSocket()
{
	//socket output
	NODE_socket *s0 = new NODE_socket(this, 0, true);
	output_sockets.append(s0);
}



void noed_Image::cook()
{

}

REGISTER_NODE(noed_Image, "Image", "Import","I");
