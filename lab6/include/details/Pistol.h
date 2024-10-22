#ifndef PISTOL_H
#define PISTOL_H

#include "Weapon.h"

class Pistol : public Weapon
{
	private:
		double calculateHitChance(double distance) const
		{
			double ratio = distance / effectiveRange;
			return ratio < 1.0 ? 1.0 - ratio : 0.0;
		}

	public:
		Pistol() : Weapon("Pistol", 9.0, 15, 1.5, 1.2, 50, 2) {}

		double reload() override
		{
			currentAmmo = amount_of_rounds;
			return reloadTime;
		}

		int fire(double distance, int mode, int &hits) override
		{
			if (currentAmmo <= 0) return 0;
			--currentAmmo;
			double hitChance = calculateHitChance(distance);

			int hitCount = 0;
			if (mode == 1)
			{ 
				if ((static_cast<double>(rand()) / RAND_MAX) < hitChance)
					++hitCount;
			}
			else if (mode == 2)
			{
				int bulletsInBurst = (currentAmmo < 3) ? currentAmmo : 3;
				for (int i = 0; i < bulletsInBurst; ++i)
				{
					if ((static_cast<double>(rand()) / RAND_MAX) < hitChance)
						++hitCount;
				}

				currentAmmo -= bulletsInBurst;
			}

			hits += hitCount;

			return hitCount;
		}	
};

#endif
