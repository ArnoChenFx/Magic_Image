#pragma once

#include <QMainWindow>
#include <QStatusBar>
#include "viewerWindow.h"
#include "nodeWindow.h"
#include "paramWindow.h"
#include "TDWindow.h"
class MagicImage : public QMainWindow
{
    Q_OBJECT

public:

    MagicImage(QWidget *parent = nullptr);

	virtual void closeEvent(QCloseEvent *event) override;


	QStatusBar *IMstatusBar = new QStatusBar;
	void cookImage();

	paramWindow *paramWid;
	viewerWindow *viewerWid;
	nodeWindow *nodeWid;
	TDWindow *TDWid;


private:
	
    QString projectName=nullptr;

    void initUI();
    void initDock();
    void initMenuBar();
    void initSingalConnection();
    bool eventFilter(QObject *target, QEvent *qevent);

    void changeTitle();
    void onSave();
    void onSaveAs();
    void save();
    void onNew(bool loadProject=false);
    void onOpen();
    void onUndo();
    void onRedo();

    void initStyle();
	
	json saveScene();
	void load(json sceneInfo);
	void loadLine(json lineInfo);
	void loadNode(json nodeInfo);
	
	QAction *createAct(QMenu *menu, QString name, QString tooltip, QString shortcut = "");


	void writeSettings();
	void readSettings();
};

