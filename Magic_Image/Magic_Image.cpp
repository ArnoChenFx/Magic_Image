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
#include <json.hpp>
using json = nlohmann::json;
using namespace std;

MagicImage::MagicImage(QWidget *parent)
    : QMainWindow(parent)
{
    nodeView->installEventFilter(this);

    initUI();
    initSingalConnection();

	//TEST
	size_t size = Menus.size();
	qDebug() <<"NODE1 NAME" << QString::fromStdString(Menus[0]["name"]);
	qDebug() <<"NODE2 NAME" << QString::fromStdString(Menus[1]["name"]);

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

}

void MagicImage::initDock()
{
    //this->setDockOptions(QMainWindow::ForceTabbedDocks);
    this->setDockNestingEnabled(true);

    //parameter
    IMparam->setFrameShape(QFrame::StyledPanel);
    //self.setStyle(self.paramDock, "dock")
    paramDock->setWidget(IMparam);
    paramDock->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetClosable);
    this->addDockWidget(Qt::RightDockWidgetArea, paramDock);

    //viewer
    viewerDock->setWidget(viewerWindow);
    viewerDock->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetClosable);
    this->addDockWidget(Qt::LeftDockWidgetArea, viewerDock);

    //node editor
    nodeDock->setWidget(nodeWindow);
    nodeDock->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetClosable);
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
    //菜单栏
    QMenuBar *nodeMenuBar = new QMenuBar();
    nodeWindow->setMenuBar(nodeMenuBar);
    QMenu *nodeMenu =  nodeMenuBar->addMenu("Node");
    QMenu *addMenu =  nodeMenuBar->addMenu("Add");

    //node menu
    QAction *Copy = createAct(nodeMenu,"Copy","","Ctrl+C");
    QAction *Pase = createAct(nodeMenu,"Pase","","Ctrl+V");
    QAction *CopyPase = createAct(nodeMenu,"Copy and Pasre","","Ctrl+D");
    QAction *Cut = createAct(nodeMenu,"Copy","","Ctrl+X");
    nodeMenu->addSeparator();
    QAction *Delete = createAct(nodeMenu,"Delete Selected","","Del");
    QAction *Disable = createAct(nodeMenu,"Disable Selected","","D");
    QAction *Independent = createAct(nodeMenu,"Independent Selected","","Shift+X");
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

    //add menu

    nodeMenuBar->setStyleSheet(QString("QMenuBar::item {background-color:%1;color:rgb(220,220,220);}"
                                       "QMenuBar {background-color:%1;}"
                                       "QMenuBar::item::selected {background-color: %2;}"
                                       ).arg(getRGB("color_background2")).arg(getRGB("color_background3")));
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

MagicImage::~MagicImage()
{

}

bool MagicImage::eventFilter(QObject *target, QEvent *event)
{
    if (target == nodeView )
    {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Tab)
            {
                qDebug()<<"TAB";
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
    }
}

void MagicImage::save()
{
    qDebug()<<projectName;
    json projectInfo;
    projectInfo["sceneInfo"] = nodeView->NODE_scene->save();
    qDebug()<<"all saved";
    std::ofstream file(projectName.toStdString());
    file << projectInfo.dump(4);

    IMstatusBar->showMessage("Save Successfully!");
}

