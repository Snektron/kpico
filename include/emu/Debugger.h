#ifndef KPICO_DEBUGGER_H
#define KPICO_DEBUGGER_H

#include <QObject>
#include <QString>
#include <stdarg.h>
#include "emu/Asic.h"
#include "emu/Log.h"

extern "C"
{
#include <z80e/debugger/debugger.h>
}

class Debugger: public QObject
{
	Q_OBJECT
private:
	log_t *mLog;
	Asic *mAsic;
	debugger_state_t mState;
	QString partialLine;

public:
	Debugger(log_t *log,  Asic *asic);
	debugger_t* debugger();
	log_t* log();
	Asic* asic();
	debugger_state_t* state();
	void vprint(const char *msg, va_list list);

public slots:
	void onCommand(QString command);
};

#endif // KPICO_DEBUGGER_H
