#include "emu/Asic.h"
#include <QFile>

void lcdUpdateCbk(void *data, ti_bw_lcd_t *lcd)
{
	Asic *asic = (Asic*) data;
	asic->updateLcd(lcd);
}

Asic::Asic(log_t *log):
	mLog(log),
	mAsic(asic_init(TI84pSE, log))
{
	mAsic->debugger = init_debugger(mAsic);
	mAsic->debugger->state = DEBUGGER_DISABLED;
	hook_add_lcd_update(mAsic->hook, this, lcdUpdateCbk);
}

Asic::~Asic()
{
	free_debugger(mAsic->debugger);
	asic_free(mAsic);
}

asic_t* Asic::asic()
{
	return mAsic;
}

log_t* Asic::log()
{
	return mLog;
}

void Asic::updateLcd(ti_bw_lcd_t *lcd)
{
	Q_UNUSED(lcd)
	emit lcdChanged();
}

void Asic::loadRom(QUrl filename)
{
	QFile file(filename.toLocalFile());
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		log_message(mLog, L_ERROR, "asic", "Failed to open ROM image");
		return;
	}
	file.read((char*) mAsic->mmu->flash, 0x4000 * mAsic->mmu->settings.flash_pages);
	file.close();
	log_message(mLog, L_DEBUG, "asic", "Successfully loaded ROM image");
}
