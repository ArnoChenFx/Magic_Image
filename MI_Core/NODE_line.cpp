#include "NODE_line.h"
#include <QPainter>
#include <UT_utils.h>
#include <NODE_graphics_scene.h>
#include <NODE_socket.h>
#include <QtDebug>
#include <NODE_item.h>
#include <NODE_socket.h>
#include <NODE_graphics_view.h>
#include <json.hpp>
using json = nlohmann::json;

NODE_line::NODE_line(NODE_graphics_view *nodeV,NODE_socket *startS,NODE_socket *endS,bool isDragMode):QGraphicsPathItem ()
{
    nodeView = nodeV;
    nodeView->NODE_scene->addItem(this);
    isDrag = isDragMode;

    startSock = startS;
    endSock = endS;
    updateSocket();

    setZValue(-1);
    //(QGraphicsItem::ItemIsSelectable);
    setFlags(QGraphicsItem::ItemIsFocusable  | QGraphicsItem::ItemIsSelectable);
    setCacheMode(QGraphicsItem::NoCache);

    _color = getColor("line_color_default");
    _color_selected = getColor("line_color_selected");
    _pen = QPen(_color);
    _pen_selected = QPen(_color_selected);
    _pen_dragging = QPen(_color);
    _pen_dragging.setStyle(Qt::DashLine);
    _pen.setWidthF(3);
    _pen_selected.setWidthF(4);
    _pen_dragging.setWidthF(3);
    roundness = 100;

    updatePosition();
    //qDebug()<<"line Created";

	//nodeV->update();
	//if(!isDrag) outputSock->node->cook();
}

NODE_line::~NODE_line()
{
	nodeView = nullptr;
	inputSock = nullptr;
	outputSock = nullptr;
	startSock = nullptr;
	endSock = nullptr;
	//qDebug() << "delete line on close";
}

QRectF NODE_line::boundingRect() const
{
    QRectF rect = QRectF(startPos,endPos);
    return rect;//currentPath.boundingRect();
}

void NODE_line::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{
    updatePosition();
    setPath(calPath());

    if(isDrag)
    {
        painter->setPen(_pen_dragging);
    }
    else{
        painter->setPen(isSelected()?_pen_selected:_pen);
    }
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path());
}

bool NODE_line::intersectsWith(QPointF p1, QPointF p2)
{
    QPainterPath cutpath = QPainterPath(p1);
    cutpath.lineTo(p2);
    QPainterPath path = calPath();
    return cutpath.intersects(path);
}

void NODE_line::updatePosition()
{
    if(!isDeleted){
        startPos = startSock->position();
        //qDebug()<<"startPos"<<startPos;

        if(!isDrag){
            endPos = endSock->position();
            //qDebug()<<"endPos"<<endPos;
        }
    }
    else{
        startPos = QPointF(0,0);
        endPos = startPos;
    }
}

void NODE_line::updateSocket()
{
    if(!isDrag){
        if(startSock->socketType){
            inputSock = startSock;
            outputSock = endSock;
        }
        else{
            inputSock = endSock;
            outputSock = startSock;
        }
		if(inputSock->multiConnect== false) inputSock->removeAll(true, this);
		if(outputSock->multiConnect == false) outputSock->removeAll(true,this);
        //nodeView->NODE_scene->sceneLines.append(this);
        saveHistory("create_line",save());
		qDebug() << "cook : " << outputSock->node->title;
    }
    else{
        startPos = startSock->position();
        endPos = startPos;
    }
}

json NODE_line::save()
{
    json lineInfo;
    lineInfo["inPos_x"] = inputSock->position().x();
	lineInfo["inPos_y"] = inputSock->position().y();
	lineInfo["outPos_x"] = outputSock->position().x();
	lineInfo["outPos_y"] = outputSock->position().y();
    return lineInfo;
}

void NODE_line::appendHistory(QString name)
{
    if(name=="create_line")
        saveHistory("create_line",save());
    else if(name=="delete_line")
        saveHistory("delete_line",save());
}

QPainterPath NODE_line::calPath()
{
    currentPath = nodeView->lineType?calCubicPath():calLinearPath();
    return currentPath;
}

QPainterPath NODE_line::calLinearPath()
{
    QPainterPath path = QPainterPath(startPos);
    path.lineTo(endPos);
    return path;
}

QPainterPath NODE_line::calCubicPath()
{
    QPainterPath path = QPainterPath();
    path.moveTo(startPos);
    qreal dx = (endPos.x() - startPos.x()) * 0.5;
    qreal dy = endPos.y() - startPos.y();
    QPointF ctrl1 = QPointF(startPos.x() + dx, startPos.y() + dy * 0);
    QPointF ctrl2 = QPointF(startPos.x() + dx, startPos.y() + dy * 1);
    path.cubicTo(ctrl1, ctrl2, endPos);

    return path;
}

QPainterPath NODE_line::calBezierPath()
{
    QPointF s = startPos;
    QPointF d = endPos;
    qreal dist = (d.x() - s.x()) * 0.5;

    qreal cpx_s = +dist;
    qreal cpx_d = -dist;
    qreal cpy_s = 0;
    qreal cpy_d = 0;

    if(true){//startSock != nullptr
        //bool sspos = startSock->socketType;
        bool sspos = true;
        if ((s.x() > d.x() && sspos==true) || (
                    s.x() < d.x() && sspos==false)){
            cpx_d *= -1;
            cpx_s *= -1;

            cpy_d = ((s.y() - d.y()) / fabs(((s.y() - d.y()) != 0)?(s.y() - d.y()):0.00001)
                    ) * roundness;
            cpy_s = ((d.y() - s.y()) / fabs(((d.y() - s.y())!=0)?(d.y() - s.y()):0.00001
                    )
                    ) * roundness;
        }
    }
    QPainterPath path = QPainterPath(startPos);
    path.cubicTo(s.x() + cpx_s, s.y() + cpy_s, d.x() + cpx_d, d.y() + cpy_d, endPos.x(),
endPos.y());

    return path;
}
