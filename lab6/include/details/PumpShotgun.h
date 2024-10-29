#ifndef PUMP_SHOTGUN_H
#define PUMP_SHOTGUN_H

#include "Weapon.h"

class PumpShotgun : public Weapon
{
	public:
		/*
		 * Конструктор класса
		 *
		 */

		PumpShotgun() : Weapon
		(
			Constants::name_pump_shotgun, 
			Constants::caliber_shotgun,
			Constants::amount_of_rounds_shotgun,
			Constants::reload_time_shotgun,
			Constants::fire_mods_shotgun,
			Constants::weight_shotgun,
			Constants::effective_range_shotgun,
			Constants::accuracy_shotgun,
			Constants::amount_of_modifications_shotgun
		)
		{
			current_ammo = amount_of_rounds;
		}

		/*
		 * Перезарядка дробовика
		 *
		 * @return количество времени, затраченного на перезарядку
		 */

		double reload() override
		{
			return reload_ammo(amount_of_rounds);
		}

		/*
		 * Стрельба из дробовика
		 *
		 * @return возвращает 1 в случае попадния, иначе - 0 
		 */

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
