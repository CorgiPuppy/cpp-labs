#include <iostream>
#include <string>

#include "../include/factory/WeaponFactory.h"
#include "../include/details/ShootingRange.h"

int main()
{
    srand((time(0)));

    Weapon* pistol = WeaponFactory::createWeapon(WeaponFactory::WeaponType::PISTOL);
    ShootingRange range;

    range.simulate(*pistol);

    delete pistol;

    return 0;
}

