#include "node_Merge.h"
#include <qcombobox.h>
#include <NODE_ui_items.h>
#include <NODE_line.h>
#include <Image_basic.h>
#include <Image_mix.h>

node_Merge::node_Merge(NODE_graphics_view* NODE_v):
	NODE_item(NODE_v, "Merge")
{
	initSocket();
	updateParamUI();
	index = 0;
	setScale(200, 210);

	ColorA = defaultImage;
	ColorB = defaultImage;
	hasMask = false;
}

void node_Merge::initSocket()
{
	//socket output
	NODE_socket *s0 = new NODE_socket(this, 0, true, "");
	output_sockets.append(s0);

	//socket input
	NODE_socket *i0 = new NODE_socket(this, 0, false, "Color A",40);
	input_sockets.append(i0);
	
	NODE_socket *i1 = new NODE_socket(this, 0, false, "Color B",70);
	input_sockets.append(i1);

	NODE_socket *i2 = new NODE_socket(this, 0, false, "Mask",100);
	input_sockets.append(i2);
}

void node_Merge::updateParamUI()
{
	QHBoxLayout *hbox = new QHBoxLayout();
	QComboBox *mode = new QComboBox();
	hbox->addWidget(mode);

	mode->addItems({"Normal", "Add", "Multiply", "Substract","Divide",
		"Max", "Min", "Screen", "Overlay", "Hard Light", "Soft Light" ,
		"Vivid Light","Linear Light","Pin Light","Color Burn", "Linear Burn",
		"Color Dodge","Difference", "Exclusion","Average","Reflect","Phoenix",
		"Glow","Color Over"
		});
	mode->setMaxVisibleItems(30);
	mode->insertSeparator(5);
	mode->insertSeparator(10);
	mode->insertSeparator(16);
	mode->insertSeparator(23);
	mode->setFont(QFont(getString("nd_attrib_font"), 10, QFont::Normal));
	mode->setCurrentIndex(0);
	//mode->currentIndexChanged.connect(lambda: self.setIndex(obj.mode.currentIndex()))
	connect(mode, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=]() {
		index = mode->currentIndex();
		cook();
	});

	mainLayout->addLayout(hbox);
	addSpacer(mainLayout);
}

void node_Merge::computeMix()
{
	getImage();
	resultImage.release();
	resultImage = ColorA.clone();

	switch (index)
	{
	case 0: break;
	case 1: {
		Image_add(resultImage, ColorB);
		break;
	}
	case 2: {
		Image_multiply(resultImage, ColorB);
		break;
	}
	case 3: {
		Image_substract(resultImage, ColorB);
		break;
	}
	case 4: {
		Image_divide(resultImage, ColorB);
		break;
	}
	case 6: {
		Image_max(resultImage, ColorB);
		break;
	}
	case 7: {
		Image_min(resultImage, ColorB);
		break;
	}
	case 8: {
		Image_screen(resultImage, ColorB);
		break;
	}
	case 9: {
		Image_overlay(resultImage, ColorB);
		break;
	}
	case 11: {
		Image_hardLight(resultImage, ColorB);
		break;
	}
	case 12: {
		Image_softLight(resultImage, ColorB);
		break;
	}
	case 13: {
		Image_vividLight(resultImage, ColorB);
		break;
	}
	case 14: {
		Image_linearLight(resultImage, ColorB);
		break;
	}
	case 15: {
		Image_pinLight(resultImage, ColorB);
		break;
	}
	case 17: {
		Image_colorBurn(resultImage, ColorB);
		break;
	}
	case 18: {
		Image_linearBurn(resultImage, ColorB);
		break;
	}
	case 19: {
		Image_colorDodge(resultImage, ColorB);
		break;
	}
	case 20: {
		Image_difference(resultImage, ColorB);
		break;
	}
	case 21: {
		Image_exclusion(resultImage, ColorB);
		break;
	}
	case 22: {
		Image_average(resultImage, ColorB);
		break;
	}
	case 24: {
		Image_reflect(resultImage, ColorB);
		break;
	}
	case 25: {
		Image_phoenix(resultImage, ColorB);
		break;
	}
	case 26: {
		Image_glow(resultImage, ColorB);
		break;
	}
	case 27: {
		Image_colorOver(resultImage, ColorB);
		break;
	}
	default: break;
	}

	if (hasMask) Image_Mask(resultImage, ColorA, Mask);
}

void node_Merge::getImage()
{
	ColorA.release();
	ColorB.release();
	


	QList<NODE_line*> lines0 = input_sockets[0]->connectedLines();
	if (lines0.length() > 0 && lines0[0]->inputSock != nullptr) {
		ColorA = lines0[0]->inputSock->node->resultImage;
	}
	else ColorA = defaultImage;

	QList<NODE_line*> lines1 = input_sockets[1]->connectedLines();
	if (lines1.length() > 0 && lines1[0]->inputSock != nullptr) {
		ColorB = lines1[0]->inputSock->node->resultImage;
	}
	else ColorB = defaultImage;

	QList<NODE_line*> lines2 = input_sockets[2]->connectedLines();
	if (lines2.length() > 0 && lines2[0]->inputSock != nullptr) {
		Mask.release();
		Mask = lines2[0]->inputSock->node->resultImage;
		hasMask = true;
	}
	else hasMask = false;

	//resize(ColorA, ColorB);
	//resize(ColorA, Mask);
}

void node_Merge::cook()
{
	if (!checkActive()) return;
	qDebug() << "cook merge";
	computeMix();
	updateImage();
	cookNext();
}

REGISTER_NODE(node_Merge, "Merge", "Color", "M");
