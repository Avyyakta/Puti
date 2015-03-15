#ifndef SHPLGLDR_H
#define SHPLGLDR_H

#include <QSharedDataPointer>
#include <QObject>
#include <QPluginLoader>

#include "plugin_interface.h"

class shPlgLdr;
class shdObjPlg;

// typedef QSharedDataPointer<shdObjPlg> shPObj;
// typedef QMap<QString,shPObj> mapPObj;

class shPlgLdr : public QSharedData, public QObject
{
    Q_OBJECT

//    mapPObj                 ___mObj;
    MPluginInterface*       ___intrfc;
    QPluginLoader*          ___ldr;

    bool __load();
    bool __unload();

    friend class shdObjPlg;
    friend class MPPlgLdr;
public:
    shPlgLdr();

    shPlgLdr(const QString& pth, QObject* prnt = nullptr);

    shPlgLdr(const shPlgLdr& shpl);

    ~shPlgLdr();

};

/* template <>
class QSharedDataPointer<shPlgLdr>
{

}; */

typedef class QSharedDataPointer<shPlgLdr> shDPPlgLdr;

class shdObjPlg : public QSharedData, public shDPPlgLdr
{
//    shpPlgLdr   ___ldr;
    QObject*    ___obj;

    friend class MPPlgLdr;
public:
    shdObjPlg() :
//        ___ldr(nullptr),
        shDPPlgLdr(),
        ___obj(nullptr)
    {
        //
    }

    shdObjPlg(shDPPlgLdr& ldr, QObject* o) :
//        ___ldr(ldr),
        shDPPlgLdr(ldr),
        ___obj(o)
    {
        //
    }

    ~shdObjPlg();

    QObject* operator()() { return ___obj; }

    // using the assignment operator would lead to corruption in the ref-counting
    shdObjPlg &operator=(const shdObjPlg &b) {
//        shPlgLdr* p = const_cast<shPlgLdr*>(*(b));
        shDPPlgLdr::operator =(shDPPlgLdr(b));
        ___obj = b.___obj;
        return *this;
    }
};

#endif // SHPLGLDR_H
