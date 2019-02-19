#pragma once
#include <node_test.h>
#include <qstring.h>

class my_node1 :public NODE_Base
{
public:
	my_node1();
	~my_node1();
	QString name;
};
