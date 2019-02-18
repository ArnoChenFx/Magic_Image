#pragma once

#include <QMainWindow>
#include <QStatusBar>
#include <QFrame>
#include "VI_image_viever.h"
#include "NODE_graphics_view.h"
#include "VI_graphics_view.h"
#include <string>
#include <QDockWidget>

class MagicImage : public QMainWindow
{
    Q_OBJECT

public:
    VI_image_viever *viewer = new VI_image_viever;
    VI_graphics_view *viewerGraphicsview = new VI_graphics_view;
    NODE_graphics_view *nodeView = new NODE_graphics_view();

    QMainWindow *nodeWindow = new QMainWindow;
    QMainWindow *viewerWindow = new QMainWindow;

    QStatusBar *IMstatusBar =new QStatusBar;
    QFrame *IMparam = new QFrame;

    MagicImage(QWidget *parent = nullptr);
    ~MagicImage();

private:
    QString projectName=nullptr;

    void initUI();
    void initDock();
    void initMenuBar();
    void initNodeWindow();
    void initViewerWindow();
    void initSingalConnection();
    bool eventFilter(QObject *target, QEvent *qevent);

    void changeTitle();
    void onSave();
    void onSaveAs();
    void save();
    void onNew();
    void onOpen();
    void onUndo();
    void onRedo();

    QDockWidget *paramDock = new QDockWidget("Parameters", this);
    QDockWidget *viewerDock = new QDockWidget("Viewer", this);
    QDockWidget *nodeDock = new QDockWidget("Node Editor", this);

    QStatusBar*viewerStatusBar = new QStatusBar;
    QLabel *rLabel = new QLabel();
    QLabel *gLabel = new QLabel();
    QLabel *bLabel = new QLabel();
    QLabel *aLabel = new QLabel();

    void initStyle();
};

