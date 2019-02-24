#include "NODE_graphics_view.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <QMimeData>
#include <QDragMoveEvent>
#include <QScrollBar>
#include <QDebug>
#include <QOpenGLWidget>
#include <QList>
#include <UT_utils.h>
#include <iostream>
#include <qwidgetaction.h>

NODE_graphics_view::NODE_graphics_view() : QGraphicsView()
{
	NODE_scene = new NODE_graphics_scene(this);
    this->setScene(NODE_scene);
    NODE_scene->setSceneRect(floor(-width / 2),floor( -height / 2), width, height);
    initFlags();

    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QPen blackpen(Qt::black);
    blackpen.setWidth(5);

    prePos = mousePos;

    this->setStyleSheet("background-color:rgb(30,30,30)");

	contextMenu = new QMenu();
	searchLine = new QLineEdit();
	connect(searchLine, &QLineEdit::textChanged,[=]() {searchNode();});
	connect(searchLine, &QLineEdit::returnPressed,[=](){applySearch();});
	searchLine->setContextMenuPolicy(Qt::NoContextMenu);
	
}

void NODE_graphics_view::onCopy()
{

    if(canUseKey){
        clipboard.clear();
        json nodes = json::array();
        json lines = json::array();
        foreach(QGraphicsItem *item,NODE_scene->selectedItems()){
            NODE_item* node= dynamic_cast<NODE_item*>(item);
            if(node){
                nodes.push_back(node->save());
            }
        }
        clipboard.push_back(nodes);

        foreach(QGraphicsItem *item,NODE_scene->selectedItems()){
            NODE_line* line= dynamic_cast<NODE_line*>(item);
            if(line){
                lines.push_back(line->save());
            }
        }
        clipboard.push_back(lines);

        prePos = mousePos;
        //std::cout<<clipboard<<std::endl;
        //std::cout<<clipboard[0]<<std::endl;
        qDebug()<<"copy";
    }
}

void NODE_graphics_view::onPase(bool move)
{
    if(canUseKey){
        qDebug()<<"pase";
        QPointF movePos = mousePos-prePos;
        QList<NODE_item*> newNodes;
        for (auto& info : clipboard[0].items())
        {
            auto ndInfo = info.value();
            auto node = new NODE_item(this);
            node->load(ndInfo);
            node->moveBy(movePos.x(),movePos.y());
            if(move) node->moveBy(0,200);
            newNodes.append(node);
        }

        for (auto& info : clipboard[1].items())
        {
            auto liInfo = info.value();
            size_t inNode = liInfo["inputNode"];
            size_t outNode = liInfo["outputNode"];
            QString inSocketName = QString::fromStdString(liInfo["inputSocket"]);
            QString outSocketName = QString::fromStdString(liInfo["outputSocket"]);
            NODE_socket *inSocket = nullptr;
            NODE_socket *outSocket = nullptr;
            int count=0;
            foreach(NODE_item* node,newNodes){
                if(count==2) break;
                else if(node->id==inNode){
                    foreach(NODE_socket *socket,node->output_sockets){
                        if(socket->name==inSocketName) inSocket = socket;
                        count ++;
                        //break;
                    }
                }
                else if(node->id==outNode){
                    foreach(NODE_socket *socket,node->input_sockets){
                        if(socket->name==outSocketName) outSocket = socket;
                        count ++;
                        //break;
                    }
                }

            }
            if(count==2) new NODE_line(this,inSocket,outSocket);
            else qDebug()<<"create Line error!!";
        }
        foreach(NODE_item* node,newNodes){node->refreshId();}
    }
}

void NODE_graphics_view::onCopyPase()
{
    if(canUseKey){
        qDebug()<<"copy and pase";
        onCopy();
        onPase(true);
    }
}

void NODE_graphics_view::onCut()
{
    if(canUseKey){
        qDebug()<<"cut";
        onCopy();
        onDeleteSelected();
    }
}

void NODE_graphics_view::onDeleteSelected()
{
    if(canUseKey){
        clearSelected();
        NODE_scene->update();
        deleteSelected();
    }
}

