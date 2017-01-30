#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <QObject>
#include <QString>
#include <stdarg.h>
#include "emu/Asic.h"
#include "emu/Log.h"

extern "C"
{
#include <z80e/debugger/debugger.h>
}

class CommandHandler: public QObject
{
	Q_OBJECT
private:
	Asic *mAsic;
	debugger_state_t mState;
	QString partialLine;

public:
	CommandHandler(Asic *asic);
	debugger_t* debugger();
	log_t* log();
	asic_t* asic();
	debugger_state_t* state();
	void vprint(const char *msg, va_list list);

public slots:
	void onCommand(QString command);

private:
	static int dbgVprint(debugger_state_t *state, const char *msg, va_list list);
	static int dbgPrint(debugger_state_t *state, const char *msg, ...);
	static void dbgFree(debugger_state_t *state);
	static debugger_state_t* dbgCopy(debugger_state_t *other, const char *title);
	static void dbgInit(debugger_state_t *state, CommandHandler *dbg);
};

#endif // COMMANDHANDLER_H
