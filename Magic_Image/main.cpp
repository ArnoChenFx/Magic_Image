#include "Magic_Image.h"
#include <QApplication>
#include <node_Viewport.h>
#include <NODE_item.h>
#include <NODE.h>
#include <Register.h>
#include <iostream>
#include <string.h>
using namespace std;


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MagicImage w;

	//node_Viewport *vp = new node_Viewport(w.nodeView);
	auto node = factory::get().produce("Viewport");
	
	w.nodeView->NODE_scene->addItem(node);
    w.show();
	
	//delete vp;
    return a.exec();
}