void NODE_graphics_view::onDisable()
{
    if(canUseKey){
        foreach(QGraphicsItem* item,NODE_scene->selectedItems()){
            NODE_item* node= dynamic_cast<NODE_item*>(item);
            if(node){
                bool active = node->active;
                node->active = !active;
				node->cook();
                node->update();
            }
        }
    }
}

void NODE_graphics_view::onConnectToViewport()
{
	if (NODE_scene->selectedItems().length()>0) {
		auto item = NODE_scene->selectedItems()[0];
		NODE_item *currentNode = dynamic_cast<NODE_item*>(item);

		if (viewportNode != nullptr && currentNode) {
			if (currentNode->output_sockets.length() > 0) {
				NODE_socket *inSocket = currentNode->output_sockets[0];
				NODE_socket *outSocket = viewportNode->input_sockets[0];
				new NODE_line(this, inSocket, outSocket);
			}

		}
	}
}

void NODE_graphics_view::onFocus()
{
    if(canUseKey){
        QList<QGraphicsItem*> list = this->NODE_scene->selectedItems();
        QRectF itemsArea;
        if(list.isEmpty()) itemsArea = NODE_scene->itemsBoundingRect();
        else itemsArea = _getSelectionBoundingbox();
        this->fitInView(itemsArea, Qt::KeepAspectRatio);
    }
}

void NODE_graphics_view::onIndependent()
{
    if(canUseKey){
        foreach(QGraphicsItem* item,NODE_scene->selectedItems()){
            NODE_item* node= dynamic_cast<NODE_item*>(item);
            if(node){
				if (node->input_sockets.length() > 0 && node->output_sockets.length() > 0
					&& node->input_sockets[0]->inputLines.length() > 0
					&& node->output_sockets[0]->outputLines.length() > 0) {
					NODE_socket *inS = node->input_sockets[0]->inputLines[0]->inputSock;
					NODE_socket *outS = node->output_sockets[0]->outputLines[0]->outputSock;
					node->removeLine();
					new NODE_line(this, inS, outS);
				}
				else node->removeLine();
				return;
            }
        }
    }
}

void NODE_graphics_view::wheelEvent(QWheelEvent *event)
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

void NODE_graphics_view::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton){
        //&&event->modifiers() == Qt::AltModifier){
        state = 4;//zoom state pre
        initMousePos = event->pos();
        zoomInitialPos = event->pos();
		QGraphicsView::mousePressEvent(event);
    }
    else if (event->button() == Qt::MiddleButton){
        //Drag view
        state = 2;//drag state
        prevPos = event->pos();
        this->viewport()->setCursor(Qt::ClosedHandCursor);
        QGraphicsView::mousePressEvent(event);
    }

    else if (event->button() == Qt::LeftButton) leftMousePressEvent(event);

}

