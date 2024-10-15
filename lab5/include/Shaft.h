#ifndef SHAFT_H
#define SHAFT_H

#include "Part.h"

class Shaft : public Part
{
	public:
		Shaft() : Part(Constants::replacement_cost_shaft, Constants::repair_cost_shaft, Constants::repair_time_shaft, Constants::service_life_shaft) {}

		bool breaking() const override
		{
			return deterioration_degree >= service_life;
		}

		friend std::ostream& operator << (std::ostream& os, const Shaft& s)
		{
			return os << "Shaft " << static_cast<const Part&>(s);
		}
};

#endif
