#include "NODE_item.h"
#include <QtDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEffect>
#include <NODE_parts_item.h>
#include <QTextDocument>
#include <QFont>
#include <NODE_socket.h>
#include <UT_utils.h>
#include <NODE_graphics_view.h>
#include <NODE_line.h>
#include <QGraphicsProxyWidget>
#include <QtWidgets>
#include <QVBoxLayout>
#include <UT_utils.h>
#include <json.hpp>
using json = nlohmann::json;

NODE_item::NODE_item(NODE_graphics_view* NODE_v,QString title,QPointF pos,qreal width,qreal height):QGraphicsItem()
{
    global_id += 1;
    //init attribute
    this->width = width;
    this->height = height;
    this->title = title;
    
	if (NODE_v != nullptr) {
		this->nodeView = NODE_v;
		loadToScene();
	}

    this->setPos(pos);

	//INIT
	imagePrevier = new QLabel;
	title_item = new NODE_title_item(this);
	viewerState_item = new NODE_Shift_item(this);
	drag_item = new NODE_Drag_item(this, width, height);

    this->setFlags(ItemIsSelectable|ItemIsMovable);
    //|ItemIsFocusable
    this->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

    this->name = "node_base";

    QGraphicsDropShadowEffect *dropShadowEffect=new QGraphicsDropShadowEffect;
    dropShadowEffect->setColor(QColor(63,63,63,100));
    dropShadowEffect->setBlurRadius(2);
    dropShadowEffect->setOffset(5);
    //this->setGraphicsEffect(dropShadowEffect);

    QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
    opacityEffect->setOpacity(0.95);

    //this->setGraphicsEffect(opacityEffect);

    colorDefault = getColor("nd_color_default");
    colorSelected = getColor("nd_color_selected");
    color_disable= getColor("nd_color_disable");
    colorTitleSelected = getColor("nd_color_title_selected");
    color_background = getColor("nd_color_background");
    color_background_disable = getColor("nd_color_background_disable");
    _penDefault  =QPen(colorDefault);
    _penSelected = QPen(colorSelected);

    nodeTitleFont = QFont(getString("nd_title_font"),12,QFont::Bold);
    nodeAttribFont = QFont(getString("nd_attrib_font"),10,QFont::Normal);
    color_title_bar = getColor("nd_color_title_bar");

    initWidget();
    initChildren();
}

void NODE_item::loadToScene()
{
	nodeView->NODE_scene->addItem(this);
	nodeView->NODE_scene->sceneNodes.append(this);
}

QRectF NODE_item::boundingRect() const
{
    return QRectF(0,0,width,height);
}

void NODE_item::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{
    //title
    QPainterPath path_title;
    path_title.setFillRule(Qt::WindingFill);
    path_title.addRoundedRect(0,0, width,title_height,edge_size,edge_size);
    path_title.addRect(0,title_height-edge_size, edge_size, edge_size);
    path_title.addRect(width-edge_size,title_height-edge_size,edge_size,edge_size);
    painter->setPen(Qt::NoPen);
    _brush_title_item = QBrush(active?color_title_bar:color_disable);
    painter->setBrush(_brush_title_item);
    painter->drawPath(path_title.simplified());

    //content
    QPainterPath path_content;
    path_content.setFillRule(Qt::WindingFill);
    path_content.addRoundedRect(0, title_height,width, height - title_height, edge_size, edge_size);
    path_content.addRect(0, title_height, edge_size, edge_size);
    path_content.addRect(width - edge_size, title_height, edge_size, edge_size);
    painter->setPen(Qt::NoPen);
    _brush_background = QBrush(active?color_background:color_background_disable);
    painter->setBrush(_brush_background);
    painter->drawPath(path_content.simplified());


    //outline
    QPainterPath path_outline;
    path_outline.addRoundedRect(0, 0,width,height,edge_size,edge_size);
    painter->setPen(isSelected()?_penSelected:_penDefault);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path_outline.simplified());

    //title
    title_item->setDefaultTextColor(isSelected() ? colorTitleSelected:colorDefault);
}

