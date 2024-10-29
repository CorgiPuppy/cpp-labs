#ifndef SINGLE_SHOT_RIFLE_H
#define SINGLE_SHOT_RIFLE_H

#include "Weapon.h"

class SingleShotRifle : public Weapon
{
	public:
		SingleShotRifle() : Weapon("Однозарядная винтовка", 7.62, 1, 2.5, 1, 4.0, 800, 90, 3)
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
