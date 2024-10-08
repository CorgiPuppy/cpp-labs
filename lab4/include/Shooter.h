#include "Constants.h"

class Shooter 
{
	private:
		int power;
		int durability;
		int distance;
		int cost;

	public:
		Shooter() :
			power(Constants::power_shooter),
			durability(Constants::durability_shooter),
			distance(Constants::distance[1] + (rand() % (Constants::distance[2] - Constants::distance[1] + 1))),
			cost(Constants::cost_1 + (rand() % (Constants::cost_2 - Constants::cost_1 + 1)))
			{}

		/*
		 * Получение характеристик стрелка
		 *
		 */

		void get_charaсteristic()
		{
			std::cout << "\t\tСтрелок:" << std::endl;
			std::cout << "\t\t\tСила - " << power << ";" << std::endl;
			std::cout << "\t\t\tСтойкость - " << durability << ";" << std::endl;
			std::cout << "\t\t\tДистанция - " << distance << ";" << std::endl;
			std::cout << "\t\t\tСтоимость - " << cost << ";" << std::endl;
		}
		
		/*
		 * Получение силы стрелка
		 *
		 * @return возвращает силу стрелка
		 */

		int get_power(void) { return this->power; }

		/*
		 * Получение стойкости стрелка
		 *
		 * @return возвращает стойкость стрелка
		 */

		int get_durability(void) { return this->durability; }

		/*
		 * Получение дистанции стрелка
		 *
		 * @return возвращает дистанцию стрелка
		 */

		int get_distance(void) { return this->distance; }

		/*
		 * Получение стоимость стрелка
		 *
		 * @return возвращает стоимость стрелка
		 */

		int get_cost(void) { return this->cost; }
};
