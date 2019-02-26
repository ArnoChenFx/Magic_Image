#include "NODE_socket.h"
#include <QtDebug>
#include <QPainter>
#include <QGraphicsSceneEvent>
#include <NODE_item.h>
#include <UT_utils.h>
#include <iostream>
#include "NODE_line.h"
#include <NODE_graphics_view.h>
#include <NODE_graphics_scene.h>

NODE_socket::NODE_socket(QGraphicsItem *parent,int index,bool sType, QString nm, qreal offset):QGraphicsItem (parent)
{
    node = dynamic_cast<NODE_item*>(parent);
    socketType = sType;
    setAcceptHoverEvents(true);
    setFlags(QGraphicsItem::ItemIsSelectable);
	nameItem = new QGraphicsTextItem(this);

	id = index;
	name = nm;
	extraOffset = offset;

    updatePosition();

    radius = radius_max;
    _pen.setWidthF(outline_width);

    color_color = getColor("socket_color_color");
    color_value = getColor("socket_color_value");
    color_output = getColor("socket_color_output");
    color_outline = getColor("socket_color_outline");

    _pen = QPen(color_outline);
    _brush_color = QBrush(color_color);
    _brush_output = QBrush(color_output);
    _brush_value = QBrush(color_value);

	//setZValue(1.1);

	nameItem->setDefaultTextColor(getColor("nd_color_attribute"));
	nameItem->setFont(getString("nd_attrib_font"));
	nameItem->setScale(0.7);
	nameItem->setPlainText(name);
	nameItem->setZValue(0.5);

	if (!socketType) {
		nameItem->moveBy(7, -12);
	}
	else nameItem->moveBy(-50,-12);

}

QRectF NODE_socket::boundingRect() const
{
    return QRectF(-radius - outline_width,
                -radius - outline_width,
                2*(radius + outline_width),
                2*(radius + outline_width));
}

void NODE_socket::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{
    //painting circle
    painter->setBrush(socketType?_brush_output:_brush_color);
    painter->setPen(_pen);
    if(!active) radius = radius_min;
    painter->drawEllipse(int(-radius), int(-radius), int(2*radius), int(2*radius));
    nameItem->setPlainText(name);

}

void NODE_socket::updatePosition()
{
	bool state = node->viewerState_item->state;
	qreal delta = state ? node->mapSize.y() : 0;
	delta += node->title_height+30;

    if(socketType)//output
    {
		setPos(node->width, delta+extraOffset);
    }
    else{//input
        setPos(0, delta + extraOffset);
    }
	node->minHeight= max(delta+30, node->minHeight);
	node->height = max(node->minHeight, node->height);
}

void NODE_socket::removeAll(bool avoid, NODE_line*avoidLine)
{
	foreach(NODE_line *line, connectedLines()) {
		if (avoid && line == avoidLine) continue;

		node->nodeView->deleteLine(line);
	}
}

void NODE_socket::updateLines()
{
    foreach(NODE_line *line, connectedLines()){
        //line->updatePosition();
        line->update();
    }
}

void NODE_socket::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    active = true;
    QGraphicsItem::hoverEnterEvent(event);
}

void NODE_socket::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    active = false;
    QGraphicsItem::hoverLeaveEvent(event);
}

void NODE_socket::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if(active){
        QPointF pos = event->pos();
        QPointF pos2 = this->pos();
        pos = mapToParent(pos);
        qreal dist = pow(pos.x()-pos2.x(),2)+pow(pos.y()-pos2.y(),2);
        qreal ratio = dist/(pow(radius_max,2));
        radius = radius_max*(1.0-ratio)+radius_min*ratio;
        update();
    }
    QGraphicsItem::hoverMoveEvent(event);
}

QPointF NODE_socket::position()
{
	QPointF pos = this->pos() + this->node->pos();
	return pos;
}

QList<NODE_line*> NODE_socket::connectedLines()
{
	QPointF pos = position();
	QPointF range = QPointF(5, 5);
	QRectF socketRect = QRectF(pos - range, pos + range);

	QList<NODE_line*> lines;
	
	QList<QGraphicsItem*> items = this->scene()->items(socketRect);
	foreach(QGraphicsItem* item, items) {
		NODE_line *line = dynamic_cast<NODE_line*>(item);
		if (line) lines.append(line);
		//if (line) qDebug() << "connected lines" << line->inputSock->node->title << "," << line->outputSock->node->title;
	}
	items.clear();
	return lines;
}
