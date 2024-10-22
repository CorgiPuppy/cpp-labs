#ifndef WEAPONFACTORY_H
#define WEAPONFACTORY_H

#include "../details/Pistol.h"

class WeaponFactory
{
	public:
		enum class WeaponType {	PISTOL };

		static Weapon* createWeapon(WeaponType type)
		{
			switch (type)
			{
				case WeaponType::PISTOL:
					return new Pistol();

				default:
					return nullptr;
			}
		}
};

#endif
