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
#include <opencv.hpp>
#include <Thread_node.h>

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
	QPointF mapSize;
	qreal title_height;
	qreal minHeight;
    //list
    QList<NODE_socket*> input_sockets;
    QList<NODE_socket*> output_sockets;

    QLabel *imagePrevier;

    void removeLine();
    void initWidget();
    QGraphicsProxyWidget *nodeProxyWidget;
    QWidget *nodeMainWidget;
    QVBoxLayout *mainLayout;
    QImage *image;

    NODE_title_item *title_item;
    NODE_Shift_item *viewerState_item;
    NODE_Drag_item *drag_item;

    explicit NODE_item(NODE_graphics_view* NODE_v=nullptr,QString title="Node",QPointF pos=QPointF(0,0),qreal width=200,qreal height=250);
	~NODE_item();

    QRectF boundingRect() const override;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *options,QWidget *widget) override;

    json save();
    void load(json nodeInfo);
    void refreshId();
    void appendHistory(QString name);
	void loadToScene();

	bool checkActive();
	//ui
	void updateUI();
	void setScale(qreal w, qreal h);
	void cookNext();

	virtual void updateParamUI();

	//virtual
	virtual void initSocket();
	virtual void cook();

	//mat
	cv::Mat defaultImage;
	cv::Mat resultImage;
	void updateImage(bool ignoreState=false);
	virtual void getPreImage();

	//thread
	Thread_node *myThread;
	QThread *tempThread;

protected:
    void initChildren();

	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
//    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
//    virtual void leftMousePressEvent(QGraphicsSceneMouseEvent *event);
//    virtual void rightMousePressEvent(QGraphicsSceneMouseEvent *event);
//    virtual void leftMouseReleaseEvent(QGraphicsSceneMouseEvent *event);
//    void keyPressEvent(QKeyEvent *event) override;
    bool collider = false;
    NODE_line *colliderLine=nullptr;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    
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

    qreal edge_size;
    qreal _padding;
    QFont nodeTitleFont;
    QFont nodeAttribFont;
	QFont nodeNameFont;

    QPointF prePos;

	QGraphicsTextItem *name_item;

	void onShiftState();
	void loadQss();

signals:
	void cookImage();
	void startThread();
};
