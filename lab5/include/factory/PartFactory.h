#ifndef PARTFACTORY_H
#define PARTFACTORY_H

#include "../details/Shaft.h"
#include "../details/ElectricMotor.h"
#include "../details/ControlPanel.h"
#include "../details/CuttingHead.h"

#include <cstring>

class PartFactory
{
	public:
		static Part* createPart(const char* type) {
			if (strcmp(type, "Shaft") == 0) return new Shaft();
			if (strcmp(type, "ElectricMotor") == 0) return new ElectricMotor();
			if (strcmp(type, "ControlPanel") == 0) return new ControlPanel();
			if (strcmp(type, "CuttingHead") == 0) return new CuttingHead();
			return nullptr;
		}
};

#endif
