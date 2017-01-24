#ifndef EMULATOR_H
#define EMULATOR_H

#include <QObject>
#include <QString>

extern "C"
{
#include <z80e/ti/asic.h>
#include <z80e/ti/hardware/t6a04.h>
#include <z80e/log/log.h>
}

class Emulator: public QObject
{
	Q_OBJECT
private:
	log_t *log;
	asic_t *asic;

public:
	Emulator();
	~Emulator();

public slots:
	void loadRom(QString rom);
	void start();
	void tick();
	void stop();
};

#endif // EMULATOR_H
