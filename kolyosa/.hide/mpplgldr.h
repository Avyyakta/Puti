#ifndef MPPLGLDR_H
#define MPPLGLDR_H

#include <QStringList>
#include <QSharedDataPointer>

#include "shplgldr.h"

/* template <>
class QSharedDataPointer<shPlgLdr>
{
}; */

/* template <>
class QSharedDataPointer<shdObjPlg>
{
}; */

typedef class QSharedDataPointer<shdObjPlg> shshObjPlg;

class MapPlgObj : public QMap<QString, shshObjPlg> {
public:
    MapPlgObj() = default;
};

class MPPlgLdr : public QObject
{
    Q_OBJECT

    QString                         ___path;
    QStringList                     ___types;
    QSharedDataPointer<shPlgLdr>    ___ldr;

    MapPlgObj                       ___mapObjs;
public:

    MPPlgLdr(const QString& pth, QObject* prnt = nullptr);
    MPPlgLdr(const MPPlgLdr &ppl);
    MPPlgLdr& operator=(const MPPlgLdr&b);

    bool load();
    bool unload();

    QObject* createObject(const QString& nmtp, const QString& nmobj = QString(), QObject* prnt = 0);
    bool deleteObject(QObject* o);


    inline QString name() { if (___ldr.data() == nullptr) return QString(); return ___ldr.data()->___intrfc->name(); }

    inline QStringList types() { if (___ldr.data() == nullptr) return QStringList(); return ___ldr->___intrfc->get_types(); }

    inline QString caption(bool full=false) { if (___ldr.data() == nullptr) return QString(); return ___ldr->___intrfc->caption(full); }

    inline QString help(bool full=false) { if (___ldr.data() == nullptr) return QString(); return ___ldr->___intrfc->help(full); }

    inline QString version(bool full=false) { if (___ldr.data() == nullptr) return QString(); return ___ldr->___intrfc->version(full); }

    inline QStringList keys() const { if (___ldr.data() == nullptr) return QStringList(); return ___ldr->___intrfc->keys(); }

    inline void initialize(const QString &key, QScriptEngine *engine) { if (___ldr.data() == nullptr) return; ___ldr->___intrfc->initialize(key, engine); }


};

#endif // MPPLGLDR_H
