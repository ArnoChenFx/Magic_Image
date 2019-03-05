#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(MI_OPENGL_LIB)
#  define MI_OPENGL_EXPORT Q_DECL_EXPORT
# else
#  define MI_OPENGL_EXPORT Q_DECL_IMPORT
# endif
#else
# define MI_OPENGL_EXPORT
#endif
