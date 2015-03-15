#include "mpplgldr.h"

MPPlgLdr::MPPlgLdr(const QString& pth, QObject* prnt) :
    QObject(prnt),
    ___path(pth),
    ___types(),
    ___ldr(new shPlgLdr(pth, this)),
    ___mapObjs()
{
    if (___ldr.data() == nullptr) {
        ___path.clear();
        return;
    }
    if (!(load())) {
        ___path.clear();
        ___ldr = (shPlgLdr*)nullptr;
    };
}

MPPlgLdr::MPPlgLdr(const MPPlgLdr &ppl) :
//        QObject(*((const QObject*)(&ppl))),
    ___path(ppl.___path),
    ___types(ppl.___types),
    ___ldr(ppl.___ldr),
    ___mapObjs(ppl.___mapObjs)
{
}

MPPlgLdr& MPPlgLdr::operator=(const MPPlgLdr&b) {
    ___path = b.___path;
    ___types = b.___types;
    ___ldr = b.___ldr;
    ___mapObjs = b.___mapObjs;
    return *this;
}

bool MPPlgLdr::load() {
    if (___ldr.data() == nullptr) {
        ___ldr = new shPlgLdr(___path, this);
    };
    if (___ldr.data() == nullptr)
        return ___ldr->__load();
    return false;
}

bool MPPlgLdr::unload() {
    if (___ldr.data() == nullptr) return true;
    if (___ldr->__unload()) {
        ___ldr = (shPlgLdr*)nullptr;
        return true;
    };
    return false;
}

QObject* MPPlgLdr::createObject(const QString& nmtp, const QString& nmobj, QObject* prnt) {
    if (!(___types.contains(nmtp))) return nullptr;
    if (!(load())) return nullptr;
    QString nm = nmobj;
    if (nm.isEmpty())
        nm = QString("%1_%2").arg(___ldr->___intrfc->name()).arg((qlonglong)___ldr.data());
    QObject* o = ___ldr->___intrfc->createObject(nmtp, nm,prnt);
    if (o) {
        shdObjPlg sho(___ldr,o);
        ___mapObjs.insert(nm, QSharedDataPointer<shdObjPlg>(&sho));
//        ___mapObjs[nm]->___ldr = ___ldr;
//        ___mapObjs[nm]->___obj = o;
    }
    return o;
}

bool MPPlgLdr::deleteObject(QObject* o) {
    if (o == nullptr) return true;
    QString nm = o->objectName();
    if (!(___mapObjs.contains(nm))) return false;
    ___mapObjs[nm] = nullptr;
    ___mapObjs.remove(nm);
    if (___mapObjs.isEmpty()) unload();
    return true;
}

