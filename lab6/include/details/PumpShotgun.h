#ifndef PUMP_SHOTGUN_H
#define PUMP_SHOTGUN_H

#include "Weapon.h"

class PumpShotgun : public Weapon
{
	public:
		PumpShotgun() : Weapon("Помповый дробовик", 12.0, 8, 0.5, 1, 3.5, 30, 70, 1)
		{
			current_ammo = amount_of_rounds;
		}

		double reload() override
		{
			return reload_ammo(amount_of_rounds);
		}

		int fire(double distance) override
		{
			if (current_ammo <= 0) return 0;
			current_ammo--;

			double hit_chance = calculate_hit_chance(distance) * shot_hit_chance;
			shot_hit_chance *= 0.95;

			return (rand() % 100) < hit_chance ? 1 : 0;
		}	
};

#endif
