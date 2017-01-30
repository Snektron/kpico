#ifndef EMULATORCONTEXT_H
#define EMULATORCONTEXT_H

#include <Pico80/api/IEmulatorContext.h>
#include <Pico80/api/IPicoEngine.h>
#include "emu/EmulatorThread.h"
#include "KPicoQml.h"

class EmulatorContext: public IEmulatorContext
{
private:
	KPicoQml kpico;
	EmulatorThread *emulator;
	QQuickItem *display;
	QQuickItem *debugView;

public:
	EmulatorContext(IPicoEngine *engine);
	~EmulatorContext();
};

#endif // EMULATORCONTEXT_H
