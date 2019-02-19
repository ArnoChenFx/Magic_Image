#pragma once

class Node_based
{
public:
	virtual ~Node_based() {}

	string name = "NODE Base";
	virtual string getName() {
		string a = "sss";
		return a;
	};
};