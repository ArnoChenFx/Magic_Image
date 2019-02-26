#pragma once
#include <QGraphicsPathItem>
#include <QPen>
#include <json.hpp>
#include "mi_core_global.h"
using json = nlohmann::json;
class NODE_socket;
class NODE_graphics_view;

class MI_CORE_EXPORT NODE_line:public QObject,public QGraphicsPathItem
{
public:

    //attribute
    NODE_socket *inputSock = nullptr;
    NODE_socket *outputSock = nullptr;
    NODE_socket *startSock = nullptr;
    NODE_socket *endSock = nullptr;
    NODE_graphics_view *nodeView;
    QPainterPath currentPath;
    QPointF startPos;
    QPointF endPos;
    bool isDrag;
    bool isDeleted = false;

    NODE_line(NODE_graphics_view *nodeV=nullptr, NODE_socket *startS=nullptr, NODE_socket *endS=nullptr,bool isDragMode=false);
	~NODE_line();

	QRectF boundingRect() const override;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *options,QWidget *widget) override;
    bool intersectsWith(QPointF p1,QPointF p2);

    void updatePosition();
    void updateSocket();

    json save();
    void appendHistory(QString name);

private:
    QColor _color;
    QColor _color_selected;
    QPen _pen;
    QPen _pen_selected;
    QPen _pen_dragging;
    qreal roundness;

    QPainterPath calPath();
    QPainterPath calLinearPath();
    QPainterPath calCubicPath();
    QPainterPath calBezierPath();

	
};

