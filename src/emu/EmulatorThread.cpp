#include "emu/EmulatorThread.h"
#include <QTimer>
#include "emu/Emulator.h"

void EmulatorThread::run()
{
	QTimer timer;
	Emulator emu;

	connect(&timer, SIGNAL(timeout()), &emu, SLOT(tick()));
	connect(this, SIGNAL(emuLoadRom(QString)), &emu, SLOT(loadRom(QString)), Qt::QueuedConnection);
	connect(this, SIGNAL(emuStart()), &emu, SLOT(start()), Qt::QueuedConnection);
	connect(this, SIGNAL(emuStop()), &emu, SLOT(stop()), Qt::QueuedConnection);

	timer.setTimerType(Qt::PreciseTimer);
	timer.start(1);

	exec();
}
