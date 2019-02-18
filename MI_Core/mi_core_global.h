#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(MI_CORE_LIB)
#  define MI_CORE_EXPORT Q_DECL_EXPORT
# else
#  define MI_CORE_EXPORT Q_DECL_IMPORT
# endif
#else
# define MI_CORE_EXPORT
#endif
