#include <iostream>

#include "../include/factory/WeaponFactory.h"
#include "../include/details/ShootingRange.h"

int main()
{
    srand((time(0)));

    Weapon* pistol = WeaponFactory::createWeapon(WeaponFactory::PISTOL);
	Weapon* rifle = WeaponFactory::createWeapon(WeaponFactory::SINGLE_SHOT_RIFLE);
	Weapon* shotgun = WeaponFactory::createWeapon(WeaponFactory::PUMP_SHOTGUN);

    ShootingRange range;

	double sum_fire_rate = 0;
	double sum_accuracy = 0;
	int weapons_count = 3;

    range.simulate(*pistol, sum_fire_rate, sum_accuracy);
    range.simulate(*rifle, sum_fire_rate, sum_accuracy);
    range.simulate(*shotgun, sum_fire_rate, sum_accuracy);

    std::cout << std::endl << "Итоговая статистика:" << std::endl;
    std::cout << "Средняя точность: " << (sum_accuracy / weapons_count) << "%" << std::endl;
    std::cout << "Средний темп стрельбы: " << (sum_fire_rate / weapons_count) << " выстрелов в минуту" << std::endl;

    delete pistol;
    delete rifle;
    delete shotgun;

	return 0;
}

