#ifndef KPICO_DEBUGGER_H
#define KPICO_DEBUGGER_H

#include <QObject>
#include "emu/Asic.h"
#include "emu/debug/Instruction.h"

extern "C"
{
#include <z80e/debugger/debugger.h>
#include <z80e/debugger/commands.h>
#include <z80e/disassembler/disassemble.h>
#include <z80e/core/registers.h>
}

typedef struct
{
	InstructionList instructions;
	z80registers_t registers;
} DebuggerData;

class Debugger: public QObject
{
	Q_OBJECT
private:
	Asic *mAsic;
	debugger_state_t mState;
	bool mMemDirty;

public:
	typedef struct {
		Debugger *debugger;
		QString line;
	} ExtraData;

	Debugger(Asic *asic);
	Asic* asic();

private:
	QString readHex(uint16_t address, int size);
	void disassemble(DebuggerData *data);

	static int disasmWrite(struct disassemble_memory *mem, const char *msg, ...);
	static uint8_t disasmRead(struct disassemble_memory *mem, uint16_t address);

	static int dbgVprint(debugger_state_t *state, const char *msg, va_list list);
	static int dbgPrint(debugger_state_t *state, const char *msg, ...);
	static void dbgFree(debugger_state_t *state);
	static debugger_state_t* dbgCopy(debugger_state_t *other, const char *title);
	static void dbgInit(debugger_state_t *state, Debugger *dbg);

	static uint8_t memWrite(void *data, uint16_t address, uint8_t value);

public slots:
	void refresh();
	void step();

signals:
	void onRefreshComplete(DebuggerData data);
};

#endif // KPICO_DEBUGGER_H
