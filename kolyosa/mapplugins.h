#ifndef MAPPLUGINS_H
#define MAPPLUGINS_H

#include <QMap>
#include <QString>

#include "epluginloader.h"

#include "kolyosa_global.h"

class _SHARED_EXPORT PLuginsMap
{
    QMap<QString, EPluginLoader*>   ___map;

public:

    PLuginsMap();
    ~PLuginsMap();

    EPluginLoader* operator[](const QString& s) {
        QMap<QString, EPluginLoader*>::iterator it;
        if ((it=___map.find(s))==___map.end()) {
            ___err(QString("[PLuginsMap] не найдено значение с ключём \"%1\"...").arg(s));
            return nullptr;
        };
        return it.value();
    }

    EPluginLoader* value(const QString& s) {
        return ___map.value(s);
    }

    QString key(EPluginLoader* pl) {
        return ___map.key(pl,"");
    }

    bool isEmpty() { return ___map.isEmpty(); }
    QList<QString> keys() { return ___map.keys(); }

};

#endif // MAPPLUGINS_H
