#ifndef KPICO_H
#define KPICO_H

#include <QObject>
#include <QtPlugin>
#include <picore/api/IPlugin.h>
#include <picore/api/IEmulator.h>
#include <picore/PluginEngine.h>

class KPico : public QObject, public IPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID IPlugin_iid FILE "kpico.json")
	Q_INTERFACES(IPlugin)
public:
	KPico();
	QString name();
	void registerPlugin(PluginEngine &engine);
};

#endif // KPICO_H
