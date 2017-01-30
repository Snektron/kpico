#ifndef DEBUGGERQML_H
#define DEBUGGERQML_H

#include <QObject>
#include <QVariantMap>
#include "emu/debug/Debugger.h"
#include "emu/debug/InstructionModel.h"

class DebuggerQml: public QObject
{
	Q_OBJECT
	Q_PROPERTY(InstructionModel *instructions READ instructions() CONSTANT)
	Q_PROPERTY(QVariantMap registers READ registers() CONSTANT)
private:
	InstructionModel mInstructions;
	QVariantMap mRegisters;

public:
	InstructionModel* instructions();
	QVariantMap registers();

private:
	void setRegisters(z80registers_t *registers);

public slots:
	void onRefreshComplete(DebuggerData data);

signals:
	void refresh();
	void step();

	void refreshed();
};

#endif // DEBUGGERQML_H
