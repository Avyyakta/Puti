#ifndef CRTDOBJECT_H
#define CRTDOBJECT_H

#include <QObject>
#include <QString>
#include "kolyosa_global.h"

class ObjCreator;

class _SHARED_EXPORT CrtdObject
{
    ObjCreator*		___crtr;
    QObject*		___obj;

    friend class ObjCreator;
    friend bool ::operator == (const CrtdObject&, const CrtdObject&);
    friend bool ::operator != (const CrtdObject&, const CrtdObject&);
public:
    inline CrtdObject(ObjCreator* crtr) :
        ___crtr(crtr), ___obj(nullptr) {}

    inline CrtdObject(const CrtdObject& co) :
        ___crtr(co.___crtr), ___obj(co.___obj) {}

    inline QObject*	operator()() { return ___obj; }

    CrtdObject& operator = (const CrtdObject& b);
//    CrtdObject& operator = (const QObject* b);

    inline QString name() { return ___obj->objectName(); }

};

inline bool operator == (const CrtdObject& a, const CrtdObject& b) {
    return ((a.___crtr == b.___crtr) &&
            (a.___obj == b.___obj));
}

inline bool operator != (const CrtdObject& a, const CrtdObject& b) {
    return ((a.___crtr != b.___crtr) ||
            (a.___obj != b.___obj));
}

#endif // CRTDOBJECT_H
