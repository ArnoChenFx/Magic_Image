#include "node_Image.h"
#include <qdebug.h>
#include <Image_basic.h>
#include <qpushbutton.h>
#include <NODE_ui_items.h>
#include <qdir.h>
#include <QFileDialog>
#include <string>
#include <UT_utils.h>

using namespace std;

node_Image::node_Image(NODE_graphics_view* NODE_v) :
	NODE_item(NODE_v, "Image")
{
	initSocket();
	viewerState_item->setState(true);
	updateParamUI();
}

void node_Image::initSocket()
{
	//socket output
	NODE_socket *s0 = new NODE_socket(this, 0, true,"");
	output_sockets.append(s0);
}

void node_Image::updateParamUI()
{
	QHBoxLayout *hbox = new QHBoxLayout();
	pathLine = new QLineEdit();
	QPushButton *open = new QPushButton();
	
	pathLine->setFont(QFont(getString("nd_attrib_font"), 10, QFont::Normal));
	connect(open, &QPushButton::clicked, this, [=]() { 
		openFile(nullptr); 
	});
	connect(pathLine, &QLineEdit::editingFinished, [=]() {
		this->openFile(pathLine->text());
	});

	addFileUI(hbox,pathLine,open,"image");
	//mainLayout->addLayout(hbox);
	//addSpacer(mainLayout);
	addHboxs(mainLayout, { hbox });
}

void node_Image::openFile(QString fileName)
{
	if (fileName == nullptr) {
		QString pathH = QDir::homePath();
		fileName = QFileDialog::getOpenFileName(nullptr, "Open Project", pathH);
	}

	string path = fileName.toStdString();

	if (!fileName.isEmpty()) {
		string format = getFormat(path);
		string name = getFilename(path);
		if (isUsefulFormat("imageFormats", format)) {
			pathLine->setText(fileName);
			this->title = QString::fromStdString(name);
			filePath = path;
			this->cook();
		}
	}
}

void node_Image::cook()
{
	//if (!checkActive()) return;
	this->resultImage = loadImage(filePath);
	updateImage();
	cookNext();
}

REGISTER_NODE(node_Image, "Image", "Import","I");
