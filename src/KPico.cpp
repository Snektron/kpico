#include "KPico.h"
#include <QDebug>

KPico::KPico()
{
	qDebug() << "KPico created!";
}

IEmulator* KPico::createEmulator()
{
	qDebug() << "createEmulator";
	return nullptr;
}

void KPico::destroyEmulator(IEmulator* emulator)
{
	qDebug() << "destroyEmulator";
}
