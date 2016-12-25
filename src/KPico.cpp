#include "KPico.h"
#include <QDebug>

KPico::KPico()
{

}

QString KPico::name()
{
	return "kpico";
}

void KPico::registerPlugin(PluginEngine *engine)
{
//	Q_UNUSED(engine)
	engine->registerDisplayFactory(nullptr);
}

IEmulator* KPico::createEmulator()
{
	return nullptr;
}

IDisplay* KPico::createDisplay()
{
	return nullptr;
}
