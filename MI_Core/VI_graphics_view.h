#pragma once

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include "mi_core_global.h"

class MI_CORE_EXPORT VI_graphics_view : public QGraphicsView
{
    Q_OBJECT

public:

	QGraphicsScene *VI_graphics_scene;
    VI_graphics_view(QWidget *parent = nullptr);

protected:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void _focus();

private:
    qreal imageWidth = 1920;
    qreal imageHeight = 1080;

    //attribute
    int state = 0;//default state
    const qreal zoomInFactor = 1.15;
    bool zoomClamp = false;
    qreal zoom = 10;
    qreal zoomStep = 1;
    qreal zoomRange_min = 0;
    qreal zoomRange_max = 10;
    QPoint initMousePos;
    QPointF prevPos;
    QPointF zoomInitialPos;
    qreal previousMouseOffset = 0;
    int zoomDirection = 0;
    qreal zoomIncr = 0;
    qreal width = 20000;
    qreal height = 20000;

};

