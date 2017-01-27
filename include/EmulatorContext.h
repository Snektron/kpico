#ifndef EMULATORCONTEXT_H
#define EMULATORCONTEXT_H

#include <Pico80/api/IEmulatorContext.h>
#include <Pico80/api/IPicoEngine.h>
#include "emu/EmulatorThread.h"
#include "emu/EmulatorQml.h"

class EmulatorContext: public IEmulatorContext
{
private:
	AsicQml asicQml;
	DebuggerQml dbgQml;

	EmulatorThread *emulator;
	QQuickItem *lcd;

public:
	EmulatorContext(IPicoEngine *engine);
	~EmulatorContext();
};

#endif // EMULATORCONTEXT_H
