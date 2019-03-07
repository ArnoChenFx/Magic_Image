#include "nodeWindow.h"
#include <QMenuBar>
#include <QDebug>
#include <QMenuBar>
#include "Magic_Image.h"
#include <Register.h>
#include "TDWindow.h"
#include "OpenGLScene.h"
#include <node_Viewport.h>
#include <node_Image.h>
#include <Image_basic.h>
#include <node_Model.h>
using namespace std;

nodeWindow::nodeWindow(MagicImage * mainW) : QDockWidget("Node Editor", mainW)
{
	mainWindow = mainW;
	mainWindow->addDockWidget(Qt::BottomDockWidgetArea, this);
	//this->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetClosable);
	this->setObjectName("nodeWindow");

	//nodeView
	nodeView = new NODE_graphics_view;
	nodeView->createContextMenu();
	nodeMainWindow = new QMainWindow;
	nodeMainWindow->setCentralWidget(nodeView);
	this->setWidget(nodeMainWindow);
	//nodeView->installEventFilter(mainWindow);

	//²Ëµ¥À¸
	QMenuBar *nodeMenuBar = new QMenuBar();
	nodeMainWindow->setMenuBar(nodeMenuBar);
	QMenu *viewMenu = nodeMenuBar->addMenu("View");
	QMenu *nodeMenu = nodeMenuBar->addMenu("Node");
	QMenu *addMenu = nodeMenuBar->addMenu("Add");

	//view menu
	QAction *Toggle = createAct(viewMenu, "Toggle Line Type", "", "");
	connect(Toggle, &QAction::triggered, this, [=]() {
		bool tp = nodeView->lineType;
		nodeView->lineType = !tp;
		nodeView->update();
		; });

	//node menu
	QAction *Copy = createAct(nodeMenu, "Copy", "", "Ctrl+C");
	QAction *Pase = createAct(nodeMenu, "Pase", "", "Ctrl+V");
	QAction *CopyPase = createAct(nodeMenu, "Copy and Pasre", "", "Ctrl+D");
	QAction *Cut = createAct(nodeMenu, "Copy", "", "Ctrl+X");
	nodeMenu->addSeparator();
	QAction *Delete = createAct(nodeMenu, "Delete Selected", "", "Del");
	QAction *Disable = createAct(nodeMenu, "Disable Selected", "", "D");
	QAction *Independent = createAct(nodeMenu, "Independent Selected", "", "X");
	nodeMenu->addSeparator();
	QAction *CtoV = createAct(nodeMenu, "Connect to viewport", "", "1");
	//QAction *Focus = createAct(nodeMenu,"Focus","","F");
	connect(Copy, &QAction::triggered, this, [=]() {nodeView->onCopy(); });
	connect(Pase, &QAction::triggered, this, [=]() {nodeView->onPase(); });
	connect(CopyPase, &QAction::triggered, this, [=]() {nodeView->onCopyPase(); });
	connect(Cut, &QAction::triggered, this, [=]() {nodeView->onCut(); });
	connect(Delete, &QAction::triggered, this, [=]() {nodeView->onDeleteSelected(); });
	connect(Disable, &QAction::triggered, this, [=]() {nodeView->onDisable(); });
	connect(Independent, &QAction::triggered, this, [=]() {nodeView->onIndependent(); });
	connect(CtoV, &QAction::triggered, this, [=]() {nodeView->onConnectToViewport(); });
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
			connect(newAction, &QAction::triggered, this, [=]() {this->onCreateNode(name.toStdString()); });

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
	
	this->initStyle();
	this->connectSignals();
}



nodeWindow::~nodeWindow()
{

}


NODE_item* nodeWindow::onCreateNode(std::string name)
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
		connect(vp, &node_Viewport::cookImage, this, [=]() {mainWindow->cookImage(); });
	}
	else if (name == "Model") {
		node_Model *md = static_cast<node_Model *>(node);
		connect(md, &node_Model::loadM, this, [=]() {
			this->mainWindow->TDWid->glScene->models.append(md->geo);
			mainWindow->TDWid->glScene->renderNow();
			qDebug() << "load model"<< this->mainWindow->TDWid->glScene->models.size();
		});
		connect(md, &node_Model::destroyM, this, [=]() {
			if (this->mainWindow->TDWid->glScene->models.contains(md->geo)) {
				this->mainWindow->TDWid->glScene->models.removeOne(md->geo);
				mainWindow->TDWid->glScene->renderNow();
				qDebug() << "remove model";
			}
		});
	}
	node->cook();
	return node;
}

void nodeWindow::onDrop()
{
	QList<string> files = nodeView->files;
	QPointF pos = nodeView->mousePos;
	int count = 0;
	foreach(string path, files) {
		string format = getFormat(path);
		string name = getFilename(path);
		qDebug() << QString::fromStdString(format);
		QPointF nodePos = pos + QPointF(0, count * 300);
		if (isUsefulFormat("imageFormats", format)) {
			node_Image *node = dynamic_cast<node_Image*>(onCreateNode("Image"));
			node->title = QString::fromStdString(name);
			node->pathLine->setText(QString::fromStdString(path));
			node->setPos(nodePos);
			node->filePath = path;
			node->cook();
			count++;
		}
	}
	nodeView->files.clear();
}


QAction* nodeWindow::createAct(QMenu *menu, QString name, QString tooltip, QString shortcut) {
	QAction *act = new QAction;
	if (shortcut != "") act->setShortcut(QKeySequence(shortcut));
	act->setText(name);
	act->setToolTip(tooltip);
	menu->addAction(act);
	return act;
}



void nodeWindow::connectSignals()
{
	connect(nodeView, &NODE_graphics_view::drop, this, [=]() {this->onDrop(); });
}

void nodeWindow::initStyle()
{
	this->setStyleSheet(QString("background-color:%1;color:rgb(200,200,200);").arg(getRGB("color_background_light")));

	nodeView->scene()->setBackgroundBrush(getColor("color_background"));
	nodeView->contextMenu->setStyleSheet(QString("background-color:%2;selection-background-color:%1;color:rgb(220,220,220);"
	).arg(getRGB("color_background_orange")).arg(getRGB("color_background_light")));

	nodeView->searchLine->setStyleSheet("border: 0.5px solid rgb(100,100,100);border-radius: 0px;font-size:12px;");
}