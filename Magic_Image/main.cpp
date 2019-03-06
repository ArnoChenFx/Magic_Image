#include "Magic_Image.h"
#include <QApplication>
#include <iostream>
#include <string.h>
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
	
    return a.exec();
}
