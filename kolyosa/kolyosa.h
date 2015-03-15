#ifndef KOLYOSA_H
#define KOLYOSA_H

#include <QSettings>
#include <QMainWindow>
#include <QToolBar>
#include <QStatusBar>
#include <QMenuBar>
#include <QMessageBox>

#include "kolyosa_global.h"

#include "logger.h"
#include "mapplugins.h"

// Сохранение установок всех и вся
extern _SHARED_EXPORT QSettings*    ___stt;
// Первое (главное) окно программы
extern _SHARED_EXPORT QMainWindow*  ___okno;
// Линейка инструментов первого окна
extern _SHARED_EXPORT QToolBar*     ___instum;
// Линия подсказок первого окна
extern _SHARED_EXPORT QStatusBar*   ___podskaz;
// Линия меню первого окна
extern _SHARED_EXPORT QMenuBar*     ___dela;
// Дополнения которые были найдены
extern _SHARED_EXPORT PLuginsMap*   ___plugs;

#define ___soob(a) { QMessageBox mb(QMessageBox::Information,QApplication::tr("Сообщение..."), (a), QMessageBox::Ok); mb.exec(); }

#endif // KOLYOSA_H
