#include "emu/debug/DebuggerQml.h"
#include <QDebug>

InstructionModel* DebuggerQml::instructions()
{
	return &mInstructions;
}

QVariantMap DebuggerQml::registers()
{
	return mRegisters;
}

void DebuggerQml::setRegisters(z80registers_t *registers)
{
	mRegisters["a"] = registers->A;
	mRegisters["b"] = registers->B;
	mRegisters["c"] = registers->C;
	mRegisters["d"] = registers->D;
	mRegisters["e"] = registers->E;
	mRegisters["f"] = registers->F;
	mRegisters["h"] = registers->H;
	mRegisters["l"] = registers->L;
	mRegisters["ixl"] = registers->IXL;
	mRegisters["ixh"] = registers->IXH;
	mRegisters["iyl"] = registers->IYL;
	mRegisters["iyh"] = registers->IYH;
	mRegisters["i"] = registers->I;
	mRegisters["r"] = registers->R;

	mRegisters["af"] = registers->AF;
	mRegisters["bc"] = registers->BC;
	mRegisters["de"] = registers->DE;
	mRegisters["hl"] = registers->HL;
	mRegisters["ix"] = registers->IX;
	mRegisters["iy"] = registers->IY;

	mRegisters["_af"] = registers->_AF;
	mRegisters["_bc"] = registers->_BC;
	mRegisters["_de"] = registers->_DE;
	mRegisters["_hl"] = registers->_HL;

	mRegisters["sp"] = registers->SP;
	mRegisters["pc"] = registers->PC;
}

void DebuggerQml::onRefreshComplete(DebuggerData data)
{
	if (data.instructions.size() > 0)
		mInstructions.setInstructions(data.instructions);
	setRegisters(&data.registers);
	emit refreshed();
}
