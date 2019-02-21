#include "Magic_Image.h"
#include <QMenuBar>
#include <QDebug>
#include <QLabel>
#include <QDockWidget>
#include <QTextEdit>
#include <QFrame>
#include <QFileDialog>
#include <QRgb>
#include "MI_utils.hpp"
#include <iostream>
#include <fstream>
#include <NODE_line.h>
#include <qmessagebox.h>
#include <Register.h>
#include <node_Viewport.h>
#include <json.hpp>
using json = nlohmann::json;
using namespace std;

MagicImage::MagicImage(QWidget *parent)
    : QMainWindow(parent)
{
    nodeView->installEventFilter(this);

    initUI();
    initSingalConnection();

}

void MagicImage::initUI()
{
    this->setWindowTitle("ARNO Magic Image");
    this->resize(1280,720);

    //菜单栏/状态栏
    initStyle();
    initMenuBar();
    initNodeWindow();
    initViewerWindow();
    initDock();
	onNew();

}

void MagicImage::initDock()
{
    //this->setDockOptions(QMainWindow::ForceTabbedDocks);
    this->setDockNestingEnabled(true);

    //parameter
    IMparam->setFrameShape(QFrame::StyledPanel);
    //self.setStyle(self.paramDock, "dock")
    paramDock->setWidget(IMparam);
    //paramDock->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetClosable);
    this->addDockWidget(Qt::RightDockWidgetArea, paramDock);

    //viewer
    viewerDock->setWidget(viewerWindow);
    //viewerDock->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetClosable);
    this->addDockWidget(Qt::LeftDockWidgetArea, viewerDock);

    //node editor
    nodeDock->setWidget(nodeWindow);
    //nodeDock->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetClosable);
    this->addDockWidget(Qt::BottomDockWidgetArea, nodeDock);
}

void MagicImage::initMenuBar()
{
    //菜单栏
    QMenuBar *mainMenuBar = menuBar();
    this->setMenuBar(mainMenuBar);
    QMenu *fileMenu =  mainMenuBar->addMenu("File");
    QMenu *editMenu =  mainMenuBar->addMenu("Edit");
    QMenu *windowsMenu =  mainMenuBar->addMenu("Windows");
	QMenu *helpMenu = mainMenuBar->addMenu("Help");

    //fileMenu
    QAction *New = createAct(fileMenu,"New","","Ctrl+N");
    QAction *Open = createAct(fileMenu,"Open","","Ctrl+O");
    fileMenu->addSeparator();
    QAction *Save = createAct(fileMenu,"Save","","Ctrl+S");
    QAction *Save_As = createAct(fileMenu,"Save As","","Ctrl+Shift+S");
    fileMenu->addSeparator();
    QAction *Close = createAct(fileMenu,"Close","","");
    connect(New,&QAction::triggered,this,[=](){onNew();});
    connect(Open,&QAction::triggered,this,[=](){onOpen();});
    connect(Save,&QAction::triggered,this,[=](){onSave();});
    connect(Save_As,&QAction::triggered,this,[=](){onSaveAs();});
    connect(Close,&QAction::triggered,this,&MagicImage::close);

    //windowMenu
    QAction *showViewer = createAct(windowsMenu,"Viewer","","");
    QAction *showParameters = createAct(windowsMenu,"Parameters","","");
    QAction *showNodeEditor = createAct(windowsMenu,"Node Editor","","");
    connect(showViewer,&QAction::triggered,this,[=](){viewerDock->show();});
    connect(showParameters,&QAction::triggered,this,[=](){paramDock->show();});
    connect(showNodeEditor,&QAction::triggered,this,[=](){nodeDock->show();});

    //edit Menu
    QAction *Undo = createAct(editMenu,"Undo","","Ctrl+Z");
    QAction *Redo = createAct(editMenu,"Redo","","Ctrl+Shift+Z");
    connect(Undo,&QAction::triggered,this,[=](){onUndo();});
    connect(Redo,&QAction::triggered,this,[=](){onRedo();});

	//help Menu
	QAction *About = createAct(helpMenu, "About", "", "");

    //状态栏
    this->setStatusBar(IMstatusBar);
//    QLabel *mesgLabel = new QLabel("Welcome!");
//    IMstatusBar->addWidget(mesgLabel);
    IMstatusBar->showMessage("Welcome!");
    IMstatusBar->setFixedHeight(20);
    IMstatusBar->setSizeGripEnabled(false);
}