void NODE_graphics_view::mouseMoveEvent(QMouseEvent *event)
{
    mousePos = mapToScene(event->pos());
    if(MODE==MODE_LINE_DRAG){
		//change drag
        if(canChangeDrag && event->buttons() & Qt::LeftButton){
            NODE_socket *startS = dragLine->startSock;
            NODE_socket *endS = nullptr;
            NODE_line *origLine = nullptr;
            if(startS->socketType){//output socket
                if(!startS->outputLines.isEmpty()){
                    origLine = startS->outputLines[0];
                    endS = origLine->outputSock;
                    deleteOneLine(origLine);
                }
            }
            else{//input socket
                if(!startS->inputLines.isEmpty()){
                    origLine = startS->inputLines[0];
                    endS = origLine->inputSock;
                    deleteOneLine(origLine);
                }
            }
            if(endS!=nullptr){
                dragLine->startSock = endS;
                startSocket = endS;
                canChangeDrag = false;
            }
            qDebug()<<"change line";
        }

		//normal drag
        dragLine->endPos = mapToScene(event->pos());

		//auto adsorb drag
		QPointF range = QPointF(50, 50);
		NODE_socket * nearestScoekt = nullptr;
		qreal len = 200;
		QPointF nearestPos;
		foreach(QGraphicsItem* item, NODE_scene->items(QRectF(mousePos - range, mousePos + range))) {
			NODE_socket * socket = dynamic_cast<NODE_socket*>(item);
			if (socket && socket->node!= startSocket->node && socket->socketType != startSocket->socketType) {
				QPointF pos = socket->position();
				qreal dist = Qdistance(mousePos, pos);
				if (dist < len) {
					len = dist;
					nearestPos = pos;
					nearestScoekt = socket;
				}
			}
		}
		if (nearestScoekt != nullptr) {
			dragLine->endPos = nearestPos;
			adsorbSocket = nearestScoekt;
			adsorb = true;
		}
		else {
			adsorb = false;
			adsorbSocket = nullptr;
		}

		//update
        dragLine->update();
        update();
    }


    else if(MODE==MODE_LINE_CUT){
        cutline->line_points.append(mapToScene(event->pos()));
        cutline->update();
    }

    //zoom
	if (state==4 || state ==1) {
		state = 1;//zoom state
		setDragMode(QGraphicsView::NoDrag);
		this->viewport()->setCursor(Qt::SizeVerCursor);

		qreal offset = zoomInitialPos.x() - event->pos().x();
		if (offset > previousMouseOffset) {
			previousMouseOffset = offset;
			zoomDirection = -1;
			zoomIncr -= 1;
		}
		else if (abs(offset - previousMouseOffset) < 0.0001) {
			previousMouseOffset = offset;
			if (zoomDirection == -1) {
				zoomDirection = -1;
			}
			else zoomDirection = 1;
		}
		else {
			previousMouseOffset = offset;
			zoomDirection = 1;
			zoomIncr += 1;
		}

		qreal zoomFactor;
		if (zoomDirection == 1.0) zoomFactor = 1.05;
		else zoomFactor = 1 / 1.05;

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

void NODE_graphics_view::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) leftMouseReleaseEvent(event);
	else if (event->button() == Qt::RightButton && state != 1) {
		//show tab menu
		showContextMenu();
	}

    //zoom
    if(state == 1){
		this->viewport()->setCursor(Qt::ArrowCursor);
        zoomDirection = 0;
        zoomIncr = 0;
        setInteractive(true);
    }

    //drag View
    else if(state == 2){
        this->viewport()->setCursor(Qt::ArrowCursor);
        setInteractive(true);
    }
    state = 0;

    QGraphicsView::mouseReleaseEvent(event);
}

void NODE_graphics_view::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_1){
        if(canUseKey){
			onConnectToViewport();
        }
    }
    else if(event->key()==Qt::Key_F){
        onFocus();
    }

    QGraphicsView::keyPressEvent(event);
}

