#include <QDir>

#include "kolyosa.h"

#include "mapplugins.h"
#include "logger.h"

#if defined(WIN32) || defined(_WIN32)
#define ___MASK_PLUGIN "psjr*.dll"
#define ___MASK_DEBUG "d\\.dll$"
#elif defined(LINUX)
#define ___MASK_PLUGIN "libpsjr*.so"
#define ___MASK_DEBUG "d\\.so$"
#else
#error "This OS isn't support!!!"
#endif

PLuginsMap::PLuginsMap() :
    ___map()
{
//    ___inf("called MapPLugins::MapPLugins()...");
    QDir dr(QApplication::applicationDirPath());
    if (!(dr.cd("../plugins"))) return;
    QStringList lsf = dr.entryList(QStringList() << ___MASK_PLUGIN);
    if (lsf.isEmpty()) return;
    QString pth = dr.path();
    foreach(QString s, lsf) {
        int p = s.indexOf(QRegExp(___MASK_DEBUG));
#ifdef IS_DEBUG
        if (p >= 0)
#else
        if (p < 0)
#endif
        {
            QString snm;
            EPluginLoader* ldr = new EPluginLoader(pth+"/"+s, &snm);
            if (ldr != nullptr) {
                if (!(ldr->isValidate())) {
//                    ___inf(QString("не добавлено значение \"%1\" с ключём \"%2\" так как неправильно...") .arg(pth+"/"+s) .arg(snm));
                    delete ldr; ldr = nullptr;
                } else {
//                    ___inf(QString("добавлено значение \"%1\" с ключём \"%2\"...") .arg(pth+"/"+s) .arg(snm));
                    ___map.insert(snm, ldr);
                    ___map[snm] = ldr;
                };
            } else {
//                ___inf(QString("не добавлено значение \"%1\" с ключём \"%2\", так как не выделено памяти...") .arg(pth+"/"+s) .arg(snm));
            };
        };
    };
    ___plugs = this;
}

PLuginsMap::~PLuginsMap() {
    ___plugs = nullptr;
    while(!(___map.isEmpty())) {
        QMap<QString, EPluginLoader*>::iterator it = ___map.end(); it--;
        EPluginLoader* epl = it.value();
        ___map.erase(it);
        delete epl;
        epl = nullptr;
    };
}

