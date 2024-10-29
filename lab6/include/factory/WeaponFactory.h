#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H

#include "../details/Pistol.h"
#include "../details/SingleShotRifle.h"
#include "../details/PumpShotgun.h"

class WeaponFactory
{
	public:
		enum WeaponType
		{
			PISTOL,
			SINGLE_SHOT_RIFLE,
			PUMP_SHOTGUN
		};

		static Weapon* createWeapon(WeaponType type)
		{
			switch (type)
			{
				case PISTOL:
					return new Pistol();
				
				case SINGLE_SHOT_RIFLE:
					return new SingleShotRifle();

				case PUMP_SHOTGUN:
					return new PumpShotgun();

				default:
					return nullptr;
			}
		}
};

#endif
