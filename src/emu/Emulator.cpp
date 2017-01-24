#include "emu/Emulator.h"
#include <QFile>
extern "C" {
#include <scas/stack.h>
}

void logCbk(void *data, loglevel_t level, const char *part, const char *message, va_list args)
{
	// do nothing for now...
	Q_UNUSED(data)
	Q_UNUSED(level)
	Q_UNUSED(part)
	Q_UNUSED(message)
	Q_UNUSED(args)
}

void lcdUpdateCbk(void *data, ti_bw_lcd_t *lcd)
{
	Emulator *emu = (Emulator*) data;
	Q_UNUSED(emu)
	Q_UNUSED(lcd)
}

Emulator::Emulator()
{
	log = init_log_z80e(logCbk, 0, L_INFO);
	asic = asic_init(TI84pSE, log);
	hook_add_lcd_update(asic->hook, this, lcdUpdateCbk);
	asic->stopped = 1;
}

Emulator::~Emulator()
{
	asic_free(asic);
	free_log(log);
}

void Emulator::loadRom(QString rom)
{
	QFile file(rom);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	file.read((char*) asic->mmu->flash, 0x4000 * asic->mmu->settings.flash_pages);
	file.close();
}

void Emulator::start()
{
	asic->stopped = 0;
}

void Emulator::tick()
{
	if (!asic->stopped)
		runloop_tick(asic->runloop);
}

void Emulator::stop()
{
	asic->stopped = 1;
}
