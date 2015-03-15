#include <QApplication>

#include "shplgldr.h"
#include "logger.h"

shdObjPlg::~shdObjPlg() {
    if (___obj) data()->___intrfc->deleteObject(___obj);
    if (___obj) {
        QObject* p = ___obj->parent();
        if (p == nullptr || p == (QObject*)(data())) {
            delete ___obj; ___obj = nullptr;
        };
    };
    QSharedDataPointer<shPlgLdr>::operator =((shPlgLdr*)nullptr);
    ___obj = nullptr;
}

bool shPlgLdr::__load() {
    if (___ldr == nullptr) return false;
    if (___ldr->isLoaded()) {
        if (___intrfc == nullptr) {
            ___intrfc = qobject_cast<MPluginInterface*>(___ldr->instance());
            if (___intrfc == nullptr) {
                ___err(QApplication::tr("при получении доступа к дополнению \"%1\"...\nОшибка : %2").arg(___ldr->fileName()).arg(___ldr->errorString()));
                return false;
            };
        };
    } else {
        ___intrfc = nullptr;
        if (___ldr->fileName().isEmpty()) {
            ___err(QApplication::tr("при загрузке дополнения отсутствует путь до него..."));
            return false;
        };
        if (___ldr->load()) {
            ___intrfc = qobject_cast<MPluginInterface*>(___ldr->instance());
            if (___intrfc == nullptr) {
                ___err(QApplication::tr("при получении доступа к дополнению \"%1\"...\nОшибка : %2").arg(___ldr->fileName()).arg(___ldr->errorString()));
                return false;
            };
        } else {
            ___err(QApplication::tr("при загрузке дополнения \"%1\"...\nОшибка : %2").arg(___ldr->fileName()).arg(___ldr->errorString()));
            return false;
        };
    };
    return true;
}

bool shPlgLdr::__unload() {
//    if (!(___mObj.isEmpty())) return false;
    if (!(___ldr->isLoaded())) return true;
    if (!(___ldr->unload())) {
        ___err(QApplication::tr("при выгрузке дополнения \"%1\"...\nОшибка : %2").arg(___ldr->fileName()).arg(___ldr->errorString()));
        return false;
    };
    ___intrfc = nullptr;
    return true;
}

shPlgLdr::shPlgLdr() :
    QSharedData(),
    QObject(),
//    ___mObj(),
    ___intrfc(nullptr),
    ___ldr(nullptr)
{
}

shPlgLdr::shPlgLdr(const QString& pth, QObject* prnt) :
    QSharedData(),
    QObject(prnt),
//    ___mObj(),
    ___intrfc(nullptr),
    ___ldr(new QPluginLoader(prnt))
{
    if (___ldr) ___ldr->setFileName(pth);
}

shPlgLdr::shPlgLdr(const shPlgLdr& shpl) :
    QSharedData(*((QSharedData*)(&shpl))),
    QObject(shpl.parent()),
//    ___mObj(shpl.___mObj),
    ___intrfc(shpl.___intrfc),
    ___ldr(shpl.___ldr)
{
}

shPlgLdr::~shPlgLdr() {
    __unload();
//    ___mObj.clear();
    if (___ldr) { delete ___ldr; ___ldr = nullptr; };
}
