#ifndef SHOOTINGRANGE_H
#define SHOOTINGRANGE_H

#include "Weapon.h"

class ShootingRange
{
	private:
		double* targets;
		int target_count;
	
	public:
		/*
		 * Конструктор класса
		 *
		 */

		ShootingRange()
		{
			target_count = rand() % Constants::max_amount_of_targets + 1;
			targets = new double[target_count];
			for (int i = 0, dist = Constants::distance; i < target_count; i++, dist *= Constants::step_distance)
				targets[i] = dist;		
		}	

		/*
		 * Деструктор класса
		 *
		 * Освобождение памяти всех мишеней
		 */

		~ShootingRange()
		{
			delete[] targets;
		}

		/*
		 * Симуляция стрельбища
		 *
		 * @param weapon оружие
		 * @param sum_fire_rate суммарная величина темпа стрельбы
		 * @param sum_accuracy суммарная величина точности стрельбы
		 */

		void simulate(Weapon &weapon, double &sum_fire_rate, double &sum_accuracy)
		{
			std::cout << std::endl << "Тестирование оружия: " << weapon.name << std::endl;
			std::cout << weapon;

			for (int i = 0; i < target_count; i++)
			{
				double distance = targets[i];
				int hits = 0;
				int sum_shots = Constants::amount_of_shots;
				double sum_time = 0.0;

				for (int j = 0; j < sum_shots; j++)
				{
					if (weapon.current_ammo == 0)
						sum_time += weapon.reload();

					hits += weapon.fire(distance);
					sum_time += 1.0;
				}

				double accuracy = (double)hits / sum_shots * 100;
				double fire_rate = sum_shots / sum_time * Constants::one_minute;

				std::cout << std::endl << "Мишень №" << i + 1 << ":" << std::endl;
				std::cout << "\tДистанция - " << distance << " метров" << std::endl;
				std::cout << "\tПопадания - " << hits << " штук" << std::endl;
				std::cout << "\tТочность - " << accuracy << "%" << std::endl;
				std::cout << "\tТемп стрельбы - " << fire_rate << " выстрелов в минуту" << std::endl;
				
				sum_accuracy += accuracy;
				sum_fire_rate += fire_rate;
				weapon.shot_hit_chance = 1.0;
			}
		}
};

#endif
