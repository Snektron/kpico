#include "KPico.h"
#include "gui/Lcd.h"
#include "EmulatorContext.h"
#include "emu/Log.h"
#include "emu/debug/Debugger.h"

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
	qRegisterMetaType<loglevel_t>("loglevel_t");
	qRegisterMetaType<DebuggerData>("DebuggerData");
	return new EmulatorContext(engine);
}
