#pragma once
#include "node_global.h"
#include <Register.h>
#include <qlineedit.h>

class NODE_EXPORT node_Image :public NODE_item
{
public:
	node_Image(NODE_graphics_view* NODE_v = nullptr);

	virtual void initSocket() override;
	virtual void updateParamUI() override;
	virtual void cook() override;
	std::string filePath;
	QLineEdit *pathLine;
private:
	void openFile(QString fileName=nullptr);
	//param
	
};

