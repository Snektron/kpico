#ifndef EMULATOR_H
#define EMULATOR_H

#include <QObject>
#include <QString>
#include <QUrl>
#include "emu/Log.h"
#include "emu/Asic.h"
#include "emu/Debugger.h"

class Emulator: public QObject
{
	Q_OBJECT
private:
	log_t *log;
	Asic *mAsic;
	Debugger *mDebugger;

public:
	Emulator(log_t *log);
	~Emulator();

	Asic* asic();
	Debugger* debugger();

signals:
	void logMessage(loglevel_t level, QString message);
};

#endif // EMULATOR_H
