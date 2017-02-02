#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <cstdint>
#include "emu/Asic.h"
#include "emu/debug/Instruction.h"

extern "C"
{
#include <z80e/disassembler/disassemble.h>
}

class Disassembler
{
private:
	Asic *mAsic;
	bool memDirty;

	typedef struct {
		Disassembler *disassembler;
		QString line;
	} ExtraData;

	static int write(struct disassemble_memory *mem, const char *msg, ...);
	static uint8_t read(struct disassemble_memory *mem, uint16_t address);
	static uint8_t writeHook(void *data, uint16_t address, uint8_t value);

	QString readHex(uint16_t address, int size);
public:
	Disassembler(Asic *asic);
	void disassemble(InstructionList *disassembly);
};

#endif // DISASSEMBLER_H
