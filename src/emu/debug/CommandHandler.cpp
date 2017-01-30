#include "emu/debug/CommandHandler.h"
#include <stdarg.h>

CommandHandler::CommandHandler(Asic *asic):
	mAsic(asic)
{
	dbgInit(&mState, this);
}

debugger_t* CommandHandler::debugger()
{
	return mAsic->asic()->debugger;
}

log_t* CommandHandler::log()
{
	return mAsic->log();
}

asic_t* CommandHandler::asic()
{
	return mAsic->asic();
}

debugger_state_t* CommandHandler::state()
{
	return &mState;
}

void CommandHandler::vprint(const char *msg, va_list list)
{
	QString str = partialLine + QString::vasprintf(msg, list);
	QStringList lines = str.split("\n");

	for (int i = 0; i < lines.length() - 1; i++)
		if (!lines[i].isEmpty())
			log_message(log(), L_INFO, "cmdhndlr", lines[i].toUtf8().constData());

	partialLine = lines.length() == 0 ? "" : lines.at(lines.length() - 1);
}

void CommandHandler::onCommand(QString command)
{
	int ret = debugger_exec(state(), command.toLatin1().data());
	if (ret > 0)
		log_message(log(), L_DEBUG, "cmdhndlr", "Command returned %d", ret);
}

int CommandHandler::dbgVprint(debugger_state_t *state, const char *msg, va_list list)
{
	CommandHandler *dbg = (CommandHandler*) state->interface_state;
	if (dbg)
		dbg->vprint(msg, list);
	return 0;
}

int CommandHandler::dbgPrint(debugger_state_t *state, const char *msg, ...)
{
	va_list list;
	va_start(list, msg);
	CommandHandler *dbg = (CommandHandler*) state->interface_state;
	if (dbg)
		dbg->vprint(msg, list);
	va_end(list);
	return 0;
}

void CommandHandler::dbgFree(debugger_state_t *state)
{
	delete state;
}

debugger_state_t* CommandHandler::dbgCopy(debugger_state_t *other, const char *title)
{
	Q_UNUSED(title)
	debugger_state_t *state = new debugger_state_t;
	state->print = CommandHandler::dbgPrint;
	state->vprint = CommandHandler::dbgVprint;
	state->state = other->state;
	state->interface_state = other->interface_state;
	state->asic = other->asic;
	state->debugger = other->debugger;
	state->create_new_state = CommandHandler::dbgCopy;
	state->close_window = CommandHandler::dbgFree;
	state->log = other->log;
	return state;
}

void CommandHandler::dbgInit(debugger_state_t *state, CommandHandler *dbg)
{
	state->print = CommandHandler::dbgPrint;
	state->vprint = CommandHandler::dbgVprint;
	state->state = Q_NULLPTR;
	state->interface_state = dbg;
	state->asic = dbg->asic();
	state->debugger = dbg->debugger();
	state->create_new_state = CommandHandler::dbgCopy;
	state->close_window = CommandHandler::dbgFree;
	state->log = dbg->log();
}