void MagicImage::initNodeWindow()
{
    //nodeView
    nodeWindow->setCentralWidget(nodeView);
	nodeView->createContextMenu();

    //菜单栏
    QMenuBar *nodeMenuBar = new QMenuBar();
    nodeWindow->setMenuBar(nodeMenuBar);
	QMenu *viewMenu = nodeMenuBar->addMenu("View");
    QMenu *nodeMenu =  nodeMenuBar->addMenu("Node");
    QMenu *addMenu =  nodeMenuBar->addMenu("Add");

	//view menu
	QAction *Toggle = createAct(viewMenu, "Toggle Line Type", "", "");
	connect(Toggle, &QAction::triggered, this, [=]() {
		bool tp = nodeView->lineType;
		nodeView->lineType = !tp;
		nodeView->update();
		; });

    //node menu
    QAction *Copy = createAct(nodeMenu,"Copy","","Ctrl+C");
    QAction *Pase = createAct(nodeMenu,"Pase","","Ctrl+V");
    QAction *CopyPase = createAct(nodeMenu,"Copy and Pasre","","Ctrl+D");
    QAction *Cut = createAct(nodeMenu,"Copy","","Ctrl+X");
    nodeMenu->addSeparator();
    QAction *Delete = createAct(nodeMenu,"Delete Selected","","Del");
    QAction *Disable = createAct(nodeMenu,"Disable Selected","","D");
    QAction *Independent = createAct(nodeMenu,"Independent Selected","","X");
    nodeMenu->addSeparator();
    QAction *CtoV = createAct(nodeMenu,"Connect to viewport","","1");
    //QAction *Focus = createAct(nodeMenu,"Focus","","F");
    connect(Copy,&QAction::triggered,this,[=](){nodeView->onCopy();});
    connect(Pase,&QAction::triggered,this,[=](){nodeView->onPase();});
    connect(CopyPase,&QAction::triggered,this,[=](){nodeView->onCopyPase();});
    connect(Cut,&QAction::triggered,this,[=](){nodeView->onCut();});
    connect(Delete,&QAction::triggered,this,[=](){nodeView->onDeleteSelected();});
    connect(Disable,&QAction::triggered,this,[=](){nodeView->onDisable();});
    connect(Independent,&QAction::triggered,this,[=](){nodeView->onIndependent();});
    connect(CtoV,&QAction::triggered,this,[=](){nodeView->onConnectToViewport();});
    //connect(Focus,&QAction::triggered,this,[=](){nodeView->onFocus();});

    
	nodeMenuBar->setStyleSheet(QString("QMenuBar::item {background-color:%1;color:rgb(220,220,220);}"
		"QMenuBar {background-color:%1;}"
		"QMenuBar::item::selected {background-color: %2;}"
	).arg(getRGB("color_background_dark")).arg(getRGB("color_background_orange")));


	//add menu
	QList<QString > menuNames;
	QList<QMenu *> menuObjects;
	for (auto& info : Menus.items())
	{
		auto ndInfo = info.value();
		QString name = QString::fromStdString(ndInfo["name"]);
		QString menuName = QString::fromStdString(ndInfo["menuName"]);
		QString key = QString::fromStdString(ndInfo["key"]);

		QAction *newAction;
		if (!menuNames.contains(menuName)) {
			menuNames.append(menuName);
			QMenu *newMenu = addMenu->addMenu(menuName);
			newAction = createAct(newMenu, name, "", key);
			connect(newAction, &QAction::triggered,this,[=]() {this->onCreateNode(name.toStdString());});

			nodeView->contextMenu->addMenu(newMenu);
			menuObjects.append(newMenu);
			newMenu->setObjectName(menuName);
			newAction->setObjectName(name);

			nodeView->allMenus.append(newMenu);
			nodeView->allActions.append(newAction);
		}
		else {
			foreach(QMenu *mn, menuObjects) {
				if (mn->objectName() == menuName) {
					newAction = createAct(mn, name, "", key);
					connect(newAction, &QAction::triggered, this, [=]() {this->onCreateNode(name.toStdString()); });
					newAction->setObjectName(name);
					nodeView->allActions.append(newAction);
					break;
				}
			}
		}

	}
	menuNames.clear();
	menuObjects.clear();
}

