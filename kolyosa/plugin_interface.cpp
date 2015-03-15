#include "plugin_interface.h"

MPluginInterface::MPluginInterface(QObject *parent) :
    QScriptExtensionPlugin(parent)
{
    //
}

MPluginInterface::~MPluginInterface() {
    //
}

_SHARED_EXPORT QStringList MPluginInterface::keys() const {
    return QStringList() << CyrGenericPluginInterface_iid;
}

_SHARED_EXPORT void MPluginInterface::initialize(const QString &/*key*/, QScriptEngine */*engine*/) {
    //
}