void NODE_graphics_view::leftMousePressEvent(QMouseEvent *event)
{

    //mousePos = mapToScene(event->pos());
    state = 0;
    setDragMode(QGraphicsView::RubberBandDrag);
	this->viewport()->setCursor(Qt::ArrowCursor);

    //action
    bool hasItem = false;
    QGraphicsItem *item;
    if((item = itemAt(event->pos()))){
        hasItem=true;
        setDragMode(QGraphicsView::NoDrag);
    }

    //change selection
    if(hasItem && event->modifiers() & Qt::ShiftModifier){
        qDebug()<<"set selected";
        QList<QGraphicsItem*> its = NODE_scene->selectedItems();
        bool selected = item->isSelected();
        item->setSelected(!selected);
        foreach(QGraphicsItem* it,its){
            it->setSelected(true);
        }
        return;
    }

    QGraphicsView::mousePressEvent(event);

    //create new line
    NODE_socket* socket= dynamic_cast<NODE_socket*>(item);

    if(socket){
        if(MODE == MODE_NOOP){
            MODE = MODE_LINE_DRAG;
            //edgeDragStart(item);
            dragLine = new NODE_line(this,socket,nullptr,true);
            canChangeDrag = true;
            startSocket = socket;
            return;
        }
        else if(MODE == MODE_LINE_DRAG){
            MODE = MODE_NOOP;
			bool res = dragEnd(socket);
            if(res) return;
        }
    }

    //click delete line
    if(MODE == MODE_NOOP){
        NODE_line* line= dynamic_cast<NODE_line*>(item);
        if(line){
            QPointF pos1 = line->inputSock->position();
            qDebug()<<"mousePos"<<mousePos;
            qDebug()<<"pos1"<<pos1;
            if(Qdistance(mousePos,pos1)<50){
                deleteOneLine(line);
            }
            else{
                QPointF pos2 = line->outputSock->position();
                qDebug()<<"pos2"<<pos2;
                if(Qdistance(mousePos,pos2)<50){
                    deleteOneLine(line);
                }
            }
        }
    }
	if (MODE == MODE_LINE_DRAG) {
		MODE = MODE_NOOP;
		if (adsorb) {
			dragEnd(adsorbSocket);
		}
		else {
			NODE_scene->removeItem(dragLine);
			delete dragLine;
			dragLine = nullptr;
		}
        NODE_scene->update();
        update();
    }
    //cut line and normal
    if(!hasItem){
        if(event->modifiers() & Qt::ControlModifier){
           MODE = MODE_LINE_CUT;
           cutline = new NODE_cutline;
           NODE_scene->addItem(cutline);
           this->viewport()->setCursor(Qt::CrossCursor);
           setDragMode(QGraphicsView::NoDrag);
        }
        else{
            //
        }
    }
}

void NODE_graphics_view::leftMouseReleaseEvent(QMouseEvent *event)
{
    //action
    bool hasItem = false;
    QGraphicsItem *item;
    if((item = itemAt(event->pos()))){
        hasItem=true;
        //setDragMode(QGraphicsView::NoDrag);
    }

    NODE_socket* socket= dynamic_cast<NODE_socket*>(item);
    if(socket && socket != startSocket){
        if(MODE == MODE_LINE_DRAG){
            bool res = dragEnd(socket);
            MODE = MODE_NOOP;
            if(res) return;
        }
    }
    if(MODE == MODE_LINE_CUT){
//        cutIntersectingEdges();
        for(int i=0;i<cutline->line_points.length()-1;i++){
            QPointF p1 = cutline->line_points[i];
            QPointF p2 = cutline->line_points[i + 1];
            foreach(NODE_line *line,NODE_scene->sceneLines){
                if(line->intersectsWith(p1,p2)){
                    if(!sceneTempLines.contains(line))
                        sceneTempLines.append(line);
                }
            }
        }
        deleteTempLine();
        cutline->line_points.clear();
        cutline->update();
        delete cutline;
        cutline = nullptr;
        NODE_scene->removeItem(cutline);
        this->viewport()->setCursor(Qt::ArrowCursor);
        setDragMode(QGraphicsView::RubberBandDrag);
        MODE = MODE_NOOP;
        return;
    }

    //(histort sclect change)
}

void NODE_graphics_view::dragMoveEvent(QDragMoveEvent *event)
{
    if(event->mimeData()->hasUrls()){
        event->accept();
    }
    else{
        event->ignore();
    }
}

void NODE_graphics_view::dropEvent(QDropEvent *event)
{
    QList<QString*> files;
    QPointF pos = mapToScene( event->pos());
    int count = 0;
    foreach(QUrl url,event->mimeData()->urls()){
        string path =  url.toLocalFile().toStdString();
        string format = getFormat(path);
        string name = getFilename(path);
        qDebug()<<QString::fromStdString(format);
        QPointF nodePos = pos+QPointF(0,count*300);
        if(isUsefulFormat("imageFormats",format))
            new NODE_item(this,QString::fromStdString(name),nodePos);
            count ++;
    }

}

