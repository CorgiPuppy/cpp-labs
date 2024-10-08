#include "Swordsman.h"
#include "Mage.h"
#include "Shooter.h"

class Mercenary
{
	public:	
		void *character;
		int type;	
		
		Mercenary(void *c, int t) : character(c), type(t) {}	

		/*
		 * Получение характеристик определенного наемника
		 *
		 */
		 
		void get_mercenary_characteristic()
		{
			switch(type)
			{
				case(0):
					static_cast<Swordsman*>(character)->Swordsman::get_charaсteristic();
					break;

				case(1):
					static_cast<Mage*>(character)->Mage::get_charaсteristic();
					break;

				case(2):
					static_cast<Shooter*>(character)->Shooter::get_charaсteristic();
					break;
			}
		}
};
