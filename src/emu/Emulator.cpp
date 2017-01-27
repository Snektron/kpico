#include "emu/Emulator.h"
#include <QFile>
#include <QThread>

Emulator::Emulator(log_t *log):
	log(log),
	mAsic(new Asic(log)),
	mDebugger(new Debugger(log, mAsic))
{
	log_message(log, L_DEBUG, "emulator", "Initializing emulator");
}

Emulator::~Emulator()
{
	delete mAsic;
}

Asic* Emulator::asic()
{
	return mAsic;
}

Debugger* Emulator::debugger()
{
	return mDebugger;
}
