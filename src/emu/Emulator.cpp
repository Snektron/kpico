#include "emu/Emulator.h"
#include <QFile>
#include <QThread>

Emulator::Emulator(log_t *log):
	log(log),
	mAsic(log),
	mCmdHandler(&mAsic),
	mDebugger(&mAsic)
{
	log_message(log, L_DEBUG, "emulator", "Initializing emulator");
}

Asic* Emulator::asic()
{
	return &mAsic;
}

CommandHandler* Emulator::cmdHandler()
{
	return &mCmdHandler;
}

Debugger* Emulator::debugger()
{
	return &mDebugger;
}
