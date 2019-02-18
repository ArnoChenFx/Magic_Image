#include "VI_image_viever.h"
#include <QImage>
#include <QMouseEvent>
#include <QDebug>

VI_image_viever::VI_image_viever(QWidget *parent):QLabel (parent)
{
    this->resize(1280,720);

    mainImage->load("F:/FFOutput/Pictures/04.My_work/S (0-00-00-00).png");
    this->setPixmap(QPixmap::fromImage(*mainImage));
    this->resize(1920,1080);
//    mainImage = QImage(self.output.data, self.output.shape[1], self.output.shape[0], QImage.Format_RGB888)
//    height, width, channel = self.output.shape
//    self.viewer.setGeometry(0, 0, width, height)
//    self.viewer.setPixmap(QPixmap.fromImage(showimage))
    this->setMouseTracking(true);

}

void VI_image_viever::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        leftMousePressEvent(event);
    }

    QLabel::mousePressEvent(event);
}

void VI_image_viever::leftMousePressEvent(QMouseEvent *event)
{
    emit click(event);
    QLabel::mousePressEvent(event);
}

void VI_image_viever::mouseMoveEvent(QMouseEvent *event)
{

//    if(event->buttons() & Qt::LeftButton){
//        leftMouseMoveEvent(event);
//    }
    emit move(event);
    QLabel::mouseMoveEvent(event);
}

void VI_image_viever::leftMouseMoveEvent(QMouseEvent *event)
{
    QString msg = QString("move:(%1,%2)").arg(event->pos().x()).arg(event->pos().y());
    //this->mainWindow->IMstatusBar->showMessage(msg);
    emit move(event);
    QLabel::mouseMoveEvent(event);

}

