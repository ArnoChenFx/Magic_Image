#pragma once
#include <node_test.h>
#include <qstring.h>
#include <factory2.h>
#include <node_base.h>

class my_node2 :public Node_based
{
public:
	my_node2();
	~my_node2();
	string name = "NODE 2";
	virtual string getName() override;
	
};

