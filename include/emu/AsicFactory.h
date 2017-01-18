#ifndef ASICFACTORY_H
#define ASICFACTORY_H

#include <picore/PluginEngine.h>
#include <picore/api/IEmulator.h>
#include "emu/Asic.h"

class AsicFactory: public EmulatorFactory
{
	IEmulator* create()
	{
		return new Asic();
	}
};

#endif // ASICFACTORY_H
