#pragma once
#include "node_global.h"
#include <Register.h>
#include <qlineedit.h>
#include "Model.h"

class NODE_EXPORT node_Model :public NODE_item
{
public:
	node_Model(NODE_graphics_view* NODE_v = nullptr);

	virtual void initSocket() override;
	virtual void updateParamUI() override;
	virtual void cook() override;
	std::string filePath;
	QLineEdit *pathLine;

	Model *geo = nullptr;

	void loadModel();

private:
	void openFile(QString fileName = nullptr);

};

