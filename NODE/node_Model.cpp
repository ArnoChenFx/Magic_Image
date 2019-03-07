#include "node_Model.h"
#include <qdebug.h>
#include <Image_basic.h>
#include <qpushbutton.h>
#include <NODE_ui_items.h>
#include <qdir.h>
#include <QFileDialog>
#include <string>
#include <UT_utils.h>

using namespace std;

node_Model::node_Model(NODE_graphics_view* NODE_v) :
	NODE_item(NODE_v, "Model")
{
	initSocket();
	color_title_bar = getColor("Import");
	updateParamUI();
	filePath = QDir::homePath().toStdString();
}

node_Model::~node_Model()
{
	emit destroyM();
	delete geo;
	
}

void node_Model::initSocket()
{
	//socket output
	NODE_socket *s0 = new NODE_socket(this, 0, true, "");
	output_sockets.append(s0);
	s0->sockeFormat = s0->MODEL;
}

void node_Model::updateParamUI()
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

	addFileUI(hbox, pathLine, open, "Model");
	addHboxs(mainLayout, { hbox });
}

void node_Model::openFile(QString fileName)
{
	if (fileName == nullptr) {
		QString pathH = QString::fromStdString(filePath);
		fileName = QFileDialog::getOpenFileName(nullptr, "Open Project", pathH);
	}

	string path = fileName.toStdString();

	if (!fileName.isEmpty()) {
		string format = getFormat(path);
		string name = getFilename(path);
		if (isUsefulFormat("modelFormats", format)) {
			pathLine->setText(fileName);
			this->title = QString::fromStdString(name);
			filePath = path;
			loadModel();
			this->cook();
		}
	}
}

void node_Model::loadModel()
{
	emit destroyM();
	delete geo;
	geo = nullptr;
	geo = new Model(filePath);
	qDebug() << "load:" << QString::fromStdString(filePath);
	emit loadM();
}

void node_Model::cook()
{
	
	updateImage();
	cookNext();
}

REGISTER_NODE(node_Model, "Model", "Import", "");
