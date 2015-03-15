#ifndef EPLUGINLOADER_H
#define EPLUGINLOADER_H

#include <QMap>
#include <QObject>
#include <QPluginLoader>

#include "logger.h"
#include "plugin_interface.h"

#include "kolyosa_global.h"

class _SHARED_EXPORT EPluginLoader
{
    QString					___fnm;
    MPluginInterface*		___ifc;
    QPluginLoader*			___ldr;

    QString					___ver;

    bool					___vld;

    QMap<QString,QObject*>  ___map;

    bool __load();
    void __unload();

public:

    // Создание переменной по типу (tnm) и имени (nm), с возможностью указания управителя (parent)
    QObject* addNewObj(const QString& tnm, const QString& nm, QObject* parent = nullptr);
    // Удаление переменной созданной до этого функцией addNewObj
    //          по имени
    bool deleteObj(const QString& nm);
    //          по указателю
    bool deleteObj(QObject* o);

    EPluginLoader(const QString& nm, QString* retNm);
    ~EPluginLoader();

    // Проверка на правильность (работоспособность) загрузчика
    bool isValidate() { return ___vld; }

};

#endif // EPLUGINLOADER_H
