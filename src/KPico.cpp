#include "KPico.h"
#include "gui/Lcd.h"
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
	qmlRegisterType<Lcd>("KPico", 1, 0, "Lcd");
	return new EmulatorContext(engine);
}
