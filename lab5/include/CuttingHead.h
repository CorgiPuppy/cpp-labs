#ifndef CUTTINGHEAD_H
#define CUTTINGHEAD_H

#include "Part.h"

class CuttingHead : public Part
{
	public:
		CuttingHead() : Part(1200, 250, 2, 350) {}

		bool breaking() const override
		{
			return deterioration_degree >= service_life;
		}

		friend std::ostream& operator << (std::ostream& os, const CuttingHead& cuttinghead)
		{
			os << "CuttingHead " << static_cast<const Part&>(cuttinghead);
			return os;
		}
};

#endif
