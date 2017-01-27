#ifndef EMULATORTHREAD_H
#define EMULATORTHREAD_H

#include <QThread>
#include <QString>
#include <QUrl>
#include "emu/EmulatorQml.h"

extern "C"
{
#include <z80e/log/log.h>
}

class EmulatorThread: public QThread
{
	Q_OBJECT
private:
	AsicQml *asicQml;
	DebuggerQml *dbgQml;

public:
	EmulatorThread(AsicQml *asicSig, DebuggerQml *dbgSig);
	void run();

private slots:
	void logMessage(loglevel_t level, QString message);
};

#endif // EMULATORTHREAD_H