void MagicImage::initViewerWindow()
{
    viewerGraphicsview->VI_graphics_scene->addWidget(viewer);
    //QHBoxLayout *layput = new QHBoxLayout;
    //viewerWindow->setLayout(layout());
    viewerWindow->setCentralWidget(viewerGraphicsview);
    //status bar
    viewerWindow->setStatusBar(viewerStatusBar);
    viewerStatusBar->addPermanentWidget(rLabel);
    viewerStatusBar->addPermanentWidget(gLabel);
    viewerStatusBar->addPermanentWidget(bLabel);
    viewerStatusBar->addPermanentWidget(aLabel);
    rLabel->setText("0.00000");
    gLabel->setText("0.00000");
    bLabel->setText("0.00000");
    aLabel->setText("1.00000");

    viewerStatusBar->setFixedHeight(20);
    viewerStatusBar->setSizeGripEnabled(false);
}

void MagicImage::initSingalConnection()
{
    connect(viewer,&VI_image_viever::move,[=](QMouseEvent *event){
        QString msg = QString("x=%1,y=%2").arg(event->pos().x()).arg(event->pos().y());
        viewerStatusBar->showMessage(msg);
        QRgb imgRgb = viewer->mainImage->pixel(event->pos().x(),event->pos().y());
        qreal r,g,b,a;
        QColor(imgRgb).getRgbF(&r,&g,&b,&a);
        rLabel->setText(QString::number(r));
        gLabel->setText(QString::number(g));
        bLabel->setText(QString::number(b));
        aLabel->setText(QString::number(a));


    });

    connect(viewer,&VI_image_viever::click,[=](QMouseEvent *event){
        QString msg = QString("click:(%1,%2)").arg(event->pos().x()).arg(event->pos().y());
        this->IMstatusBar->showMessage(msg);
    });
}

bool MagicImage::eventFilter(QObject *target, QEvent *event)
{
    if (target == nodeView )
    {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Tab)
            {
				nodeView->showContextMenu();
                return true;
            }
        }
    }
    return QMainWindow::eventFilter(target, event);
}

void MagicImage::changeTitle()
{
    QString title = "ANRO Magic Image - ";
    if(projectName==nullptr)
        title += "New";
    else
      title += projectName.split("/").last();
//    if self.nodeScene.has_been_modified:
//        title += "*"

    setWindowTitle(title);
}

void MagicImage::onSave()
{
    if(projectName==nullptr){
        onSaveAs();
        return;
    }
    save();
}

void MagicImage::onSaveAs()
{
    QString fileName =
      QFileDialog::getSaveFileName(nullptr,
                                   tr("Save Project"),
                                   QDir::homePath(),
                                   tr("Project File (*.mag)"));

    if (!fileName.isEmpty())
    {
        if (!fileName.endsWith("mag", Qt::CaseInsensitive)){
            fileName += ".mag";
        }
        projectName = fileName;
        save();
        changeTitle();
		isModified = false;
    }
}

void MagicImage::save()
{
    qDebug()<<projectName;
    json projectInfo;
    projectInfo["sceneInfo"] = saveScene();
    qDebug()<<"all saved";
    std::ofstream file(projectName.toStdString());
    file << projectInfo.dump(4);

	isModified = false;
    IMstatusBar->showMessage("Save Successfully!");
}

void MagicImage::onNew(bool loadProject)
{
    nodeView->NODE_scene->clear();
    nodeView->NODE_scene->sceneNodes.clear();
    nodeView->NODE_scene->sceneLines.clear();
    nodeView->sceneTempLines.clear();
    nodeView->sceneSelectedLines.clear();
    nodeView->sceneSelectedNodes.clear();
	if(!loadProject) onCreateNode("Viewport");
    history.clear();
    history_index = 0;
	if(Menus.size()>0) Menus.clear();
	isModified = false;
}

