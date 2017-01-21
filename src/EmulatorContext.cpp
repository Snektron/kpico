#include "EmulatorContext.h"
#include <QQmlComponent>
#include <QDebug>

EmulatorContext::EmulatorContext(IPicoEngine *engine)
{
	display = engine->qmlEngine()->setDisplay(QUrl("qrc:/qml/Display.qml"));
}

EmulatorContext::~EmulatorContext()
{
	delete display;
}
