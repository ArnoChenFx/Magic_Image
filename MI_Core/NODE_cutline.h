#pragma once
#include <QGraphicsPathItem>
#include <QPen>
#include "mi_core_global.h"


class MI_CORE_EXPORT NODE_cutline:public QGraphicsItem
{
public:
    NODE_cutline();
	~NODE_cutline();

    QRectF rect;
    QVector<QPointF> line_points;

    QRectF boundingRect() const override;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *options,QWidget *widget) override;
private:
    QPen _pen;

    void calShape();
};
