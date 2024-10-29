#ifndef PISTOL_H
#define PISTOL_H

#include "Weapon.h"

class Pistol : public Weapon
{
	public:
		/*
		 * Конструктор класса
		 *
		 */

		Pistol() : Weapon
		(
			Constants::name_pistol, 
			Constants::caliber_pistol,
			Constants::amount_of_rounds_pistol,
			Constants::reload_time_pistol,
			Constants::fire_mods_pistol,
			Constants::weight_pistol,
			Constants::effective_range_pistol,
			Constants::accuracy_pistol,
			Constants::amount_of_modifications_pistol
		)
		{
			current_ammo = amount_of_rounds;
		}

		/*
		 * Перезарядка пистолета
		 *
		 * @return количество времени, затраченного на перезарядку
		 */

		double reload() override
		{
			return reload_ammo(amount_of_rounds);
		}

		/*
		 * Стрельба из пистолета
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
