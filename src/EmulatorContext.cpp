#include "EmulatorContext.h"
#include <QQmlComponent>
#include <QDebug>
#include <QObject>

EmulatorContext::EmulatorContext(IPicoEngine *engine)
{
	engine->theme()->addFile(":/theme/kpico.thm");

	emulator = new EmulatorThread(&kpico);
	emulator->start();
	engine->rootContext()->setContextProperty("KPico", &kpico);

	display = engine->qmlEngine()->loadComponent(QUrl("qrc:/qml/Display.qml"));
	engine->qmlEngine()->setDisplay(display);

	debugView = engine->qmlEngine()->loadComponent(QUrl("qrc:/qml/DebugView.qml"));
	engine->qmlEngine()->addSidebarView(debugView, "debugview");

	kpico.createConnections(display, engine->qmlEngine());
}

EmulatorContext::~EmulatorContext()
{
	emulator->quit();
	emulator->wait();

	delete display;
	delete debugView;
	delete emulator;
}