void NODE_item::removeLine()
{
    foreach(NODE_socket *socket,input_sockets){
        socket->removeAll();
    }
    foreach(NODE_socket *socket,output_sockets){
        socket->removeAll();
    }
    //nodeView->NODE_scene->removeItem(this);
    //nodeView->sceneSelectedNodes.removeOne(this);
    //delete this;
}

void NODE_item::initChildren()
{
    //title
    title_item->setPlainText(title);
    title_item->setFont(nodeTitleFont);
    title_item->setPos(0,-30);
    connect(title_item->document(),&QTextDocument::contentsChanged, [=]() {
        title = title_item->toPlainText();
    });

    //drag item

    drag_item->setPos(width-10,height-10);
    connect(drag_item,&NODE_Drag_item::positionChange,this,[=]() {
        width = drag_item->position.x();
        height = drag_item->position.y();
        updateUI();
    });

    //shift item
    viewerState_item->setPos(10,13);
    connect(viewerState_item,&NODE_Shift_item::stateChange,this,[=]() {
        bool state = viewerState_item->state;
        qreal delta = mapSize.y();
        if(state){
            imagePrevier->setVisible(true);
            height = height + delta;
        }
        else{
            imagePrevier->setVisible(false);
            height = height - delta;
        }
        drag_item->setPos(width-10,height-10);
        updateUI();
    });

    //socket output
    NODE_socket *s0 = new NODE_socket(this,0,true);
    output_sockets.append(s0);

    //socket input
    NODE_socket *p0 = new NODE_socket(this,1);
    input_sockets.append(p0);
}

void NODE_item::initWidget()
{
    nodeProxyWidget = new QGraphicsProxyWidget(this);
    nodeMainWidget = new QWidget;
    nodeMainWidget->setStyleSheet("background-color:transparent");
    nodeProxyWidget->setWidget(nodeMainWidget);
    mainLayout =new QVBoxLayout;
    mainLayout->setContentsMargins(0,0,0,0);
    QRectF rect = QRectF(8, title_height+5,width-16, height-title_height-16);
//           QRectF(edge_size, title_height + edge_size,
//           width - 2*edge_size, height - 2*edge_size-title_height);
    nodeProxyWidget->setGeometry(rect);
    nodeMainWidget->setLayout(mainLayout);

    //picture viewer
    mainLayout->addWidget(imagePrevier);
    imagePrevier->setAlignment(Qt::AlignTop);
    //imagePrevier->setStyleSheet("border-width: 1px;border-style: solid;border-color: rgb(255, 170, 0);");
    //QPixmap *img = new QPixmap("D:/DATA/Picture/04.My_work/Co_plant.png");
    img = new QPixmap("F:/FFOutput/Pictures/04.My_work/Co_plant.png");
    updateViewer(rect);

}

void NODE_item::updateUI()
{
    foreach(NODE_socket *sock,output_sockets){
        sock->updatePosition();
    }
    foreach(NODE_socket*sock,input_sockets){
        sock->updatePosition();
    }
    QRectF rect = QRectF(5, title_height+2,width-10, height-title_height-10);

    nodeProxyWidget->setGeometry(rect);
    updateViewer(rect);
    update();
}

void NODE_item::updateViewer(QRectF rect)
{
    if(!viewerState_item->state) return;
    imagePrevier->resize(rect.width(),rect.height());
    QPixmap map= img->scaled(imagePrevier->size(), Qt::KeepAspectRatio);
    imagePrevier->setPixmap(map);
    imagePrevier->resize(map.width(),map.height());
    mapSize = QPointF(map.width(),map.height());
}

json NODE_item::save()
{
    json nodeInfo = json::object();
    nodeInfo["title"] = title.toStdString();
    nodeInfo["name"] = name.toStdString();
    nodeInfo["width"] = width;
    nodeInfo["height"] = height;
    nodeInfo["state"] = viewerState_item->state;
    nodeInfo["id"] = id;
    nodeInfo["active"] = active;
    nodeInfo["pos_x"] = pos().x();
    nodeInfo["pos_y"] = pos().y();
    return nodeInfo;
}

