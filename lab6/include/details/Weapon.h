#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class Weapon 
{
	public:
		std::string name;       
		double caliber;         
		int maxAmmo;            
		int currentAmmo;        
		double reloadTime;      
		double weight;          
		double effectiveRange;  
		int modifications;      

		Weapon(std::string n, double cal, int maxA, double reloadT, double wt, double effR, int mods) 
			: name(n), caliber(cal), maxAmmo(maxA), currentAmmo(maxA), 
			  reloadTime(reloadT), weight(wt), effectiveRange(effR), modifications(mods) {}

		virtual double reload() = 0;

		virtual int fire(double distance, int mode, int &hits) = 0;

		void displayCharacteristics() {
			std::cout << "Weapon: " << name << "\n"
					  << "Caliber: " << caliber << "mm"  
					  << " Max Ammo: " << maxAmmo << "\n"
					  << "Reload Time: " << reloadTime << " sec"
					  << " Weight: " << weight << " kg" 
					  << " Effective Range: " << effectiveRange << " m" 
					  << " Modifications: " << modifications << "\n";
		}

		virtual ~Weapon() = default;
};

#endif