void MagicImage::onOpen()
{
    QString path;
    if(projectName!=nullptr) path = projectName.toCaseFolded();
    else path = QDir::homePath();

    QString fileName =
      QFileDialog::getOpenFileName(nullptr,
                                   tr("Open Project"),
                                   path,
                                   tr("Project File (*.mag)"));
    if (!fileName.isEmpty()){
        onNew(true);
        std::fstream ifs(fileName.toStdString());
        if (!ifs) {
            std::cout << "*ERROR** Could not read input file " << "defalut_config" << "\n"<<std::endl;;
          }
        json project = json::parse(ifs);
        json sceneInfo = project["sceneInfo"];
        load(sceneInfo);
        projectName = fileName;
        changeTitle();
		isModified = false;
    }
}

void MagicImage::onUndo()
{
    cout<<"history size: "<<history.size()<<endl;
    if(history_index>int(history.size()-1)) return;
    if(history_index<0 || history.size()<1) return;

    int index = history_index;

    //cout<<history[history_index]<<endl;
    json info = history[size_t(history_index)];
    string h_name = info["history_name"];
    QString history_name = QString::fromStdString(h_name);
    json history_content = info[h_name];

    if(history_name=="move_item"){
        size_t id = history_content["id"];
        foreach(NODE_item*node,nodeView->NODE_scene->sceneNodes){
            if(node->id==id)
                node->setPos(QPointF(history_content["prePos_x"],history_content["prePos_y"]));
        }
        qDebug()<<"undo move item";
    }
    else if(history_name=="create_node"){
        size_t id = history_content["id"];
        foreach(NODE_item*node,nodeView->NODE_scene->sceneNodes){
            if(node->id==id){
                nodeView->sceneSelectedNodes.append(node);
                nodeView->deleteSelected();
                goto end_ci;
            }
        }
        end_ci:
        history.erase(history.size()-1);
        qDebug()<<"undo not create_node";
    }
    else if(history_name == "delete_node"){
		loadNode(history_content);
        history.erase(history.size()-1);
        qDebug()<<"undo not delete_node";
    }
    else if(history_name == "create_line"){
		QPointF outPos = QPointF(history_content["outPos_x"], history_content["outPos_y"]);
		foreach(QGraphicsItem* item1, nodeView->NODE_scene->items(outPos)) {
			NODE_socket *socket = dynamic_cast<NODE_socket*>(item1);
			if (socket) {
				socket->removeAll();
				break;
			}
		}

        history.erase(history.size()-1);
        qDebug()<<"undo not create_line";
    }
    else if(history_name == "delete_line"){
        loadLine(history_content);
        history.erase(history.size()-1);
        qDebug()<<"undo not delete_line";
    }

    qDebug()<<history_name;
    //cout<<"history content: "<<history_content<<endl;
    cout<<"history index: "<<history_index<<endl;
    history_index = index - 1;
}

void MagicImage::onRedo()
{
    cout<<"history size: "<<history.size()<<endl;
    if(history_index > int(history.size()-1)) return;
    if(history_index<0 || history.size()<1) return;

    int index = history_index;
    //cout<<history[history_index]<<endl;
    json info = history[size_t(history_index)];
    string h_name = info["history_name"];
    QString history_name = QString::fromStdString(h_name);
    json history_content = info[h_name];

    if(history_name=="move_item"){
        size_t id = history_content["id"];
        foreach(NODE_item*node,nodeView->NODE_scene->sceneNodes){
            if(node->id==id)
                node->setPos(QPointF(history_content["pos_x"],history_content["pos_y"]));
        }
        qDebug()<<"redo move item";
    }
    else if(history_name=="create_node"){
		loadNode(history_content);
        history.erase(history.size()-1);
        qDebug()<<"redo create_node";
    }
    else if(history_name == "delete_node"){
        size_t id = history_content["id"];
        foreach(NODE_item*node,nodeView->NODE_scene->sceneNodes){
            if(node->id==id){
                nodeView->sceneSelectedNodes.append(node);
                nodeView->deleteSelected();
                goto end_ci;
            }
        }
        end_ci:
        history.erase(history.size()-1);
        qDebug()<<"redo delete_node";
    }
    else if(history_name == "create_line"){
        loadLine(history_content);
        history.erase(history.size()-1);
        qDebug()<<"redo create_line";
    }
    else if(history_name == "delete_line"){
        QPointF outPos = QPointF(history_content["outPos_x"], history_content["outPos_y"]);
		foreach(QGraphicsItem* item1, nodeView->NODE_scene->items(outPos)) {
			NODE_socket *socket = dynamic_cast<NODE_socket*>(item1);
			if (socket) {
				socket->removeAll();
				break;
			}
		}
        history.erase(history.size()-1);
        qDebug()<<"redo delete_line";
    }

    qDebug()<<history_name;
    cout<<"history index: "<<history_index<<endl;
    history_index= index + 1;
}

