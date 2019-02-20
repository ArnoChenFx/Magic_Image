#include "NODE_parts_item.h"
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QTextCursor>
#include <QPainter>
#include <UT_utils.h>
#include <NODE_item.h>
#include <NODE_graphics_view.h>

NODE_title_item::NODE_title_item(QGraphicsItem *parent):QGraphicsTextItem(parent)
{
    node  = dynamic_cast<NODE_item*>(parent);
    setFlags(QGraphicsItem :: ItemIsFocusable);
    setTextInteractionFlags(Qt :: NoTextInteraction);
}

void NODE_title_item::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    node->nodeView->canUseKey=false;
    setTextInteractionFlags(Qt::TextEditable);
    QGraphicsTextItem::mouseDoubleClickEvent(event);
}

void NODE_title_item::keyPressEvent(QKeyEvent *event)
{
    if (event->key() != Qt::Key_Return)
    {
        QGraphicsTextItem::keyPressEvent(event);
    }
    else
    {
        node->nodeView->canUseKey=true;
        event->accept();
        setTextInteractionFlags(Qt::NoTextInteraction);
    }
}

void NODE_title_item::focusOutEvent(QFocusEvent *event)
{
    //this->setTextCursor(QTextCursor());
    //this->setTextInteractionFlags();
    node->nodeView->canUseKey=true;
    setTextInteractionFlags(Qt::NoTextInteraction);

}

NODE_Drag_item::NODE_Drag_item(QGraphicsItem *parent,qreal width,qreal height):QGraphicsItem(parent)
{
    position = QPointF(width,height);
    setFlags(QGraphicsItem :: ItemIsMovable|ItemSendsGeometryChanges);
    colorDefault = getColor("nd_color_drag_default");
    colorSelected = getColor("nd_color_drag_selected");
}

QRectF NODE_Drag_item::boundingRect() const
{
    return(QRectF(-5,-5,10,10));
}

void NODE_Drag_item::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{
    QRectF rect= boundingRect();
    //painter->setPen(QColor(Qt::blue));
    painter->setBrush(QBrush(_pressed ? colorSelected:colorDefault));
    painter->drawEllipse(rect);
}

QVariant NODE_Drag_item::itemChange(GraphicsItemChange change, const QVariant &value)
{

    if(change==ItemPositionHasChanged){
        QPointF eventPos = value.toPointF();
        if(eventPos.x()<40) eventPos = QPointF(40,eventPos.y());
        if(eventPos.y()<(node->minHeight-10)) eventPos = QPointF(eventPos.x(), node->minHeight - 10);
        position = eventPos + QPointF(10,10);
        setPos(eventPos);
        emit positionChange();

    }
    return QGraphicsItem::itemChange(change, value);
}

void NODE_Drag_item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    _pressed= true;
    qDebug() << "pressed drag item";
    update();
    QGraphicsItem::mousePressEvent(event); // zorgt ervoor dat de parents niet het klikken overriden
}

void NODE_Drag_item::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    _pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

NODE_Shift_item::NODE_Shift_item(QGraphicsItem *parent):QGraphicsItem(parent)
{
    setFlags(ItemSendsGeometryChanges);
    colorDefault = getColor("nd_color_drag_default");
    colorSelected = getColor("nd_color_shift_checked");
}

QRectF NODE_Shift_item::boundingRect() const
{
    return(QRectF(-5,-5,10,10));
}

void NODE_Shift_item::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{
    QRectF rect= boundingRect();
    //painter->setPen(QColor(Qt::blue));
    painter->setBrush(QBrush(state ? colorSelected:colorDefault));
    painter->drawEllipse(rect);
}

void NODE_Shift_item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    state = !state;
    emit stateChange();
    update();
    QGraphicsItem::mousePressEvent(event); // zorgt ervoor dat de parents niet het klikken overriden
}

