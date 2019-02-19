#include "my_node2.h"
#include <factory2.h>

my_node2::my_node2()
{
	name = "I AM NODE2";
}


my_node2::~my_node2()
{
}

string my_node2::getName()
{
	return name;
}
//REGISTER_MESSAGE(Message1, "message1", 2);
REGISTER_NODE(my_node2, "NODE2");