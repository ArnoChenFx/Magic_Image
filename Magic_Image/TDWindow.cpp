#include "TDWindow.h"
#include "Magic_Image.h"
#include "UT_utils.h"

TDWindow::TDWindow(MagicImage * mainW) :QDockWidget("3D Viewer", mainW)
{
	mainWindow = mainW;
	mainWindow->addDockWidget(Qt::RightDockWidgetArea, this);
	this->setObjectName("TDWindow");

	TDMainWindow = new QMainWindow;
	
	glScene = new OpenGLScene;
	glWidget = TDMainWindow->createWindowContainer(glScene);
	TDMainWindow->setCentralWidget(glWidget);
	this->setWidget(TDMainWindow);

	initStyle();
}

TDWindow::~TDWindow()
{
	delete TDMainWindow;
}

void TDWindow::connectSignals()
{
}

void TDWindow::initStyle()
{
	this->setStyleSheet(QString("background-color:%1;color:rgb(200,200,200);").arg(getRGB("color_background_light")));

}
