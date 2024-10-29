#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants
{
	const char* name_pistol = "Пистолет";
	const double caliber_pistol = 9.0;
	const int amount_of_rounds_pistol = 20;
	const double reload_time_pistol = 1.5;
	const int fire_mods_pistol = 1;
	const double weight_pistol = 2.1;
	const double effective_range_pistol = 30;
	const int accuracy_pistol = 75;
	const int amount_of_modifications_pistol = 3;

	const char* name_single_shot_rifle = "Однозарядная винтовка";
	const double caliber_rifle = 6.4;
	const int amount_of_rounds_rifle = 1;
	const double reload_time_rifle = 3.5;
	const int fire_mods_rifle = 1;
	const double weight_rifle = 5.0;
	const double effective_range_rifle = 600;
	const int accuracy_rifle = 95;
	const int amount_of_modifications_rifle = 2;

	const char* name_pump_shotgun = "Помповый дробовик";
	const double caliber_shotgun = 15.0;
	const int amount_of_rounds_shotgun = 6;
	const double reload_time_shotgun = 1.0;
	const int fire_mods_shotgun = 1;
	const double weight_shotgun = 3.0;
	const double effective_range_shotgun = 20;
	const int accuracy_shotgun = 60;
	const int amount_of_modifications_shotgun = 1;
}

#endif
