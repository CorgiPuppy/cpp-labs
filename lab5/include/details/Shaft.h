#ifndef SHAFT_H
#define SHAFT_H

#include "Part.h"
#include "../strategy/DefaultPartStrategy.h"

class Shaft : public Part
{
	public:
		Shaft() : Part(Constants::replacement_cost_shaft, Constants::repair_cost_shaft, Constants::repair_time_shaft, Constants::service_life_shaft, new DefaultPartStrategy()) {}

		friend std::ostream& operator << (std::ostream& os, const Shaft& s);
};

std::ostream& operator << (std::ostream& os, const Shaft& s)
{
    return os << "Shaft " << static_cast<const Part&>(s);
}

#endif
