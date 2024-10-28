#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class Weapon 
{
	public:
		std::string name;       
		double caliber;         
		int amount_of_rounds;            
		int amount_of_shooting_modes;      
		int current_ammo;        
		double reloadTime;      
		double weight;          
		double effective_range;  

		Weapon(std::string n, double cal, int maxA, double reloadT, double wt, double effR, int mods) 
			: name(n), caliber(cal), amount_of_rounds(maxA), current_ammo(maxA), 
			  reloadTime(reloadT), weight(wt), effective_range(effR), amount_of_shooting_modes(mods) {}

		virtual double reload() = 0;

		virtual int fire(double distance, int mode, int &hits) = 0;

		void displayCharacteristics() {
			std::cout << "Оружие - " << name << std::endl << "{" << std::endl << "\tКалибр - " << caliber << "мм" << std::endl << "\tКоличество патронов - " << amount_of_rounds << std::endl << "\tКоличество режимов стрельбы - " << amount_of_shooting_modes << std::endl << "\tВремя перезарядки - " << reloadTime << " секунд" << std::endl << "\tВес - " << weight << " кг" << std::endl << "\tДальность - " << effective_range << " метров" << std::endl << "}" << std::endl; 
					  		}

		virtual ~Weapon() = default;
};

#endif
