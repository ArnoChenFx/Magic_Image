#include "Magic_Image.h"
#include <QApplication>
#include <iostream>
#include <string.h>
//#include <GL/glew.h>
using namespace std;


int main(int argc, char *argv[])
{
	//glewInit();

    QApplication a(argc, argv);

    MagicImage w;

	//QFile qss("data/style.qss");
	//qss.open(QFile::ReadOnly);
	//qApp->setStyleSheet(qss.readAll());
	//qss.close();

    w.show();
	
	//delete vp;
    return a.exec();
}
