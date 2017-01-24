#ifndef EMULATORTHREAD_H
#define EMULATORTHREAD_H

#include <QThread>
#include <QString>

class EmulatorThread: public QThread
{
	Q_OBJECT
public:
	void run();

signals:
	void emuLoadRom(QString rom);
	void emuStart();
	void emuStop();
};

#endif // EMULATORTHREAD_H
