#include "EmulatorContext.h"
#include <QQmlComponent>
#include <QDebug>

EmulatorContext::EmulatorContext(IPicoQmlEngine *engine)
{
	display = engine->setDisplay(QUrl("qrc:/qml/Display.qml"));
}

EmulatorContext::~EmulatorContext()
{
	delete display;
}
