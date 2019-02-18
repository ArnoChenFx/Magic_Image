#pragma once
#include <QGraphicsTextItem>
#include <QGraphicsItem>
#include "mi_core_global.h"

class NODE_item;
class MI_CORE_EXPORT NODE_title_item :public QGraphicsTextItem
{
public:
    NODE_title_item(QGraphicsItem *parent = nullptr);
    NODE_item *node;

private:
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void focusOutEvent(QFocusEvent *event) override;

};

class MI_CORE_EXPORT NODE_Drag_item :public QObject,public QGraphicsItem
{
    Q_OBJECT

public:
    QPointF position;

    NODE_Drag_item(QGraphicsItem *parent = nullptr,qreal width=0,qreal height=0);
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;


protected:

    QRectF boundingRect() const override;
    virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *options,QWidget *widget) override;

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QColor colorDefault;
    QColor colorSelected;
    bool _pressed = false;

signals:
    void positionChange();
};

class MI_CORE_EXPORT NODE_Shift_item :public QObject,public QGraphicsItem
{
    Q_OBJECT

public:
    QPointF position;

    NODE_Shift_item(QGraphicsItem *parent = nullptr);

    bool state = true;

protected:
    QRectF boundingRect() const override;
    virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *options,QWidget *widget) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QColor colorDefault;
    QColor colorSelected;
    bool _pressed = false;

signals:
    void stateChange();
};