void MagicImage::onNew()
{
    nodeView->NODE_scene->clear();
    nodeView->NODE_scene->sceneNodes.clear();
    nodeView->NODE_scene->sceneLines.clear();
    nodeView->sceneTempLines.clear();
    nodeView->sceneSelectedLines.clear();
    nodeView->sceneSelectedNodes.clear();
    history.clear();
    history_index = 0;
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
        onNew();
        std::fstream ifs(fileName.toStdString());
        if (!ifs) {
            std::cout << "*ERROR** Could not read input file " << "defalut_config" << "\n"<<std::endl;;
          }
        json project = json::parse(ifs);
        json sceneInfo = project["sceneInfo"];
        nodeView->NODE_scene->load(sceneInfo);
        projectName = fileName;
        changeTitle();
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
        nodeView->NODE_scene->loadNode(history_content);
        history.erase(history.size()-1);
        qDebug()<<"undo not delete_node";
    }
    else if(history_name == "create_line"){
        QString outSocketName = QString::fromStdString(history_content["outputSocket"]);
        size_t id = history_content["outputNode"];
        foreach(NODE_item* node,nodeView->NODE_scene->sceneNodes){
            if(node->id==id){
                foreach(NODE_socket *socket,node->input_sockets){
                    if(socket->name==outSocketName){
                        socket->removeAll();
                        goto end_cl;
                    }
                }
            }
        }
        end_cl:
        history.erase(history.size()-1);
        qDebug()<<"undo not create_line";
    }
    else if(history_name == "delete_line"){
        nodeView->NODE_scene->loadLine(history_content);
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
        nodeView->NODE_scene->loadNode(history_content);
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
        nodeView->NODE_scene->loadLine(history_content);
        history.erase(history.size()-1);
        qDebug()<<"redo create_line";
    }
    else if(history_name == "delete_line"){
        QString outSocketName = QString::fromStdString(history_content["outputSocket"]);
        size_t id = history_content["outputNode"];
        foreach(NODE_item* node,nodeView->NODE_scene->sceneNodes){
            if(node->id==id){
                foreach(NODE_socket *socket,node->input_sockets){
                    if(socket->name==outSocketName){
                        socket->removeAll();
                        goto end_cl;
                    }
                }
            }
        }
        end_cl:
        history.erase(history.size()-1);
        qDebug()<<"redo delete_line";
    }

    qDebug()<<history_name;
    cout<<"history index: "<<history_index<<endl;
    history_index= index + 1;
}

void MagicImage::initStyle()
{
    this->setStyleSheet(QString(
     "QMainWindow{background-color:%1;border:0px groove gray;}"
     "QWidget{background-color:%1;border:0.5px solid rgb(60,60,60);}"
     "QTabBar::tab{background-color:%3;color:rgb(230,230,230)}"
     "QTabBar::tab:selected, QTabBar::tab:hover {background-color:%2;}"
     "QMenu{background-color:%2;color:rgb(230,230,230);}"
     "QMenu::item::selected {background-color: %3;}"
     "QMenuBar::item {background-color:%1;color:rgb(220,220,220);}"
     "QMenuBar {background-color:%1;}"
     "QMenuBar::item::selected {background-color: %2;}"
     )
     .arg(getRGB("color_background2")).arg(getRGB("color_background3")).arg(getRGB("color_background")));

    rLabel->setStyleSheet("background-color:transparent;font-size:12px;color:red;border:0px");
    gLabel->setStyleSheet("background-color:transparent;font-size:12px;color:green;border:0px");
    bLabel->setStyleSheet("background-color:transparent;font-size:12px;color:blue;border:0px");
    aLabel->setStyleSheet("background-color:transparent;font-size:12px;color:white;border:0px");

    viewerStatusBar->setStyleSheet(QString("QStatusBar::item {border: None;}""QStatusBar{background-color:%1;color:rgb(230,230,230);border: 0px solid black;"
                                  "border-radius: 0px;font-size:12px;}")
                                   .arg(getRGB("color_background2")));

    IMstatusBar->setStyleSheet(QString("background-color:%1;color:rgb(230,230,230);border: 0px solid black;"
                                       "border-radius: 0px;font-size:12px;")
                                        .arg(getRGB("color_background2")));

    viewerGraphicsview->scene()->setBackgroundBrush(getColor("color_background"));
    nodeView->NODE_scene->setBackgroundBrush(getColor("color_background"));

    paramDock->setStyleSheet(QString("background-color:%1;color:rgb(200,200,200);").arg(getRGB("color_background3")));
    viewerDock->setStyleSheet(QString("background-color:%1;color:rgb(200,200,200);").arg(getRGB("color_background3")));
    nodeDock->setStyleSheet(QString("background-color:%1;color:rgb(200,200,200);").arg(getRGB("color_background3")));

    viewer->setStyleSheet("QLabel{background-color:rgb(30,30,30);border: 0px solid #32414B;padding: 0px;margin: 0px;color: black}");

}

