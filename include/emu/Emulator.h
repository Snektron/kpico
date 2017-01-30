#ifndef EMULATOR_H
#define EMULATOR_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QVariantMap>
#include "emu/Log.h"
#include "emu/Asic.h"
#include "emu/debug/CommandHandler.h"
#include "emu/debug/Debugger.h"

class Emulator: public QObject
{
	Q_OBJECT
private:
	log_t *log;
	Asic mAsic;
	CommandHandler mCmdHandler;
	Debugger mDebugger;

public:
	Emulator(log_t *log);

	Asic* asic();
	CommandHandler* cmdHandler();
	Debugger* debugger();
};

#endif // EMULATOR_H
