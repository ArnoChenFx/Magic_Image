#pragma once

#include "factory.h"
#include <qdebug.h>

class NODE_Base
{

};

#define FACTORY_NODE Factory<NODE_Base>

#define REGISTER_NODE_CLASS_KEY(CLASS, KEY) \
    FACTORY_NODE::register_h<CLASS> __##CLASS(KEY)
	

#define REGISTER_NODE_CLASS(CLASS) \
    REGISTER_NODE_CLASS_KEY(CLASS, CLASS_NAME(CLASS))


