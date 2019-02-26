#include "NODE_ui_utils.h"
#include <qdir.h>
#include <qfiledialog.h>


void openFile()
{
	QString pathH = QDir::homePath();
	QString path = QFileDialog::getOpenFileName(nullptr, "Open Project", pathH);

	//if (!path.isEmpty()) {
	//	string format = getFormat(path);
	//	string name = getFilename(path);
	//	if (isUsefulFormat("imageFormats", format)) {
	//		auto node = onCreateNode("Image");
	//		node->title = QString::fromStdString(name);
	//		node->setPos(nodePos);
	//		node->resultImage = loadImage(path);
	//		node->cook();
	//		count++;
	//	}
	//}
}

