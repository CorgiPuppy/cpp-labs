#ifndef SINGLE_SHOT_RIFLE_H
#define SINGLE_SHOT_RIFLE_H

#include "Weapon.h"

class SingleShotRifle : public Weapon
{
	public:
		/*
		 * Конструктор класса
		 *
		 */

		SingleShotRifle() : Weapon
		(
			Constants::name_single_shot_rifle, 
			Constants::caliber_rifle,
			Constants::amount_of_rounds_rifle,
			Constants::reload_time_rifle,
			Constants::fire_mods_rifle,
			Constants::weight_rifle,
			Constants::effective_range_rifle,
			Constants::accuracy_rifle,
			Constants::amount_of_modifications_rifle
		)
		{
			current_ammo = amount_of_rounds;
		}

		/*
		 * Перезарядка винтовки
		 *
		 * @return количество времени, затраченного на перезарядку
		 */

		double reload() override
		{
			return reload_ammo(amount_of_rounds);
		}

		/*
		 * Стрельба из винтовки
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