void NODE_item::load(json nodeInfo)
{
    title = QString::fromStdString(nodeInfo["title"]);
    setPos(QPointF(nodeInfo["pos_x"],nodeInfo["pos_y"]));
    width = nodeInfo["width"];
    height = nodeInfo["height"];
    bool state = nodeInfo["state"];
    viewerState_item->state = state;
    active = nodeInfo["active"];
    id = nodeInfo["id"];

    if(state) imagePrevier->setVisible(true);
    else imagePrevier->setVisible(false);
    title_item->setPlainText(title);
    drag_item->setPos(width-10,height-10);
    update();
}

void NODE_item::refreshId()
{
    global_id += 1;
    id = global_id;
}

void NODE_item::appendHistory(QString name)
{
    if(name=="create_node")
        saveHistory("create_node",save());
    else if(name=="delete_node")
        saveHistory("delete_node",save());
    else if(name=="move_item"){
        json move = json::object();
        move["id"] = id;
        move["prePos_x"] = prePos.x();
        move["prePos_y"] = prePos.y();
        move["pos_x"] = this->pos().x();
        move["pos_y"] = this->pos().y();
        saveHistory("move_item",move);
        prePos = this->pos();
    }

}

void NODE_item::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    appendHistory("move_item");

    if(collider){
        //qDebug()<<"collier with line"<<colliderLine;
        NODE_socket *preSocket = colliderLine->inputSock;
        NODE_socket *nextSocket = colliderLine->outputSock;

        if(!nodeView->sceneTempLines.contains(colliderLine))
                nodeView->sceneTempLines.append(colliderLine);
        nodeView->deleteTempLine();

        if(!input_sockets.isEmpty())
            new NODE_line(nodeView,preSocket,input_sockets[0]);
        if(!output_sockets.isEmpty())
            new NODE_line(nodeView,output_sockets[0],nextSocket);
        collider = false;
        colliderLine = nullptr;
    }
    event->accept();
    QGraphicsItem::mouseReleaseEvent(event);
}

void NODE_item::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //nodeView->colliderNode = this;
    //foreach(NODE_socket *inSocket,input_sockets) inSocket->updateLines();

    //foreach(NODE_socket *outSocket,output_sockets) outSocket->updateLines();

    foreach(NODE_line *line,nodeView->NODE_scene->sceneLines){
        collider = false;
        if(this->collidesWithItem(line)){
            if(line->inputSock->node!= this && line->outputSock->node!=this){
                collider = true;
                colliderLine = line;
                line->setSelected(true);
                collider = true;
                event->accept();
                QGraphicsItem::mouseMoveEvent(event);
                break;
            }
        }
        else{
            line->setSelected(false);
        }
    }
    QGraphicsItem::mouseMoveEvent(event);
}

json NODE_item::getMenuSet() {
	json a;
	return a;
}
//void NODE_item::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    if(event->button() == Qt::LeftButton){
//        leftMousePressEvent(event);

//    }
//    else if(event->button() == Qt::RightButton){
//        rightMousePressEvent(event);
//    }
//    QGraphicsItem::mousePressEvent(event);
//}

//void NODE_item::leftMousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    pressed = isSelected() ? true:false;
//    qDebug() <<"left mouse press "<<title;
//    //update();
//    QGraphicsItem::mousePressEvent(event);
//}

//void NODE_item::rightMousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    pressed = isSelected() ? true:false;
//    qDebug() <<"right mouse press "<<title;
//    //update();
//    QGraphicsItem::mousePressEvent(event);
//}

//void NODE_item::leftMouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
//    pressed = isSelected() ? true:false;
//    qDebug() <<"left mouse release "<<title;
//    height += 1;
//    //update();
//    QGraphicsItem::mouseReleaseEvent(event);
//}

//void NODE_item::keyPressEvent(QKeyEvent *event)
//{
//    if(event->key()==Qt::Key_1){
//        qDebug()<<"connect to viewport";
//    }
//    else if(event->key()==Qt::Key_D){
//        active = !active;
//        update();
//    }

//    QGraphicsItem::keyPressEvent(event);
//}
