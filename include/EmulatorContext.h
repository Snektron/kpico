#ifndef EMULATORCONTEXT_H
#define EMULATORCONTEXT_H

#include <Pico80/api/IEmulatorContext.h>
#include <Pico80/api/IPicoEngine.h>
#include "emu/EmulatorThread.h"

class EmulatorContext: public IEmulatorContext
{
private:
	QQuickItem *display;
	EmulatorThread *emulator;

public:
	EmulatorContext(IPicoEngine *engine);
	~EmulatorContext();
};

#endif // EMULATORCONTEXT_H
