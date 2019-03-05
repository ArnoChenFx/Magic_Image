#include "TDWindow.h"
#include "Magic_Image.h"
#include "UT_utils.h"

TDWindow::TDWindow(MagicImage * mainW) :QDockWidget("3D Viewer", mainW)
{
	mainWindow = mainW;
	mainWindow->addDockWidget(Qt::RightDockWidgetArea, this);
	this->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetClosable);
	this->setFloating(true);

	TDMainWindow = new QMainWindow;
	this->resize(1920, 1080);

	glScene = new OpenGLScene;
	//glScene->installEventFilter(this);

	
	glWidget = TDMainWindow->createWindowContainer(glScene);

	TDMainWindow->setCentralWidget(glWidget);

	this->setWidget(TDMainWindow);
}

TDWindow::~TDWindow()
{
}

void TDWindow::connectSignals()
{
}

void TDWindow::initStyle()
{
	this->setStyleSheet(QString("background-color:%1;color:rgb(200,200,200);").arg(getRGB("color_background_light")));

}
