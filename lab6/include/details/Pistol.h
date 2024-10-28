#ifndef PISTOL_H
#define PISTOL_H

#include "Weapon.h"

class Pistol : public Weapon
{
	private:
		double calculate_hit_chance(double distance, double visibility, double movement) const
		{
			double ratio = distance / effective_range;
			double base_hit_chance = ratio < 1.0 ? (1.0 - ratio) : 0.0;
			base_hit_chance *= visibility;
			base_hit_chance *= (1.0 - movement);
			
			if (base_hit_chance < 0.0)
				base_hit_chance = 0.0;
			else if (base_hit_chance > 1.0)
				base_hit_chance = 1.0;

			return base_hit_chance;
		}

	public:
		Pistol() : Weapon("Pistol", 9.0, 15, 1.5, 1.2, 50, 2) {}

		double reload() override
		{
			current_ammo = amount_of_rounds;
			return reloadTime;
		}

		int fire(double distance, int mode, int &hits) override
		{
			if (current_ammo <= 0) return 0;

			double visibility = ((double) rand() / (RAND_MAX)) + 1;
			double movement = ((double) rand() / (RAND_MAX)) + 1;

			int hit_count = 0;

			double hit_chance = calculate_hit_chance(distance, visibility, movement);

			if (mode == 1)
			{ 
				if ((static_cast<double>(rand()) / RAND_MAX) < hit_chance)
					hit_count++;

				current_ammo--;
			}
			else if (mode == 2)
			{
				int bullets_in_flash = (current_ammo < 3) ? current_ammo : 3;
				for (int i = 0; i < bullets_in_flash; i++)
				{
					if ((static_cast<double>(rand()) / RAND_MAX) < hit_chance)
						hit_count++;
				}

				current_ammo -= bullets_in_flash;
			}

			hits += hit_count;

			return hit_count;
		}	
};

#endif
