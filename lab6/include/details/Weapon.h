#ifndef WEAPON_H
#define WEAPON_H

#include <cstring>
#include <cmath>

class Weapon 
{
	public:
		char* name;       
		double caliber;         
		int amount_of_rounds;            
		int current_ammo;        
		double reload_time;      
		int fire_mods;
		double weight;          
		double effective_range;  
		int accuracy;
		int modifications;
		double shot_hit_chance;

		Weapon(const char* n, double cal, int aor, double rt, int fm, double wt, double er, int acc, int mods) : caliber(cal), amount_of_rounds(aor), reload_time(rt), fire_mods(fm), weight(wt), effective_range(er), accuracy(acc), modifications(mods), current_ammo(0), shot_hit_chance(1.0) 
		{
			name = new char[strlen(n) + 1];
			strcpy(name, n);
		}

		virtual ~Weapon()
		{
			delete [] name;
		}

		virtual double reload() = 0;

		virtual int fire(double distance) = 0;

		double reload_ammo(int ammo)
		{
			if (ammo <= 0) return 0.0;

			int ammo_to_reload = ((ammo + current_ammo) > amount_of_rounds) ? (amount_of_rounds - current_ammo) : ammo;
			current_ammo += ammo_to_reload;
			
			return ammo_to_reload * reload_time;
		}

		double calculate_hit_chance(double distance) const
		{
			if (distance <= effective_range)
				return 100.0;

			double ratio = effective_range / distance;
			return (ratio > 0.0) ? (100.0 * std::exp(-3 * (1.0 - ratio))) : 0.0;
		}

		friend std::ostream &operator<<(std::ostream &os, const Weapon &w)
		{
			return os << "Оружие - " << w.name << std::endl << "{" << std::endl << "\tКалибр - " << w.caliber << "мм" << std::endl << "\tКоличество патронов - " << w.amount_of_rounds << std::endl << "\tКоличество режимов стрельбы - " << w.modifications << std::endl << "\tВремя перезарядки - " << w.reload_time << " секунд" << std::endl << "\tВес - " << w.weight << " кг" << std::endl << "\tДальность - " << w.effective_range << " метров" << std::endl << "\tТочность - " << w.accuracy << "%" << std::endl << "\tШанс попадания - " << w.shot_hit_chance << std::endl << "}" << std::endl; 
		}
};

#endif
