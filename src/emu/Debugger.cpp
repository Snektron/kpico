#include "emu/Debugger.h"
#include <stdarg.h>

int dbg_vprint(debugger_state_t *state, const char *msg, va_list list)
{
	Debugger *dbg = (Debugger*) state->interface_state;
	if (dbg)
		dbg->vprint(msg, list);
	return 0;
}

int dbg_print(debugger_state_t *state, const char *msg, ...)
{
	va_list list;
	va_start(list, msg);
	Debugger *dbg = (Debugger*) state->interface_state;
	if (dbg)
		dbg->vprint(msg, list);
	va_end(list);
	return 0;
}

void dbg_free(debugger_state_t *state)
{
	delete state;
}

debugger_state_t* dbg_copy(debugger_state_t *other, const char *title)
{
	Q_UNUSED(title)
	debugger_state_t *state = new debugger_state_t;
	state->print = dbg_print;
	state->vprint = dbg_vprint;
	state->state = other->state;
	state->interface_state = other->interface_state;
	state->asic = other->asic;
	state->debugger = other->debugger;
	state->create_new_state = dbg_copy;
	state->close_window = dbg_free;
	state->log = other->log;
	return state;
}

void dbg_init(debugger_state_t *state, Debugger *dbg)
{
	state->print = dbg_print;
	state->vprint = dbg_vprint;
	state->state = Q_NULLPTR;
	state->interface_state = dbg;
	state->asic = dbg->asic()->asic();
	state->debugger = dbg->debugger();
	state->create_new_state = dbg_copy;
	state->close_window = dbg_free;
	state->log = dbg->log();
}

Debugger::Debugger(log_t *log, Asic *asic):
	mLog(log),
	mAsic(asic)
{
	mAsic->asic()->debugger = init_debugger(asic->asic());
	dbg_init(&mState, this);
}

debugger_t* Debugger::debugger()
{
	return mAsic->asic()->debugger;
}

log_t* Debugger::log()
{
	return mLog;
}

Asic* Debugger::asic()
{
	return mAsic;
}

debugger_state_t* Debugger::state()
{
	return &mState;
}

void Debugger::vprint(const char *msg, va_list list)
{
	QString str = partialLine + QString::vasprintf(msg, list);
	QStringList lines = str.split("\n");

	for (int i = 0; i < lines.length() - 1; i++)
		if (!lines[i].isEmpty())
			log_message(log(), L_INFO, "debugger", lines[i].toUtf8().constData());

	partialLine = lines.length() == 0 ? "" : lines.at(lines.length() - 1);
}

void Debugger::onCommand(QString command)
{
	int ret = debugger_exec(state(), command.toLatin1().data());
	if (ret > 0)
		log_message(log(), L_DEBUG, "debugger", "Command returned %d", ret);
}
