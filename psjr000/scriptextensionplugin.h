#ifndef SCRIPTEXTENSIONPLUGIN_H
#define SCRIPTEXTENSIONPLUGIN_H

#include <QScriptExtensionPlugin>

#include "../kolyosa/kolyosa.h"

#include "../kolyosa/plugin_interface.h"


class ScriptExtensionPlugin : public MPluginInterface
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID CyrGenericPluginInterface_iid FILE "psjr000.json")
#endif // QT_VERSION >= 0x050000

public:
    ScriptExtensionPlugin(QObject *parent = 0);

    // Типы данных которые может создать дополнения
    virtual QStringList get_types();

    // Внутреннее имя дополнения
    virtual QString name();

    //  Создание объекта внутреннего типа {nmtp} с именем {nmtp},
    // входящий в пулл объектов объекта {parent}
    virtual QObject* createObject(const QString& nmtp, const QString& nmobj = QString(), QObject* parent = 0);

    // Удаление ранее созданного этим дополнением объекта
    virtual bool deleteObject(QObject* o);

    // Версия этого дополнения (false - краткая, иначе полная)
    virtual QString version(bool full=false);

};

#endif // SCRIPTEXTENSIONPLUGIN_H
