#include "Magic_Image.h"
#include <QApplication>



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MagicImage w;
    w.show();
    return a.exec();
}
