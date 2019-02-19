#include "NODE_socket.h"
#include <QtDebug>
#include <QPainter>
#include <QGraphicsSceneEvent>
#include <NODE_item.h>
#include <UT_utils.h>
#include <iostream>
#include "NODE_line.h"
#include <NODE_graphics_view.h>

NODE_socket::NODE_socket(QGraphicsItem *parent,int index,bool sType):QGraphicsItem (parent)
{
    node = dynamic_cast<NODE_item*>(parent);
    socketType = sType;
    setAcceptHoverEvents(true);
    setFlags(QGraphicsItem::ItemIsSelectable);
	nameItem = new QGraphicsTextItem(this);

	id = index;
    name = "Image";

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

    nameItem->setDefaultTextColor(getColor("nd_color_attribute"));
    nameItem->setFont(getString("nd_attrib_font"));
    nameItem->setScale(0.7);
    nameItem->setPlainText(name);
    nameItem->setZValue(0.5);
    if(socketType){
        nameItem->moveBy(-50,-12);
    }
    else{
        nameItem->moveBy(7,-12);
    }
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
		setPos(node->width, delta);
    }
    else{//input
        setPos(0, delta);
    }
	node->minHeight= max(delta+30, node->minHeight);
	node->height = max(node->minHeight, node->height);
}

void NODE_socket::removeAll()
{
    if(socketType){//output socket
        for(int i=0;i<outputLines.length();i++){
            NODE_line *line = outputLines[i];
            if(!node->nodeView->sceneTempLines.contains(line)){
                //line->inputSock = nullptr;
                node->nodeView->sceneTempLines.append(line);
            }
            //node->nodeView->deleteLine(line);
        }
        //outputLines.clear();
    }
    else{//input socket
        for(int i=0;i<inputLines.length();i++){
            NODE_line *line = inputLines[i];
            if(!node->nodeView->sceneTempLines.contains(line)){
                //line->outputSock = nullptr;
                node->nodeView->sceneTempLines.append(line);
            }
            //node->nodeView->deleteLine(line);
        }
        //inputLines.clear();
    }
    node->nodeView->deleteTempLine();
}

void NODE_socket::updateLines()
{
    if(socketType){//output socket
        foreach(NODE_line *line,outputLines){
            //line->updatePosition();
            line->update();
        }
    }
    else{
        foreach(NODE_line *line,inputLines){
            //line->updatePosition();
            line->update();
        }
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
