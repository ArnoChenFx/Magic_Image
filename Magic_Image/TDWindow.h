#pragma once
#include <qdockwidget.h>
#include <qmainwindow.h>
#include "OpenGLScene.h"

class MagicImage;

class TDWindow : public QDockWidget
{
public:
	TDWindow(MagicImage * mainW = nullptr);
	~TDWindow();

	MagicImage * mainWindow;
	QMainWindow *TDMainWindow;
	OpenGLScene *glScene;
	QWidget * glWidget;

private:
	void connectSignals();
	void initStyle();
};

