#include "emu/debug/Debugger.h"
#include <stdarg.h>

Debugger::Debugger(Asic *asic):
	mAsic(asic),
	mMemDirty(true)
{
	disassembler_init();
	dbgInit(&mState, this);
	hook_add_memory_write(mAsic->asic()->hook, 0, 65535, this, memWrite);
}

Asic* Debugger::asic()
{
	return mAsic;
}

QString Debugger::readHex(uint16_t address, int size)
{
	QString hex = "";
	for (int i = 0; i < size; i++)
	{
		asic_t *asic = mAsic->asic();
		int n = asic->cpu->read_byte(asic->cpu->memory, address + i);
		hex += QString::number(n, 16).rightJustified(2, '0');
	}
	return hex;
}

void Debugger::disassemble(DebuggerData *data)
{
	ExtraData extra;
	extra.debugger = this;

	struct disassemble_memory mem;
	mem.extra_data = &extra;
	mem.read_byte = disasmRead;
	mem.current = 0;

	uint16_t last = 0;
	do
	{
		last = mem.current;

		Instruction instr;
		instr.address = mem.current;
		instr.size = parse_instruction(&mem, disasmWrite, false);
		instr.hex = readHex(last, instr.size);
		instr.decoded = extra.line;

		data->instructions.addInstruction(instr);

		extra.line = "";
	} while (last < mem.current); // detect overflow

	mMemDirty = false;
}

int Debugger::disasmWrite(struct disassemble_memory *mem, const char *msg, ...)
{
	ExtraData *data = (ExtraData*) mem->extra_data;
	va_list list;
	va_start(list, msg);
	data->line.append(QString::vasprintf(msg, list));
	va_end(list);
	return 0;
}

uint8_t Debugger::disasmRead(struct disassemble_memory *mem, uint16_t address)
{
	ExtraData *data = (ExtraData*) mem->extra_data;
	asic_t *asic = data->debugger->asic()->asic();
	return asic->cpu->read_byte(asic->cpu->memory, address);
}

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
	state->asic = dbg->asic()->asic();
	state->debugger = dbg->asic()->asic()->debugger;
	state->create_new_state = Debugger::dbgCopy;
	state->close_window = Debugger::dbgFree;
	state->log = dbg->asic()->log();
}

uint8_t Debugger::memWrite(void *data, uint16_t address, uint8_t value)
{
	Q_UNUSED(address)
	Debugger *dbg = (Debugger*) data;
	dbg->mMemDirty = true;
	return value;
}

void Debugger::refresh()
{
	DebuggerData data;
	if (mMemDirty)
		disassemble(&data);
	data.registers = mAsic->asic()->cpu->registers;
	emit onRefreshComplete(data);
}

void Debugger::step()
{
	command_step(&mState, 0, Q_NULLPTR);
}
