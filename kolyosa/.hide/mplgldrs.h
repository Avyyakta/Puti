#ifndef MPLGLDRS_H
#define MPLGLDRS_H

#include <QSharedDataPointer>
#include <QPluginLoader>

#include "plugin_interface.h"

#include <QString>
#include <QMap>
#include <QObject>

#include "kolyosa.h"
#include "mpplgldr.h"

class _SHARED_EXPORT MPlgLdrs : public QMap<QString, MPPlgLdr>, public QObject
{
    Q_OBJECT

public:
    MPlgLdrs(QObject* prnt = nullptr);
    ~MPlgLdrs();
};

#endif // MPLGLDRS_H
