#include "NODE_cutline.h"
#include <QPainter>
#include <qdebug.h>

NODE_cutline::NODE_cutline():QGraphicsItem()
{
    _pen = QPen(Qt::white);
    _pen.setWidthF(2.0);
   // _pen.setDashPattern([3, 3]);
    setZValue(2);
}

QRectF NODE_cutline::boundingRect() const
{
    return rect;
}

void NODE_cutline::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(_pen);

    QPolygonF poly = QPolygonF(line_points);
    painter->drawPolyline(poly);
}

void NODE_cutline::calShape()
{
    QPolygonF poly = QPolygonF(line_points);
    QPainterPath path;
    if(line_points.length()>1){
        path = QPainterPath(line_points[0]);
        for(int i=1;i<line_points.length();i++){
            path.lineTo(line_points[i]);
        }
    }
    else{
        path = QPainterPath(QPointF(0,0));
        path.lineTo(QPointF(1,1));
    }
    rect = path.boundingRect();
}

NODE_cutline::~NODE_cutline()
{
	qDebug() << "cutline delete";
}