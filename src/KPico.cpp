#include "KPico.h"
#include <QDebug>

KPico::KPico()
{

}

QString KPico::name()
{
	return "kpico";
}

IEmulator* KPico::createEmulator()
{
	return nullptr;
}

IDisplay* KPico::createDisplay()
{
	return nullptr;
}
