#ifndef KPICO_H
#define KPICO_H

#include <QObject>
#include <QtPlugin>
#include <api/IPlugin.h>
#include <api/IEmulator.h>

class KPico : public QObject, public IPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID IPlugin_iid FILE "kpico.json")
	Q_INTERFACES(IPlugin)
public:
	KPico();

	IEmulator* createEmulator();
	void destroyEmulator(IEmulator* emulator);
};

#endif // KPICO_H
