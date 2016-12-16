#include "KPico.h"
#include <QDebug>
#include <core/Logger.h>

KPico::KPico()
{

}

QString KPico::name()
{
	return "KPico";
}

IEmulator* KPico::createEmulator()
{
	return nullptr;
}

void KPico::destroyEmulator(IEmulator* emulator)
{

}

IDisplay* KPico::createDisplay()
{
	return nullptr;
}

void KPico::destroyDisplay(IDisplay *display)
{

}
