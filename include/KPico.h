#ifndef KPICO_H
#define KPICO_H

#include <QObject>
#include <QtPlugin>
#include <Pico80/api/IPlugin.h>
#include <Pico80/api/IEmulatorContext.h>
#include <Pico80/api/IPicoEngine.h>

class KPico: public QObject, public IPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID IPlugin_iid FILE "kpico.json")
	Q_INTERFACES(IPlugin)
public:
	KPico();
	QString name();
	IEmulatorContext* createContext(IPicoEngine *engine);
};

#endif // KPICO_H
