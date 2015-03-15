#ifndef PLUGIN_INTERFACE_H
#define PLUGIN_INTERFACE_H 1

#include <QtCore/qplugin.h>
#include <QtScript/QScriptExtensionPlugin>

#include "kolyosa_global.h"

QT_BEGIN_NAMESPACE

#define CyrGenericPluginInterface_iid "org.withoutcompany.CyrSHIVA.Qt.MPluginInterface"

class _SHARED_EXPORT MPluginInterface : public QScriptExtensionPlugin
{
    Q_OBJECT

public:
    explicit MPluginInterface(QObject *parent = 0);
    virtual ~MPluginInterface();

    // Типы данных которые может создать дополнения
    virtual QStringList get_types()=0;

    // Внутреннее имя дополнения
    virtual QString name()=0;

    //  Экраннок название дополнения
    // (false - краткое, иначе полное)
//    virtual QString caption(bool full=false)=0;

    //  Создание объекта внутреннего типа {nmtp} с именем {nmtp},
    // входящий в пулл объектов объекта {parent}
    virtual QObject* createObject(const QString& nmtp, const QString& nmobj = QString(), QObject* parent = 0)=0;

    // Удаление ранее созданного этим дополнением объекта
    virtual bool deleteObject(QObject* o)=0;

    // Описание дополнения (false - краткое, иначе полное)
//    virtual QString help(bool full=false)=0;

    // Версия этого дополнения (false - краткая, иначе полная)
    virtual QString version(bool full=false)=0;

    virtual QStringList keys() const;

    virtual void initialize(const QString &key, QScriptEngine *engine);

// signals:
// public slots:
};

QT_END_NAMESPACE

#endif // PLUGIN_INTERFACE_H
