#include "my_node1.h"

my_node1::my_node1()
{
	name = "I AM NODE1";
}


my_node1::~my_node1()
{
}

REGISTER_NODE_CLASS(my_node1);