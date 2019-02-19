#include "Magic_Image.h"
#include <QApplication>
#include <iostream>
#include <string.h>
using namespace std;


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MagicImage w;

    w.show();
	
	//delete vp;
    return a.exec();
}
