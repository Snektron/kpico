#include "KPico.h"
#include <QDebug>

KPico::KPico()
{
	qInfo() << "KPico constructor";
}

QString KPico::name()
{
	return "kpico";
}

void KPico::registerPlugin(PluginEngine &engine)
{
	Q_UNUSED(engine)
}
