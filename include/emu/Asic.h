#ifndef ASIC_H
#define ASIC_H

#include <picore/api/IEmulator.h>

class Asic: public IEmulator
{
public:
	Asic();
	void initialize(QQuickItem *display);
	void tick();
};

#endif // ASIC_H