void MagicImage::closeEvent(QCloseEvent *event)
{
	if (isModified) {
		QMessageBox *msg = new QMessageBox();
		msg->setStyleSheet(QString("QLabel{min-width:600 px; font-size: 18px;background-color:%3;color:rgb(230,230,230)}"
			"QPushButton{ width:100px; font-size: 18px;background-color:%2;color:rgb(230,230,230)}"
			"QPushButton:hover{ width:100px; font-size: 18px;background-color:%1;color:rgb(230,230,230)}"
			"QPushButton:pressed{ width:100px; font-size: 18px;background-color:%4;color:rgb(230,230,230)}"
			"QMessageBox{background-color:%3;color:rgb(230,230,230)}"
		).arg(getRGB("color_background_light")).arg(getRGB("color_background")).arg(getRGB("color_background_dark"))
	    .arg(getRGB("color_background_orange")));

		msg->setWindowTitle("Magic Image Information");
		msg->setInformativeText("The current project has changed.Would you like to save change?");
		msg->setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		int res = msg->exec();
		if (res == QMessageBox::Yes) {
			onSave();
			event->accept();
		}
		else if (res == QMessageBox::Cancel) {
			event->ignore();
			return;
		}
		event->accept();
	}
}

NODE_item* MagicImage::onCreateNode(string name)
{
	auto node = factory::get().produce(name);
	node->nodeView = nodeView;
	node->loadToScene();
	nodeView->state = 0;
	node->setPos(nodeView->mousePos);
	qDebug() << "create node: " << QString::fromStdString(name);

	if (name == "Viewport") {
		node_Viewport *vp = static_cast<node_Viewport *>(node);
		nodeView->viewportNode = vp;
		vp->viewer = viewer;
	}
	return node;
}

json MagicImage::saveScene()
{
	qDebug() << "start save";
	json sceneInfo = json::object();
	json nodeInfo = json::array();
	json lineInfo = json::array();

	foreach(NODE_item* node, nodeView->NODE_scene->sceneNodes) {
		json nodeJson = node->save();
		nodeInfo.push_back(nodeJson);
	}
	qDebug() << "nodes saved";
	foreach(NODE_line* line, nodeView->NODE_scene->sceneLines) {
		json lineJson = line->save();
		lineInfo.push_back(lineJson);
	}
	qDebug() << "lines saved";

	json nodeEditorInfo = json::object();
	nodeEditorInfo["lineType"] = nodeView->lineType;

	sceneInfo["Nodes"] = nodeInfo;
	sceneInfo["Lines"] = lineInfo;
	sceneInfo["nodeEditor"] = nodeEditorInfo;
	return sceneInfo;
}

void MagicImage::load(json sceneInfo)
{
	json nodeInfo = sceneInfo["Nodes"];
	json lineInfo = sceneInfo["Lines"];
	json nodeEditorInfo = sceneInfo["nodeEditor"];
	bool lType = nodeEditorInfo["lineType"];
	nodeView->lineType = lType;

	for (auto& info : nodeInfo.items())
	{
		auto ndInfo = info.value();
		loadNode(ndInfo);
	}

	for (auto& info : lineInfo.items())
	{
		auto liInfo = info.value();
		loadLine(liInfo);
	}
}

void MagicImage::loadNode(json ndInfo)
{
	string name = ndInfo["name"];
	auto node = onCreateNode(name);
	node->load(ndInfo);
}

