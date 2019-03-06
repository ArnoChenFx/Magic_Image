#include "viewerWindow.h"
#include "Magic_Image.h"
#include <qdebug.h>

viewerWindow::viewerWindow(MagicImage * mainW ):QDockWidget("Viewer",mainW)
{
	mainWindow = mainW;
	mainWindow->addDockWidget(Qt::LeftDockWidgetArea, this);
	//this->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetClosable);
	this->setObjectName("viewerWindow");

	//new
	viewer = new VI_image_viever;
	viewerGraphicsview = new VI_graphics_view(viewer);
	viewerMainWindow = new QMainWindow;
	viewerStatusBar = new QStatusBar;
	rLabel = new QLabel();
	gLabel = new QLabel();
	bLabel = new QLabel();
	aLabel = new QLabel();
	resLabel = new QLabel();
	factorLabel = new QLabel();
	QLabel *spacer = new QLabel();
	spacer->setMinimumWidth(20);
	spacer->setStyleSheet("background-color:transparent;border:0px");

	//status bar
	viewerMainWindow->setCentralWidget(viewerGraphicsview);
	viewerMainWindow->setStatusBar(viewerStatusBar);
	viewerStatusBar->addPermanentWidget(rLabel);
	viewerStatusBar->addPermanentWidget(gLabel);
	viewerStatusBar->addPermanentWidget(bLabel);
	viewerStatusBar->addPermanentWidget(aLabel);
	viewerStatusBar->addPermanentWidget(spacer);
	viewerStatusBar->addPermanentWidget(factorLabel);
	viewerStatusBar->addPermanentWidget(resLabel);
	rLabel->setText("0.00000");
	gLabel->setText("0.00000");
	bLabel->setText("0.00000");
	aLabel->setText("1.00000");
	resLabel->setText(QString("(%1,%2)").arg(viewer->width()).arg(viewer->height()));
	factorLabel->setText(QString("%1%").arg(100));

	//set state
	viewerStatusBar->setFixedHeight(20);
	viewerStatusBar->setSizeGripEnabled(false);

	this->setWidget(viewerMainWindow);

	//init
	this->connectSignals();
	this->initStyle();
}


viewerWindow::~viewerWindow()
{
	//delete viewerMainWindow;
}

void viewerWindow::connectSignals()
{
	connect(viewer, &VI_image_viever::move, [=](QMouseEvent *event) {
		QString msg = QString("x=%1,y=%2").arg(event->pos().x()).arg(event->pos().y());
		viewerStatusBar->showMessage(msg);
		QRgb imgRgb = viewer->mainImage->pixel(event->pos().x(), event->pos().y());
		qreal r, g, b, a;
		QColor(imgRgb).getRgbF(&r, &g, &b, &a);
		rLabel->setText(QString::number(r));
		gLabel->setText(QString::number(g));
		bLabel->setText(QString::number(b));
		aLabel->setText(QString::number(a));

	});

	connect(viewer, &VI_image_viever::scaled, [=]() {
		resLabel->setText(QString("(%1,%2)").arg(viewer->width()).arg(viewer->height()));
	});

	connect(viewer, &VI_image_viever::click, [=](QMouseEvent *event) {
		QString msg = QString("click:(%1,%2)").arg(event->pos().x()).arg(event->pos().y());
		mainWindow->IMstatusBar.showMessage(msg);
	});

	connect(viewerGraphicsview, &VI_graphics_view::scaled, [=]() {
		factorLabel->setText(QString("%1%").arg(viewerGraphicsview->scakeRatio*100));
	});

}

void viewerWindow::initStyle()
{
	this->setStyleSheet(QString("background-color:%1;color:rgb(200,200,200);").arg(getRGB("color_background_light")));

	rLabel->setStyleSheet("background-color:transparent;font-size:12px;color:red;border:0px");
	gLabel->setStyleSheet("background-color:transparent;font-size:12px;color:green;border:0px");
	bLabel->setStyleSheet("background-color:transparent;font-size:12px;color:blue;border:0px");
	aLabel->setStyleSheet("background-color:transparent;font-size:12px;color:white;border:0px");

	resLabel->setStyleSheet("background-color:transparent;font-size:12px;color:white;border:0px");
	factorLabel->setStyleSheet("background-color:transparent;font-size:12px;color:white;border:0px");

	viewerStatusBar->setStyleSheet(QString("QStatusBar::item {border: None;}""QStatusBar{background-color:%1;color:rgb(230,230,230);border: 0px solid black;"
		"border-radius: 0px;font-size:12px;}")
		.arg(getRGB("color_background_dark")));

	viewerGraphicsview->scene()->setBackgroundBrush(getColor("color_background"));

	viewer->setStyleSheet("QLabel{background-color:rgb(30,30,30);border: 0px solid #32414B;padding: 0px;margin: 0px;color: black}");
}

