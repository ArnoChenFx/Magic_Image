#include "NODE_ui_items.h"
#include <qlabel.h>

int size = 50;
int namew = 60;
int nameh = 20;

void addFileUI(QHBoxLayout *hbox, QLineEdit *pathLine, QPushButton *button, QString name)
{
	//QLabel *nameLabel = new QLabel();
	//nameLabel->setText(name);
	//nameLabel->setFixedWidth(name.length()*10);
	//nameLabel->setFixedHeight(nameh);
	
	//pathLine->setText("file--path");

	button->setIcon(QIcon("icons/file.png"));
	button->setMaximumSize(QSize(size, size));
	button->setFixedWidth(namew);
	button->setFixedHeight(nameh);

	//hbox->addWidget(nameLabel, Qt::AlignLeft);
	hbox->addWidget(pathLine, Qt::AlignLeft);
	hbox->addWidget(button, Qt::AlignLeft);

	//button->clicked.connect(lambda: self.openFile(obj.pathLine, obj));
}

void addHline(QVBoxLayout *mainLayout)
{
	QFrame *hline = new QFrame();
	hline->setStyleSheet("background-color: rgb(60,60,60);");
	hline->setFrameShape(QFrame::HLine);
	hline->setFrameShadow(QFrame::Sunken);
	hline->setLineWidth(2);
	mainLayout->addWidget(hline);
}

void addSpacer(QVBoxLayout *mainLayout)
{
	addHline(mainLayout);
	QSpacerItem *spacerItem =new QSpacerItem(40, 200, QSizePolicy::Expanding, QSizePolicy::Expanding);
	mainLayout->addItem(spacerItem);
}