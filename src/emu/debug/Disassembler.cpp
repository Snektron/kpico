#include "emu/debug/Disassembler.h"
#include <QString>

int Disassembler::write(struct disassemble_memory *mem, const char *msg, ...)
{
	ExtraData *data = (ExtraData*) mem->extra_data;

	va_list list;
	va_start(list, msg);
	data->line.append(QString::vasprintf(msg, list));
	va_end(list);

	return 0;
}

uint8_t Disassembler::read(struct disassemble_memory *mem, uint16_t address)
{
	ExtraData *data = (ExtraData*) mem->extra_data;
	asic_t *asic = data->disassembler->mAsic->asic();
	return asic->cpu->read_byte(asic->cpu->memory, address);
}

uint8_t Disassembler::writeHook(void *data, uint16_t address, uint8_t value)
{
	Q_UNUSED(address)
	Disassembler *dasm = (Disassembler*) data;
	dasm->memDirty = true;
	return value;
}

QString Disassembler::readHex(uint16_t address, int size)
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

Disassembler::Disassembler(Asic *asic):
	mAsic(asic),
	memDirty(true)
{
	disassembler_init();
	hook_add_memory_write(mAsic->asic()->hook, 0, 65535, this, writeHook);
}

void Disassembler::disassemble(InstructionList *disassembly)
{
	if (!memDirty)
		return;

	ExtraData extra;
	extra.disassembler = this;

	struct disassemble_memory mem;
	mem.extra_data = &extra;
	mem.read_byte = read;
	mem.current = 0;

	uint16_t last = 0;
	do
	{
		last = mem.current;

		Instruction instr;
		instr.address = mem.current;
		instr.size = parse_instruction(&mem, write, false);
		instr.hex = readHex(last, instr.size);
		instr.decoded = extra.line;

		disassembly->addInstruction(instr);

		extra.line = "";
	} while (last < mem.current); // detect overflow

	memDirty = false;
}
