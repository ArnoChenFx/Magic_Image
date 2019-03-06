#include "paramWindow.h"
#include "Magic_Image.h"


paramWindow::paramWindow(MagicImage * mainW) : QDockWidget("Parameter", mainW)
{
	mainWindow = mainW;
	mainWindow->addDockWidget(Qt::RightDockWidgetArea, this);
	//this->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetClosable);
	this->setObjectName("paramWindow");

	paramView->setFrameShape(QFrame::StyledPanel);
	this->setWidget(paramView);

	initStyle();
}

paramWindow::~paramWindow()
{
}

void paramWindow::initStyle()
{
	this->setStyleSheet(QString("background-color:%1;color:rgb(200,200,200);").arg(getRGB("color_background_light")));
}
