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

		int get_power()
		{
			switch(type)
			{
				case(0):
					return static_cast<Swordsman*>(character)->get_power();

				case(1):
					return static_cast<Mage*>(character)->get_power();
				
				case(2):
					return static_cast<Shooter*>(character)->get_power();

				default:
					return 0;
			}
		}

		int get_durability()
		{
			switch(type)
			{
				case(0):
					return static_cast<Swordsman*>(character)->get_durability();

				case(1):
					return static_cast<Mage*>(character)->get_durability();
				
				case(2):
					return static_cast<Shooter*>(character)->get_durability();

				default:
					return 0;
			}
		}

		int get_distance()
		{
			switch(type)
			{
				case(0):
					return static_cast<Swordsman*>(character)->get_distance();

				case(1):
					return static_cast<Mage*>(character)->get_distance();
				
				case(2):
					return static_cast<Shooter*>(character)->get_distance();

				default:
					return 0;
			}
		}

		int get_cost()
		{
			switch(type)
			{
				case(0):
					return static_cast<Swordsman*>(character)->get_cost();

				case(1):
					return static_cast<Mage*>(character)->get_cost();
				
				case(2):
					return static_cast<Shooter*>(character)->get_cost();

				default:
					return 0;
			}
		}


};
