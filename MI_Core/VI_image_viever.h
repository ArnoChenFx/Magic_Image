#pragma once

#include <QLabel>
#include <QImage>
#include "mi_core_global.h"

class MI_CORE_EXPORT VI_image_viever:public QLabel
{
    Q_OBJECT

public:
    QImage *mainImage = new QImage;

    VI_image_viever(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void leftMousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event) override;
    void leftMouseMoveEvent(QMouseEvent *event);

signals:
    void click(QMouseEvent *event);
    void move(QMouseEvent *event);

};

