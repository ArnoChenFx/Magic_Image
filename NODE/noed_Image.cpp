#include "noed_Image.h"
#include <NODE_graphics_view.h>
#include <NODE_item.h>
#include <Register.h>
#include <qdebug.h>

noed_Image::noed_Image(NODE_graphics_view* NODE_v) :
	NODE_item(NODE_v)
{
	qDebug() << "start";
}


noed_Image::~noed_Image()
{
}

json noed_Image::getMenuSet()
{
	json a;
	//menu.hotKey
	return a;
}
//REGISTER_NODE(node_Viewport, "Viewport", 2);
REGISTER_NODE(noed_Image, "Image", "Import","I");
