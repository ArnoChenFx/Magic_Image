#pragma once
#include <QGraphicsItem>
#include <QPen>
#include "mi_core_global.h"

class NODE_item;
class NODE_line;

class MI_CORE_EXPORT NODE_socket:public QGraphicsItem
{
public:
    //attribute
    bool active = false;
    bool socketType;//false:left,true:right
    NODE_item *node;
    QString name;
	int id;

    QGraphicsTextItem *nameItem;

    //list
    //NODE_line *inputLine=nullptr;
    QList<NODE_line*> inputLines;
    QList<NODE_line*> outputLines;

    void removeAll();
    void updateLines();

    NODE_socket(QGraphicsItem *parent = nullptr,int index=0,bool sType=false);

    QRectF boundingRect() const override;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *options,QWidget *widget) override;
    void updatePosition();
	QPointF position();

protected:
	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
	virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    qreal radius;
    qreal radius_min = 7;
    qreal radius_max = 12;
    qreal outline_width = 0.5;

    QColor color_color;
    QColor color_output;
    QColor color_value;
    QColor color_outline;

    QPen _pen = QPen(color_outline);
    QBrush _brush_color;
    QBrush _brush_output;
    QBrush _brush_value;
};
