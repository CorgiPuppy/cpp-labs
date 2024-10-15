#ifndef ELECTRICMOTOR_H
#define ELECTRICMOTOR_H

#include "Part.h"

class ElectricMotor : public Part
{
	public:
		ElectricMotor() : Part
		(
			Constants::replacement_cost_electric_motor, 
			Constants::repair_cost_electric_motor,
			Constants::repair_time_electric_motor,
			Constants::service_life_electric_motor
		) {}

		bool breaking() const override
		{
			return deterioration_degree >= service_life;
		}

		friend std::ostream& operator << (std::ostream& os, const ElectricMotor& em);
};

std::ostream& operator << (std::ostream& os, const ElectricMotor& em)
{
	return os << "ElectricMotor " << static_cast<const Part&>(em);
}

#endif
