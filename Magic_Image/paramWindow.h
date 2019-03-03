#pragma once
#include <qdockwidget.h>
#include <QFrame>

class MagicImage;

class paramWindow : public QDockWidget
{
public:
	paramWindow(MagicImage * mainW = nullptr);
	~paramWindow();

	MagicImage * mainWindow;

	QFrame *paramView = new QFrame;

private:
	//void connectSignals();
	void initStyle();
};

