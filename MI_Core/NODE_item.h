#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <NODE_parts_item.h>
#include <NODE_socket.h>
#include <QGraphicsProxyWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <UT_utils.h>
#include <json.hpp>
#include "mi_core_global.h"

class NODE_graphics_view;

class MI_CORE_EXPORT NODE_item : public QObject,public QGraphicsItem
{
    Q_OBJECT

public:
    NODE_graphics_view *nodeView;

    //attribute
    qreal width;
    qreal height;
    bool pressed = false;
    bool active = true;
    QString title;
    QString name;
    QColor color_title_bar;
    size_t id = global_id;

    //list
    QList<NODE_socket*> input_sockets;
    QList<NODE_socket*> output_sockets;

    QLabel *imagePrevier;

    void removeLine();
    void initWidget();
    QGraphicsProxyWidget *nodeProxyWidget;
    QWidget *nodeMainWidget;
    QVBoxLayout *mainLayout;
    QPixmap *img;

    NODE_title_item *title_item;
    NODE_Shift_item *viewerState_item;
    NODE_Drag_item *drag_item;

    explicit NODE_item(NODE_graphics_view* NODE_v=nullptr,QString title="Node",QPointF pos=QPointF(0,0),qreal width=200,qreal height=250);

    QRectF boundingRect() const override;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *options,QWidget *widget) override;

    json save();
    void load(json nodeInfo);
    void refreshId();
    void appendHistory(QString name);
protected:
    void initChildren();

//    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
//    virtual void leftMousePressEvent(QGraphicsSceneMouseEvent *event);
//    virtual void rightMousePressEvent(QGraphicsSceneMouseEvent *event);
//    virtual void leftMouseReleaseEvent(QGraphicsSceneMouseEvent *event);
//    void keyPressEvent(QKeyEvent *event) override;
    bool collider = false;
    NODE_line *colliderLine;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void updateUI();
    void updateViewer(QRectF rect);
private:
    //pen
    QColor colorDefault;
    QColor colorSelected;
    QColor color_disable;
    QColor colorTitleSelected;
    QColor color_background;
    QColor color_background_disable;
    QPen _penDefault;
    QPen _penSelected;

    QBrush _brush_title_item;
    QBrush _brush_background;

    qreal edge_size = 10.0;
    qreal title_height = 24.0;
    qreal _padding = 4.0;
    QFont nodeTitleFont;
    QFont nodeAttribFont;

    QPointF mapSize;
    QPointF prePos;
};
