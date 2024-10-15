#ifndef ELECTRICMOTOR_H
#define ELECTRICMOTOR_H

#include "Part.h"

class ElectricMotor : public Part
{
	public:
		ElectricMotor() : Part(1500, 300, 2, 300) {}

		bool breaking() const override
		{
			return deterioration_degree >= service_life;
		}

		friend std::ostream& operator << (std::ostream& os, const ElectricMotor& electricmotor)
		{
			os << "ElectricMotor " << static_cast<const Part&>(electricmotor);
			return os;
		}
};

#endif
