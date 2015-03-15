#include "scriptextensionplugin.h"

#include "frmvseuslugi.h"
#include "dlgsetup.h"
#include "frmmainsetup.h"
#include "proba.h"

#define FOROM_CENTER        "vse_uclugi"
#define FOROM_CENTER_N      0

#define SETUPS              "vse_setups"
#define SETUPS_N            1

#define PAGE_SETUP          "page_setup"
#define PAGE_SETUP_N        2

#define PROBE               "proba"
#define PROBE_N             3

ScriptExtensionPlugin::ScriptExtensionPlugin(QObject *parent) :
    MPluginInterface(parent)
{
}

QStringList ScriptExtensionPlugin::get_types() {
    /*___inf("1");*/
    return QStringList()
            << FOROM_CENTER
            << SETUPS
            << PAGE_SETUP
            << PROBE
               ;
}

// Внутреннее имя дополнения
QString ScriptExtensionPlugin::name() {
//    ___inf("called plugin name");
    return QString("izvozcik");
}

//  Экраннок название дополнения
// (false - краткое, иначе полное)
//    QString ScriptExtensionPlugin::caption(bool full=false) { return QString(); }

//  Создание объекта внутреннего типа {nmtp} с именем {nmtp},
// входящий в пулл объектов объекта {parent}
QObject* ScriptExtensionPlugin::createObject(const QString& nmtp, const QString& nmobj, QObject* parent) {
    int ndx = get_types().indexOf(nmtp);
    QObject* o = nullptr; if (ndx < 0) return o;
    QString nmObj = nmobj;
    if (nmObj.isEmpty()) nmObj = QString("%1_%2") .arg(name()) .arg((qlonglong)this);

    switch (ndx) {
    case FOROM_CENTER_N: {
        FrmVseUslugi* f = new FrmVseUslugi((QWidget*)parent);
        if (f) o = f;
        else {
            ___err(QApplication::tr("[%1] выделения памяти под главное в окне...").arg(name()));
        };
    }; break;
    case SETUPS_N: {
        o = new DlgSetup((QWidget*)parent);
        if (o == nullptr) {
            ___err(QApplication::tr("[%1] выделения памяти под изменение установок...").arg(name()));
        };
    }; break;
    case PAGE_SETUP_N: {
        o = new FrmMainSetup((QWidget*)parent);
        if (o == nullptr) {
            ___err(QApplication::tr("[%1] выделения памяти под страничку установок...").arg(name()));
        };
    }; break;
    case PROBE_N: {
        o = new Proba(parent);
        if (o == nullptr) {
            ___err(QApplication::tr("[%1] выделения памяти под проверочную переменную...").arg(name()));
        };
    }; break;
    default:
        break;
    };

    if (o == nullptr) return nullptr;
    if (o->objectName().isEmpty())
        o->setObjectName(nmObj);

    return o;
}

// Удаление ранее созданного этим дополнением объекта
bool ScriptExtensionPlugin::deleteObject(QObject* o) {
    if (o == nullptr) return true;
    QObject* p = o->parent();
    if (p != nullptr && p != this) return false;
    delete o; o = nullptr;
    return true;
}

// Описание дополнения (false - краткое, иначе полное)
//    QString help(bool full=false)=0;

// Версия этого дополнения (false - краткая, иначе полная)
QString ScriptExtensionPlugin::version(bool full) {
    if (full) return QString("(prepreprerelease) 0.0.0 alpha");
    return QString("0.0.0a");
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(psjr000, ScriptExtensionPlugin)
#endif // QT_VERSION < 0x050000
