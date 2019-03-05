#pragma once
#include <qdockwidget.h>
#include <qmainwindow.h>
#include <qstatusbar.h>
#include "NODE_graphics_view.h"
#include <string>
#include "NODE_item.h"
class MagicImage;

class nodeWindow : public QDockWidget
{
public:
	nodeWindow(MagicImage * mainW = nullptr);
	~nodeWindow();

	MagicImage * mainWindow;

	QMainWindow *nodeMainWindow;
	NODE_graphics_view *nodeView;

	NODE_item* nodeWindow::onCreateNode(std::string name);
	void onDrop();

private:
	void connectSignals();
	void initStyle();
	QAction*createAct(QMenu *menu, QString name, QString tooltip, QString shortcut = "");
};