QRectF NODE_graphics_view::_getSelectionBoundingbox(){
        qreal bbx_min=999;
        qreal bbx_max=999;
        qreal bby_min=999;
        qreal bby_max=999;
        qreal bbw = 0;
        qreal bbh = 0;

        foreach(QGraphicsItem* item,NODE_scene->selectedItems()){
            QPointF pos = item->scenePos();
            qreal x = pos.x();
            qreal y = pos.y();
            qreal w = x + item->boundingRect().width();
            qreal h = y + item->boundingRect().height();

            //bbx min
            if(abs(bbx_min-999)<0.0001) bbx_min = x;
            else if(x < bbx_min) bbx_min = x;
            //end if

            //bbx max
            if(abs(bbx_max-999)<0.0001) bbx_max = w;
            else if(w > bbx_max) bbx_max = w;
            //end if

            //bby min
            if(abs(bby_min-999)<0.0001) bby_min = y;
            else if(y < bby_min) bby_min = y;
            //end if

            //bby max
            if(abs(bby_max-999)<0.0001) bby_max = h;
            else if(h > bby_max)bby_max = h;
        }
        //end if
        bbw = bbx_max - bbx_min;
        bbh = bby_max - bby_min;
        return QRectF(bbx_min, bby_min, bbw, bbh);
}

void NODE_graphics_view::initFlags()
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //setRenderHint(QPainter::Antialiasing);
    //setDragMode(QGraphicsView::RubberBandDrag);
    //setOptimizationFlags(QGraphicsView::DontSavePainterState);
//    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    //setTransformationAnchor(QGraphicsView::AnchorUnderMouse);


    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
//    setCacheMode(QGraphicsView::CacheNone);
//    //setRenderHint(QPainter::Antialiasing);
    setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    setDragMode(QGraphicsView::RubberBandDrag);
    setCacheMode(QGraphicsView::CacheBackground);
    //setViewport(new QOpenGLWidget(this));
}

bool NODE_graphics_view::dragEnd(NODE_socket *socket)
{
    if(socket){
        if(socket != startSocket && startSocket->node != socket->node
            && startSocket->socketType != socket->socketType){
            //new NODE_line(NODE_scene,startSocket,socket);
            dragLine->endSock = socket;
            dragLine->isDrag = false;
            dragLine->updateSocket();
            dragLine->update();
            dragLine = nullptr;
            qDebug()<<"create finished drag line";
            //(history:create new line)
            //this->repaint();
            return true;
        }
    }
    deleteOneLine(dragLine);
    dragLine = nullptr;
    return false;
}

void NODE_graphics_view::clearSelected()
{
    foreach(QGraphicsItem *item,NODE_scene->selectedItems()){
        NODE_item* node= dynamic_cast<NODE_item*>(item);
        if(node && !sceneSelectedNodes.contains(node)){
            sceneSelectedNodes.append(node);
        }
    }
    qDebug()<<"selected node count"<<sceneSelectedNodes.length();

    foreach(NODE_item* node,sceneSelectedNodes){
        node->removeLine();
    }

    qDebug()<<"nodes deleted";
    //deleteTempLine();
    NODE_scene->update();

    foreach(QGraphicsItem *item,NODE_scene->selectedItems()){
        NODE_line* line= dynamic_cast<NODE_line*>(item);
        if(line && !sceneSelectedLines.contains(line)){
            sceneSelectedLines.append(line);
        }
    }
}

void NODE_graphics_view::deleteOneLine(NODE_line *line)
{
    sceneTempLines.append(line);
    deleteTempLine();
}

QList<NODE_item *> NODE_graphics_view::getSelectedNodes()
{
    QList<NODE_item*> nodes;
    foreach(QGraphicsItem *item,NODE_scene->selectedItems()){
        NODE_item* node= dynamic_cast<NODE_item*>(item);
        if(node){
            nodes.append(node);
        }
    }
    return nodes;
}

QList<NODE_line *> NODE_graphics_view::getSelectedLines()
{
    QList<NODE_line*> lines;
    foreach(QGraphicsItem *item,NODE_scene->selectedItems()){
        NODE_line* line= dynamic_cast<NODE_line*>(item);
        if(line){
            lines.append(line);
        }
    }
    return lines;
}

