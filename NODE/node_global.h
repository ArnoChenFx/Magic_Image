#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(NODE_LIB)
#  define NODE_EXPORT Q_DECL_EXPORT
# else
#  define NODE_EXPORT Q_DECL_IMPORT
# endif
#else
# define NODE_EXPORT
#endif
