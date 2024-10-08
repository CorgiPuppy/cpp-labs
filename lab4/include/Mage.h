#include "Constants.h"

class Mage 
{
	private:	
		int power;
		int durability;
		int distance;
		int cost;
	
	public:
		Mage(int type = 0) {
			switch(type)
			{
				case(1):
					power = Constants::power_mid_range_mage; 
					durability = Constants::durability_mage; 
					distance = Constants::distance[1]; 

				case(2):
					power = Constants::power_long_range_mage; 
					durability = Constants::durability_mage; 
					distance = Constants::distance[2]; 

				case(3):
					power = Constants::power_mage; 
					durability = Constants::durability_mage; 
					distance = Constants::distance[rand() % 3]; 
			}

			cost = Constants::cost_1 + (rand() % (Constants::cost_2 - Constants::cost_1 + 1));
		}	
		
		/*
		 * Получение характеристик мага
		 *
		 */

		void get_charaсteristic()
		{
			std::cout << "\t\tМаг:" << std::endl;
			std::cout << "\t\t\tСила - " << power << ";" << std::endl;
			std::cout << "\t\t\tСтойкость - " << durability << ";" << std::endl;
			std::cout << "\t\t\tДистанция - " << distance << ";" << std::endl;
			std::cout << "\t\t\tСтоимость - " << cost << ";" << std::endl;
		}
		
		/*
		 * Получение силы мага
		 *
		 * @return возвращает силу мага
		 */

		int get_power(void) { return this->power; }

		/*
		 * Получение стойкости мага
		 *
		 * @return возвращает стойкость мага
		 */

		int get_durability(void) { return this->durability; }

		/*
		 * Получение дистанции мага
		 *
		 * @return возвращает дистанцию мага
		 */

		int get_distance(void) { return this->distance; }

		/*
		 * Получение стоимость мага
		 *
		 * @return возвращает стоимость мага
		 */

		int get_cost(void) { return this->cost; }
};
