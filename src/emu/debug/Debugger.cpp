#include "emu/debug/Debugger.h"
#include <stdarg.h>

int Debugger::dbgVprint(debugger_state_t *state, const char *msg, va_list list)
{
	Q_UNUSED(state)
	Q_UNUSED(msg)
	Q_UNUSED(list)
	return 0;
}

int Debugger::dbgPrint(debugger_state_t *state, const char *msg, ...)
{
	Q_UNUSED(state)
	Q_UNUSED(msg)
	return 0;
}

void Debugger::dbgFree(debugger_state_t *state)
{
	delete state;
}

debugger_state_t* Debugger::dbgCopy(debugger_state_t *other, const char *title)
{
	Q_UNUSED(title)
	debugger_state_t *state = new debugger_state_t;
	state->print = Debugger::dbgPrint;
	state->vprint = Debugger::dbgVprint;
	state->state = other->state;
	state->interface_state = other->interface_state;
	state->asic = other->asic;
	state->debugger = other->debugger;
	state->create_new_state = Debugger::dbgCopy;
	state->close_window = Debugger::dbgFree;
	state->log = other->log;
	return state;
}

void Debugger::dbgInit(debugger_state_t *state, Debugger *dbg)
{
	state->print = Debugger::dbgPrint;
	state->vprint = Debugger::dbgVprint;
	state->state = Q_NULLPTR;
	state->interface_state = dbg;
	state->asic = dbg->asic->asic();
	state->debugger = dbg->asic->asic()->debugger;
	state->create_new_state = Debugger::dbgCopy;
	state->close_window = Debugger::dbgFree;
	state->log = dbg->asic->log();
}

Debugger::Debugger(Asic *asic):
	asic(asic),
	disassembler(asic)
{
	dbgInit(&state, this);
}

void Debugger::refresh()
{
	DebuggerData data;

	disassembler.disassemble(&data.instructions);
	data.registers = asic->asic()->cpu->registers;

	emit onRefreshComplete(data);
}

void Debugger::step()
{
	command_step(&state, 0, Q_NULLPTR);
}
