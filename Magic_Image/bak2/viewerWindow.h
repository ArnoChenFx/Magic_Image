#pragma once
#include <qdockwidget.h>
#include <qmainwindow.h>
#include <qstatusbar.h>
#include "VI_image_viever.h"
#include "VI_graphics_view.h"
#include "OpenGLWindow.h"

class MagicImage;

class viewerWindow : public QDockWidget
{
public:
	viewerWindow(MagicImage * mainW=nullptr);
	~viewerWindow();

	MagicImage * mainWindow;

	QMainWindow *viewerMainWindow;
	VI_image_viever *viewer;
	VI_graphics_view *viewerGraphicsview;
	OpenGLWindow *glView;

	QStatusBar*viewerStatusBar;
	QLabel *rLabel;
	QLabel *gLabel;
	QLabel *bLabel;
	QLabel *aLabel;

private:
	void connectSignals();
	void initStyle();

	bool eventFilter(QObject *target, QEvent *qevent);
};
