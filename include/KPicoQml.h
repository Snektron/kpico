#ifndef KPICOQML_H
#define KPICOQML_H

#include <QObject>
#include <QQuickItem>
#include <Pico80/api/IPicoQmlEngine.h>
#include "emu/debug/DebuggerQml.h"

class AsicQml: public QObject
{
	Q_OBJECT
signals:
	void onLcdChanged();
	void loadRom(QUrl filename);
};

class CommandHandlerQml: public QObject
{
	Q_OBJECT
signals:
	void command(QString command);
};

class KPicoQml: public QObject
{
	Q_OBJECT
	Q_PROPERTY(AsicQml *asic READ asicQml CONSTANT)
	Q_PROPERTY(DebuggerQml *debugger READ debugger() CONSTANT)

private:
	AsicQml mAsicQml;
	CommandHandlerQml mCmdQml;
	DebuggerQml mDebuggerQml;

public:
	void createConnections(QQuickItem *display, IPicoQmlEngine *qmlEngine);
	AsicQml* asicQml();
	CommandHandlerQml* cmdQml();
	DebuggerQml* debugger();
};

#endif // KPICOQML_H
