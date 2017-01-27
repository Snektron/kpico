#include "emu/Asic.h"
#include <QFile>

void lcdUpdateCbk(void *data, ti_bw_lcd_t *lcd)
{
	Asic *asic = (Asic*) data;
	asic->updateLcd(lcd);
}

Asic::Asic(log_t *log):
	log(log),
	mAsic(asic_init(TI84pSE, log))
{
	hook_add_lcd_update(mAsic->hook, this, lcdUpdateCbk);
}

Asic::~Asic()
{
	asic_free(mAsic);
}

asic_t *Asic::asic()
{
	return mAsic;
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
		log_message(log, L_ERROR, "asic", "Failed to open ROM image");
		return;
	}
	file.read((char*) mAsic->mmu->flash, 0x4000 * mAsic->mmu->settings.flash_pages);
	file.close();
	log_message(log, L_DEBUG, "asic", "Successfully loaded ROM image");
}
