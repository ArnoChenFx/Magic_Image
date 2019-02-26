#pragma once

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include "mi_core_global.h"
#include <VI_image_viever.h>

class MI_CORE_EXPORT VI_graphics_view : public QGraphicsView
{
    Q_OBJECT

public:
	VI_image_viever *viewer;

	QGraphicsScene *VI_graphics_scene;

    VI_graphics_view(VI_image_viever *vi);

protected:
	virtual void wheelEvent(QWheelEvent *event) override;
	virtual void mousePressEvent(QMouseEvent *event) override;
	virtual void mouseMoveEvent(QMouseEvent *event) override;
	virtual void mouseReleaseEvent(QMouseEvent *event) override;
	virtual void keyPressEvent(QKeyEvent *event) override;
    void _focus();

private:
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

	void setScale();
};

