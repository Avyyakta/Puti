#ifndef KOLYOSA_GLOBAL_H
#define KOLYOSA_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(KOLYOSA_LIBRARY)
#  define KOLYOSASHARED_EXPORT Q_DECL_EXPORT
#else
#  define KOLYOSASHARED_EXPORT Q_DECL_IMPORT
#endif

#define _SHARED_EXPORT KOLYOSASHARED_EXPORT

#endif // KOLYOSA_GLOBAL_H
