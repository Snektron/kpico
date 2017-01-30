#ifndef KPICO_ASIC_H
#define KPICO_ASIC_H

#include <QObject>
#include <QUrl>
#include "emu/Log.h"

extern "C"
{
#include <z80e/ti/asic.h>
#include <z80e/ti/hardware/t6a04.h>
#include <z80e/debugger/debugger.h>
#include <z80e/debugger/hooks.h>
}

class Asic: public QObject
{
	Q_OBJECT
private:
	log_t *mLog;
	asic_t *mAsic;

public:
	Asic(log_t *log);
	~Asic();

	asic_t* asic();
	log_t* log();

	void updateLcd(ti_bw_lcd_t *lcd);

public slots:
	void loadRom(QUrl filename);

signals:
	void lcdChanged();
};

#endif // KPICO_ASIC_H
