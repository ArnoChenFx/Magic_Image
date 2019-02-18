#include "VI_graphics_view.h"
#include <QGraphicsItem>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QScrollBar>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>

VI_graphics_view::VI_graphics_view(QWidget *parent) : QGraphicsView(parent)
{	
	VI_graphics_scene = new QGraphicsScene;
    this->setScene(VI_graphics_scene);
    VI_graphics_scene->setSceneRect(-width,-height,width*2,height*2);
    _focus();

    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    this->setCacheMode(QGraphicsView::CacheBackground);
//    this->verticalScrollBar()->blockSignals(true);
//    this->horizontalScrollBar()->blockSignals(true);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setRenderHint(QPainter::Antialiasing);
}

void VI_graphics_view::wheelEvent(QWheelEvent *event)
{
    state = 1;//zoom state

    QPointF pBefore = this->mapToScene(event->pos());

    qreal zoomFactor;
    if(event->angleDelta().y()> 0) zoomFactor = zoomInFactor;
    else zoomFactor = 1 / zoomInFactor;
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    scale(zoomFactor, zoomFactor);

    QPointF pAfter = mapToScene(event->pos());
    QPointF diff = pAfter - pBefore;
    setTransformationAnchor(QGraphicsView::NoAnchor);
    translate(diff.x(), diff.y());

    state = 0;//default state;
}

void VI_graphics_view::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton){
        //     &&event->modifiers() == Qt::AltModifier){
        state = 1;//zoom state
        initMousePos = event->pos();
        zoomInitialPos = event->pos();

    }


    //Drag view
    else if (event->button() == Qt::MiddleButton){
        this->viewport()->setCursor(Qt::ClosedHandCursor);
        state = 2;//drag state
        prevPos = event->pos();
    }

    else{
        state = 0;
    }
    QGraphicsView::mousePressEvent(event);

}

void VI_graphics_view::mouseMoveEvent(QMouseEvent *event)
{
    //zoom
    if (state == 1){
        qreal offset = zoomInitialPos.x() - event->pos().x();
        if(offset >previousMouseOffset){
            previousMouseOffset = offset;
            zoomDirection = -1;
            zoomIncr -= 1;
        }
        else if(abs(offset-previousMouseOffset)<0.0001){
            previousMouseOffset = offset;
            if(zoomDirection == -1){
                zoomDirection = -1;
            }
            else zoomDirection = 1;
        }
        else{
            previousMouseOffset = offset;
            zoomDirection = 1;
            zoomIncr += 1;
        }

        qreal zoomFactor;
        if(zoomDirection == 1.0) zoomFactor = 1.03;
        else zoomFactor = 1 / 1.03;

        //Perform zoom and re-center on initial click position.
        QPointF pBefore = this->mapToScene(initMousePos);
        setTransformationAnchor(QGraphicsView::AnchorViewCenter);
        scale(zoomFactor, zoomFactor);
        QPointF pAfter = mapToScene(initMousePos);
        QPointF diff = pAfter - pBefore;

        setTransformationAnchor(QGraphicsView::NoAnchor);
        translate(diff.x(), diff.y());
    }
    //Drag
    else if(state == 2){
        QPointF ofset = prevPos - event->pos();
        prevPos = event->pos();
        verticalScrollBar()->setValue(verticalScrollBar()->value() + int(ofset.y()));
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() + int(ofset.x()));
        this->viewport()->setCursor(Qt::ClosedHandCursor);
    }

    QGraphicsView::mouseMoveEvent(event);
}

void VI_graphics_view::mouseReleaseEvent(QMouseEvent *event)
{
    //zoom
    if(state == 1){
        zoomDirection = 0;
        zoomIncr = 0;
        setInteractive(true);
    }

    //drag View
    else if(state == 2){
        setInteractive(true);
        this->viewport()->setCursor(Qt::ArrowCursor);
    }
    state = 0;


    QGraphicsView::mouseReleaseEvent(event);
}

void VI_graphics_view::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_F){
        _focus();
    }

    QGraphicsView::keyPressEvent(event);
}

void VI_graphics_view::_focus()
{
    QRectF itemsArea = QRectF(0,0,imageWidth,imageHeight);
    this->fitInView(itemsArea, Qt::KeepAspectRatio);
}
