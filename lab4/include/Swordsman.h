#include "Constants.h"

class Swordsman
{
	private:
		int power;
		int durability;
		int distance;
		int cost;
	
	public:
		Swordsman() :
			power(Constants::power_swordsman), 
			durability(Constants::durability_swordsman),
			distance(Constants::distance[0]),
			cost(Constants::cost_1 + (rand() % (Constants::cost_2 - Constants::cost_1 + 1)))	
		{}

		/*
		 * Получение характеристик мечника
		 *
		 */

		void get_charaсteristic() {
			std::cout << "\t\tМечник:" << std::endl;
			std::cout << "\t\t\tСила - " << power << ";" << std::endl;
			std::cout << "\t\t\tСтойкость - " << durability << ";" << std::endl;
			std::cout << "\t\t\tДистанция - " << distance << ";" << std::endl;
			std::cout << "\t\t\tСтоимость - " << cost << ";" << std::endl;
		}
		
		/*
		 * Получение силы мечника
		 *
		 * @return возвращает силу мечника
		 */

		int get_power(void) { return this->power; }

		/*
		 * Получение стойкости мечника
		 *
		 * @return возвращает стойкость мечника
		 */

		int get_durability(void) { return this->durability; }

		/*
		 * Получение дистанции мечника
		 *
		 * @return возвращает дистанцию мечника
		 */

		int get_distance(void) { return this->distance; }

		/*
		 * Получение стоимость мечника
		 *
		 * @return возвращает стоимость мечника
		 */

		int get_cost(void) { return this->cost; }
};
