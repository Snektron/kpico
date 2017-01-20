#ifndef EMULATORCONTEXT_H
#define EMULATORCONTEXT_H

#include <Pico80/api/IEmulatorContext.h>
#include <Pico80/api/IPicoQmlEngine.h>

class EmulatorContext: public IEmulatorContext
{
private:
	QQuickItem *display;

public:
	EmulatorContext(IPicoQmlEngine *engine);
	~EmulatorContext();
};

#endif // EMULATORCONTEXT_H
