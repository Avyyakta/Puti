#include <QApplication>
#include <QDir>
#include <QFile>

#include "mplgldrs.h"

MPlgLdrs::MPlgLdrs(QObject* prnt) :
    QMap<QString, MPPlgLdr>(),
    QObject(prnt)
{

    QDir dr(QApplication::applicationDirPath());
    if (!(dr.cd("../plugins"))) return;
    QStringList entrs = dr.entryList(QStringList() << "*.dll");
    QStringList::iterator it = entrs.begin();
    while(it != entrs.end()) {
#ifdef IS_DEBUG
        if ((*it).indexOf(QRegExp("d\\.dll$"))<0)
#else
        if ((*it).indexOf(QRegExp("d\\.dll$"))>=0)
#endif
        {
            entrs.erase(it); it = entrs.begin();
        } else
            it++;
    };
    if (entrs.isEmpty()) return;
    foreach (QString var, entrs) {
        MPPlgLdr ppl(var, this);
        insert(ppl.name(), ppl);
    };
}

