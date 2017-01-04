#include "KPico.h"

KPico::KPico()
{
}

QString KPico::name()
{
	return "kpico";
}

void KPico::registerPlugin(PluginEngine &engine)
{
	engine.registerDisplayQml(QUrl("qrc:/TestDisplay.qml"));
}
