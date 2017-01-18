#include "KPico.h"
#include "gui/Display.h"

#include "emu/AsicFactory.h"

KPico::KPico()
{}

QString KPico::name()
{
	return "kpico";
}

void KPico::registerPlugin(PluginEngine &engine)
{
	qmlRegisterType<Display>("KPico", 1, 0, "Display");

	engine.registerDisplayQml(QUrl("qrc:/qml/Display.qml"));
	engine.registerEmulatorFactory(new AsicFactory());
}
