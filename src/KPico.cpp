#include "KPico.h"
#include "gui/Display.h"
#include "EmulatorContext.h"

KPico::KPico()
{

}

QString KPico::name()
{
	return "kpico";
}

IEmulatorContext* KPico::createContext(IPicoEngine *engine)
{
	qmlRegisterType<Display>("KPico", 1, 0, "Display");
	return new EmulatorContext(engine);
}
