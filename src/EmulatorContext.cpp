#include "EmulatorContext.h"
#include <QQmlComponent>
#include <QDebug>

EmulatorContext::EmulatorContext(IPicoEngine *engine)
{
	display = engine->qmlEngine()->loadComponent(QUrl("qrc:/qml/Display.qml"));
	emulator = new EmulatorThread();
	emulator->start();

	engine->rootContext()->setContextProperty("Emulator", emulator);
	engine->qmlEngine()->setDisplay(display);
}

EmulatorContext::~EmulatorContext()
{
	emulator->quit();
	emulator->wait();

	delete display;
	delete emulator;
}
