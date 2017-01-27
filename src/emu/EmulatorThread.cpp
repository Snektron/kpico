#include "emu/EmulatorThread.h"
#include <QTimer>
#include <QDebug>
#include "emu/Emulator.h"
#include "emu/Log.h"

EmulatorThread::EmulatorThread(AsicQml *asicQml, DebuggerQml *dbgQml):
	asicQml(asicQml),
	dbgQml(dbgQml)
{}

void EmulatorThread::run()
{
	Log log;
	connect(&log, SIGNAL(message(loglevel_t, QString)),
			this, SLOT(logMessage(loglevel_t, QString)),
			Qt::QueuedConnection);

	QTimer timer;
	Emulator emu(log.log());

	connect(emu.asic(), SIGNAL(lcdChanged()),
			asicQml, SIGNAL(onLcdChanged()),
			Qt::QueuedConnection);

	connect(asicQml, SIGNAL(loadRom(QUrl)),
			emu.asic(), SLOT(loadRom(QUrl)),
			Qt::QueuedConnection);

	connect(dbgQml, SIGNAL(command(QString)),
			emu.debugger(), SLOT(onCommand(QString)),
			Qt::QueuedConnection);

//	connect(&timer, SIGNAL(timeout()), &emu, SLOT(tick()));
//	connect(this, SIGNAL(emuLoadRom(QUrl)), &emu, SLOT(loadRom(QUrl)), Qt::QueuedConnection);
//	connect(this, SIGNAL(emuStart()), &emu, SLOT(start()), Qt::QueuedConnection);
//	connect(this, SIGNAL(emuStop()), &emu, SLOT(stop()), Qt::QueuedConnection);
//	connect(&emu, SIGNAL(lcdChanged()), this, SIGNAL(lcdChanged()), Qt::QueuedConnection);

	timer.setTimerType(Qt::PreciseTimer);
	timer.start(1);

	exec();
}

void EmulatorThread::logMessage(loglevel_t level, QString message)
{
	switch(level)
	{
	case L_DEBUG:
		qDebug("%s", message.toUtf8().constData());
		break;
	case L_INFO:
		qInfo("%s", message.toUtf8().constData());
		break;
	case L_WARN:
		qWarning("%s", message.toUtf8().constData());
		break;
	case L_ERROR:
		qCritical("%s", message.toUtf8().constData());
		break;
	}
}
