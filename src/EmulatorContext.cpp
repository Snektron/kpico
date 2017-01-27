#include "EmulatorContext.h"
#include "gui/Lcd.h"
#include <QQmlComponent>
#include <QDebug>
#include <QObject>
extern "C"
{
#include <z80e/log/log.h>
}

EmulatorContext::EmulatorContext(IPicoEngine *engine)
{
	qRegisterMetaType<loglevel_t>("loglevel_t");

	emulator = new EmulatorThread(&asicQml, &dbgQml);
	emulator->start();
	engine->rootContext()->setContextProperty("Asic", &asicQml);
	engine->rootContext()->setContextProperty("Debugger", &dbgQml);

	lcd = engine->qmlEngine()->loadComponent(QUrl("qrc:/qml/Display.qml"));
	engine->qmlEngine()->setDisplay(lcd);

	Lcd* qmlLcd = lcd->findChild<Lcd*>("LCD");
	if (!qmlLcd)
		qWarning() << "failed to find LCD.";
	else
		QObject::connect(&asicQml, SIGNAL(onLcdChanged()), qmlLcd, SIGNAL(lcdChanged()));

	QQuickItem *console = engine->qmlEngine()->consoleInputComponent();
	if (!console)
		qWarning() << "failed to find console.";
	else
		QObject::connect(console, SIGNAL(commandEntered(QString)), &dbgQml, SIGNAL(command(QString)));
}

EmulatorContext::~EmulatorContext()
{
	emulator->quit();
	emulator->wait();

	delete lcd;
	delete emulator;
}
