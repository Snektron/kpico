#include "KPicoQml.h"
#include "gui/Lcd.h"

void KPicoQml::createConnections(QQuickItem *display, IPicoQmlEngine *qmlEngine)
{
	Lcd* lcd = display->findChild<Lcd*>("LCD");
	if (!lcd)
		qWarning() << "failed to find LCD.";
	else
		QObject::connect(asicQml(), SIGNAL(onLcdChanged()), lcd, SIGNAL(lcdChanged()));

	QQuickItem *console = qmlEngine->consoleInputComponent();
	if (!console)
		qWarning() << "failed to find console.";
	else
		QObject::connect(console, SIGNAL(commandEntered(QString)), cmdQml(), SIGNAL(command(QString)));
}

AsicQml* KPicoQml::asicQml()
{
	return &mAsicQml;
}

CommandHandlerQml* KPicoQml::cmdQml()
{
	return &mCmdQml;
}

DebuggerQml* KPicoQml::debugger()
{
	return &mDebuggerQml;
}
