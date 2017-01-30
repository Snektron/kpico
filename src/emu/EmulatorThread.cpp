#include "emu/EmulatorThread.h"
#include <QTimer>
#include <QDebug>
#include "emu/Emulator.h"
#include "emu/Log.h"

EmulatorThread::EmulatorThread(KPicoQml *kpico):
	kpico(kpico)
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
			kpico->asicQml(), SIGNAL(onLcdChanged()),
			Qt::QueuedConnection);

	connect(kpico->asicQml(), SIGNAL(loadRom(QUrl)),
			emu.asic(), SLOT(loadRom(QUrl)),
			Qt::QueuedConnection);

	connect(kpico->cmdQml(), SIGNAL(command(QString)),
			emu.cmdHandler(), SLOT(onCommand(QString)),
			Qt::QueuedConnection);

	connect(kpico->debugger(), SIGNAL(refresh()),
			emu.debugger(), SLOT(refresh()),
			Qt::QueuedConnection);

	connect(kpico->debugger(), SIGNAL(step()),
			emu.debugger(), SLOT(step()),
			Qt::QueuedConnection);

	connect(emu.debugger(), SIGNAL(onRefreshComplete(DebuggerData)),
			kpico->debugger(), SLOT(onRefreshComplete(DebuggerData)),
			Qt::QueuedConnection);

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
