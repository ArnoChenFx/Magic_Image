#include "VI_graphics_view.h"
#include <QGraphicsItem>
#include <QWheelEvent>
#include <QGraphicsView>
#include <QScrollBar>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>
#include <qtransform.h>
#include <qmatrix.h>

VI_graphics_view::VI_graphics_view(VI_image_viever *vi) : QGraphicsView()
{	
	VI_graphics_scene = new QGraphicsScene(this);
    this->setScene(VI_graphics_scene);
    VI_graphics_scene->setSceneRect(-width,-height,width*2,height*2);

    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

	viewer = vi;
	VI_graphics_scene->addWidget(viewer);

	scakeRatio = 1;
	focus();
	connect(viewer, &VI_image_viever::scaled, this, [=]() {setScale(); });
	
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
	//qDebug() << this->sceneRect().width();
	//qDebug() << this->sceneRect().height();
	scakeRatio *= zoomFactor;
	emit scaled();
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
        if(zoomDirection == 1.0) zoomFactor = zoomInFactor;
        else zoomFactor = 1 / zoomInFactor;

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
		this->viewport()->setCursor(Qt::ArrowCursor);
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
        focus();
    }
	else if (event->key() == Qt::Key_H) {
		this->resetMatrix();
		scakeRatio = 1;
		QRectF rect = QRectF(0, 0, viewer->width(), viewer->height());
		centerOn(rect.center());
		emit scaled();
	}
    QGraphicsView::keyPressEvent(event);
}

void VI_graphics_view::focus()
{
	qreal w = viewer->width();
	qreal h = viewer->height();
	QRectF itemsArea = QRectF(0,0, w , h);
	this->fitView(itemsArea);
}

void VI_graphics_view::fitView(const QRectF &rect)
{
	qreal ss = 1;

	// Reset the view scale to 1:1.
	QRectF unity = this->matrix().mapRect(QRectF(0, 0, 1, 1));
	if (unity.isEmpty())
		return;
	scale(1 / unity.width(), 1 / unity.height());
	ss *= 1 / unity.width();

	// Find the ideal x / y scaling ratio to fit \a rect in the view.
	int margin = 2;
	QRectF viewRect = viewport()->rect().adjusted(margin, margin, -margin, -margin);
	if (viewRect.isEmpty())
		return;
	QRectF sceneRect = this->matrix().mapRect(rect);
	if (sceneRect.isEmpty())
		return;
	qreal xratio = viewRect.width() / sceneRect.width();
	qreal yratio = viewRect.height() / sceneRect.height();
	// Respect the aspect ratio mode.

	xratio = yratio = qMin(xratio, yratio);

	ss *= xratio;
	// Scale and center on the center of \a rect.
	scale(xratio, yratio);
	centerOn(rect.center());

	scakeRatio *= ss;
	emit scaled();
}

void VI_graphics_view::setScale()
{
	//qreal w = viewer->width();
	//qreal h = viewer->height();
	//viewer->setGeometry(-1 * w / 2,  -1*h / 2, w / 2, h / 2);
}