void NODE_graphics_view::deleteSelected()
{
    for(int i=0;i<sceneSelectedLines.length();i++){
        NODE_line*line = sceneSelectedLines[i];
        deleteLine(line);
        delete sceneSelectedLines[i];
        //sceneSelectedLines[i]->deleteLater();
        sceneSelectedLines[i] = nullptr;
    }
    sceneSelectedLines.clear();
    qDebug()<<"lines left:"<<sceneSelectedLines.length();

    for(int i=0;i<sceneSelectedNodes.length();i++){
        NODE_item*node = sceneSelectedNodes[i];
        deleteNode(node);
        delete sceneSelectedNodes[i];
        //sceneSelectedNodes[i]->deleteLater();
        sceneSelectedNodes[i] = nullptr;
    }
    sceneSelectedNodes.clear();
    qDebug()<<"nodes left:"<<sceneSelectedNodes.length();
}

void NODE_graphics_view::deleteTempLine()
{
    for(int i=0;i<sceneTempLines.length();i++){
        deleteLine(sceneTempLines[i]);
        delete sceneTempLines[i];
        //sceneTempLines[i]->deleteLater();
        sceneTempLines[i] = nullptr;
    }
    sceneTempLines.clear();
    qDebug()<<"temp lines left:"<<sceneTempLines.length();
}

void NODE_graphics_view::deleteLine(NODE_line *line)
{
    if(MODE!=MODE_LINE_DRAG) line->appendHistory("delete_line");
    if(NODE_scene->sceneLines.contains(line)) NODE_scene->sceneLines.removeOne(line);
    if(line->inputSock != nullptr) line->inputSock->outputLines.removeOne(line);
	if (line->outputSock != nullptr) {
		line->outputSock->inputLines.removeOne(line);
		line->outputSock->node->cook();
	}
    qDebug()<<"delete line"<<line->pos();

    line->isDeleted = true;
    line->setVisible(false);
    line->setSelected(false);
	//if(line.isD)
	
    NODE_scene->removeItem(line);
    //(history)
}

void NODE_graphics_view::deleteNode(NODE_item *node)
{
	if (node->name == "Viewport") {
		this->viewportNode = nullptr;
	}
    node->appendHistory("delete_node");
    NODE_scene->removeItem(node);
    NODE_scene->sceneNodes.removeOne(node);
    qDebug()<<"delete node"<<node->title;

	if (viewportNode == nullptr) {
		foreach(auto node, NODE_scene->sceneNodes) {
			if (node->name == "Viewport") {
				viewportNode = node;
				return;
			}
		}
	}
}

void NODE_graphics_view::createContextMenu()
{
	//setContextMenuPolicy(Qt::CustomContextMenu);
	//connect(this, &QWidget::customContextMenuRequested, this, [=]() {showContextMenu(); });

	QWidgetAction *search = new QWidgetAction(contextMenu);
	search->setDefaultWidget(searchLine);
	contextMenu->addAction(search);
	connect(searchLine, &QLineEdit::textChanged, this, [=]() {searchNode(); });
	connect(searchLine, &QLineEdit::returnPressed, this, [=]() {applySearch(); });
}

void NODE_graphics_view::showContextMenu()
{
	searchLine->setText("");
	searchLine->setFocus();
	contextMenu->exec(QCursor::pos());
}

void NODE_graphics_view::searchNode()
{
	QString text = searchLine->text();
	if (text == "") {
		clearSearch();
		foreach(QMenu *menu, allMenus) {
			menu->menuAction()->setVisible(true);
		}
	}
	else {
		foreach(QMenu *menu, allMenus) {
			menu->menuAction()->setVisible(false);
		}

		clearSearch();

		foreach(QAction *action, allActions) {
			if (action->objectName().toLower().startsWith(text.toLower())) {//if text in i :
				searchedActions.append(action);
				contextMenu->addAction(action);
			}
		}
	}
}

void NODE_graphics_view::applySearch()
{
	if (searchedActions.length() > 0) {
		QAction *action = searchedActions[0];
		contextMenu->setActiveAction(action);
	}
}

void NODE_graphics_view::clearSearch()
{
	foreach(QAction *action, searchedActions) {
		contextMenu->removeAction(action);
	}
	searchedActions.clear();
}