void MagicImage::loadLine(json liInfo)
{
	QPointF inPos = QPointF(liInfo["inPos_x"], liInfo["inPos_y"]);
	QPointF outPos = QPointF(liInfo["outPos_x"], liInfo["outPos_y"]);
	//QPointF range = QPointF(10,10);

	int count = 0;
	NODE_socket *inSocket = nullptr;
	NODE_socket *outSocket = nullptr;

	foreach(QGraphicsItem* item1, nodeView->NODE_scene->items(inPos)) {//QRectF(inPos - range, inPos + range)
		NODE_socket *socket1 = dynamic_cast<NODE_socket*>(item1);
		if (socket1) {
			count++;
			inSocket = socket1;
			break;
		}
	}
	foreach(QGraphicsItem* item2, nodeView->NODE_scene->items(outPos)) {//QRectF(outPos - range, outPos + range)
		NODE_socket *socket2 = dynamic_cast<NODE_socket*>(item2);
		if (socket2) {
			count++;
			outSocket = socket2;
			break;
		}
	}

	if (count == 2) new NODE_line(nodeView, inSocket, outSocket);
	else qDebug() << "create Line error!!  "<<count;
}

void MagicImage::initStyle()
{
    this->setStyleSheet(QString(
     "QMainWindow{background-color:%1;border:0px groove gray;}"
     "QWidget{background-color:%1;border:0.5px solid rgb(60,60,60);}"
     "QTabBar::tab{background-color:%3;color:rgb(230,230,230)}"
     "QTabBar::tab:selected, QTabBar::tab:hover {background-color:%2;}"
     "QMenu{background-color:%2;color:rgb(230,230,230);}"
     "QMenu::item::selected {background-color: %4;}"
     "QMenuBar::item {background-color:%1;color:rgb(220,220,220);}"
     "QMenuBar {background-color:%1;}"
     "QMenuBar::item::selected {background-color: %2;}"
     )
     .arg(getRGB("color_background_dark")).arg(getRGB("color_background_light")).arg(getRGB("color_background")).arg(getRGB("color_background_orange")));

    rLabel->setStyleSheet("background-color:transparent;font-size:12px;color:red;border:0px");
    gLabel->setStyleSheet("background-color:transparent;font-size:12px;color:green;border:0px");
    bLabel->setStyleSheet("background-color:transparent;font-size:12px;color:blue;border:0px");
    aLabel->setStyleSheet("background-color:transparent;font-size:12px;color:white;border:0px");

    viewerStatusBar->setStyleSheet(QString("QStatusBar::item {border: None;}""QStatusBar{background-color:%1;color:rgb(230,230,230);border: 0px solid black;"
                                  "border-radius: 0px;font-size:12px;}")
                                   .arg(getRGB("color_background_dark")));

    IMstatusBar->setStyleSheet(QString("background-color:%1;color:rgb(230,230,230);border: 0px solid black;"
                                       "border-radius: 0px;font-size:12px;")
                                        .arg(getRGB("color_background_dark")));

    viewerGraphicsview->scene()->setBackgroundBrush(getColor("color_background"));
    nodeView->scene()->setBackgroundBrush(getColor("color_background"));

    paramDock->setStyleSheet(QString("background-color:%1;color:rgb(200,200,200);").arg(getRGB("color_background_light")));
    viewerDock->setStyleSheet(QString("background-color:%1;color:rgb(200,200,200);").arg(getRGB("color_background_light")));
    nodeDock->setStyleSheet(QString("background-color:%1;color:rgb(200,200,200);").arg(getRGB("color_background_light")));

    viewer->setStyleSheet("QLabel{background-color:rgb(30,30,30);border: 0px solid #32414B;padding: 0px;margin: 0px;color: black}");

	nodeView->contextMenu->setStyleSheet(QString("background-color:%2;selection-background-color:%1;color:rgb(220,220,220);"
	).arg(getRGB("color_background_orange")).arg(getRGB("color_background_light")));

	nodeView->searchLine->setStyleSheet("border: 0.5px solid rgb(100,100,100);border-radius: 0px;font-size:12px;");
}

