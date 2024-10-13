#ifndef SHAFT_H
#define SHAFT_H

#include "Part.h"

class Shaft : public Part
{
	public:
		Shaft() : Part(500, 100, 1, 200) {}

		bool breaking() const override
		{
			return deterioration_degree >= service_life;
		}

		friend std::ostream& operator << (std::ostream& os, const Shaft& shaft)
		{
			os << "Shaft " << static_cast<const Part&>(shaft);
			return os;
		}
};

#endif
