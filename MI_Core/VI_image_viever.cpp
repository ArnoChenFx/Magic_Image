#include "VI_image_viever.h"
#include <QMouseEvent>
#include <QDebug>

VI_image_viever::VI_image_viever(QWidget *parent):QLabel (parent)
{
	mainImage = new QImage(1920,1080, QImage::Format_RGB888);
	mainImage->fill(Qt::black);
	updateImage();

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

void VI_image_viever::updateImage()
{
	this->setPixmap(QPixmap::fromImage(*mainImage));
	this->setFixedHeight(mainImage->height());
	this->setFixedWidth(mainImage->width());
}