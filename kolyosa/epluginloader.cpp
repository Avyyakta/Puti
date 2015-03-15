#include "epluginloader.h"

bool EPluginLoader::__load() {
//    if (!___vld) return false;
    if (___ldr == nullptr) {
        ___ldr = new QPluginLoader();
        if (___ldr == nullptr) {
            ___err(QApplication::tr("нехватка памяти под загрузчик дополнения \"%1\"...") .arg(___fnm));
            ___ifc = nullptr;
            return false;
        } else {
            ___ldr->setFileName(___fnm);
            if (!(___ldr->isLoaded())) if (!(___ldr->load())) {
                ___err(QApplication::tr("при загрузке дополнения \"%1\"...\nОшибка : %2") .arg(___fnm) .arg(___ldr->errorString()));
                delete ___ldr; ___ldr = nullptr;
                return false;
            };
        };
    };
    if (___ifc != nullptr) return true;
    ___ifc = qobject_cast<MPluginInterface*>(___ldr->instance());
    if (___ifc == nullptr) {
        ___err(QApplication::tr("при нахождении доступа к дополнению \"%1\"...\nОшибка : %2") .arg(___fnm) .arg(___ldr->errorString()));
        delete ___ldr; ___ldr = nullptr;
        return false;
    } else return true;
}

void EPluginLoader::__unload() {
//    if (!___vld) return;
    if (___ldr == nullptr) return;
    ___ifc = nullptr;
    if (___ldr->isLoaded()) if (!(___ldr->unload())) {
        ___err(QApplication::tr("при выгрузке дополнения \"%1\"...\nОшибка : %2") .arg(___fnm) .arg(___ldr->errorString()));
    };
    delete ___ldr; ___ldr = nullptr;
    return;
}

EPluginLoader::EPluginLoader(const QString& nm, QString* retNm) :
    ___fnm(nm),
    ___ifc(nullptr),
    ___ldr(nullptr),
    ___ver(),
    ___vld(false),
    ___map()
{
    if (nm.isEmpty()) {
        ___err("создание обёртки загрузчика с пустым именем...");
        return;
    };
    if (!(__load())|| ___ifc == nullptr) {
        ___err("загрузки при создание обёртки загрузчика...");
        return;
    };
    *retNm = ___ifc->name();
    ___ver = ___ifc->version();
    __unload();
    ___vld = true;
}

EPluginLoader::~EPluginLoader() {
/*    QList<QString> ls = ___map.keys();
    foreach (QString v, ls) {
        QObject* o = ___map.value(v);
        if (o) deleteObj(o);
    } */
    ___map.clear();
//    while(!(isEmpty())) deleteObj(lastKey());
    __unload();
}

QObject* EPluginLoader::addNewObj(const QString& tnm, const QString& nm, QObject* p) {
    if (!___vld) return nullptr;
    bool nldd = ___ifc == nullptr;
    if (nldd) if (!__load()) return nullptr;
    QObject* o = ___ifc->createObject(tnm, nm, p);
    if (o == nullptr) {
        if (nldd) __unload();
        return nullptr;
    };
    ___map.insert(nm, o);
//    ___inf(QString("[EPluginLoader::addNewObj] добавлена переменная \"%1\" типа \"%2\" {%3}...") .arg(nm) .arg(tnm) .arg((qlonglong)o));
    return o;
}

bool EPluginLoader::deleteObj(const QString& nm) {
    if (!___vld) return false;
    if (nm.isEmpty() || ___map.isEmpty()) return false;
    QMap<QString,QObject*>::iterator it = ___map.find(nm);
    if (it == ___map.end()) return false;
    QObject* o = it.value();
    ___map.erase(it);
    if (___ifc->deleteObject(o) == false) {
//        ___inf(QString("[EPluginLoader::deleteObj] delete \"%1\"...") .arg(nm));
        if (o != nullptr) {
            if (o->parent() == nullptr) {
                delete o;
                o = nullptr;
            };
        };
    };
    if (___map.isEmpty()) __unload();
    return true;
}

bool EPluginLoader::deleteObj(QObject* o) {
    if (!___vld) return false;
    if (___map.isEmpty()) return false;
    if (o == nullptr) return true;
    QMap<QString,QObject*>::iterator it = ___map.find(___map.key(o));
    if (it == ___map.end()) return false;
    if (___ifc->deleteObject(it.value()) == false) {
        delete it.value(); it.value() = nullptr;
    };
    ___map.erase(it);
    if (___map.isEmpty()) __unload();
    return true;
}
