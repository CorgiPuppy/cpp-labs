#ifndef GUILD_H
#define GUILD_H

#include <iostream>
#include <vector>

#include "Mercenary.h"

class Guild 
{
	private:
		Mercenary** mercenaries;
		int size_mercenaries;
		int capacity_mercenaries;

		Mercenary** group;
		int size_group;
		int capacity_group;

		/*
		 * Изменение размера вместимости наемников
		 *
		 */

		void resize_mercenaries_mercenaries() {
			capacity_mercenaries *= 2;
		   
			Mercenary** temp_mercenaries = new Mercenary*[capacity_mercenaries];
			for (int i = 0; i < size_mercenaries; i++) 
				temp_mercenaries[i] = mercenaries[i];
		  
			delete[] mercenaries;
			mercenaries = temp_mercenaries;
		}

		/*
		 * Изменение размера вместимости моей группы наемников
		 *
		 */

		void resize_mercenaries_group() 
		{
			capacity_group *= 2;

			Mercenary** temp_group = new Mercenary*[capacity_group];
			for (int i = 0; i < size_group; i++)
				temp_group[i] = group[i];
			
			delete[] group;
			group = temp_group;
		}

	public:
		Guild() : 
			size_mercenaries(0), 
			capacity_mercenaries(2),
			size_group(0),
			capacity_group(2) 
		{
			mercenaries = new Mercenary*[capacity_mercenaries];
			group = new Mercenary*[capacity_group];
		}

		~Guild() 
		{
			for (int i = 0; i < size_mercenaries; i++)
				delete mercenaries[i]; 

			delete[] mercenaries; 
			delete[] group; 
		}

		/*
		 * Добавление наемника
		 *
		 * @param mercenary наемник
		 */

		void set_add_mercenaries(Mercenary* mercenary) {
			if (size_mercenaries >= capacity_mercenaries) 
				resize_mercenaries_mercenaries();
			
			mercenaries[size_mercenaries++] = mercenary;
		}

		/*
		 * Получение случайного набора наемников
		 *
		 */


		void get_random_mercenaries() {
			set_add_mercenaries(new Mercenary(new Swordsman(true), 0)); // Танк
			set_add_mercenaries(new Mercenary(new Swordsman(false), 0)); // Обычный мечник
			set_add_mercenaries(new Mercenary(new Mage(1), 1)); // Маг средней дальности
			set_add_mercenaries(new Mercenary(new Mage(2), 1)); // Дальнобойный маг
			set_add_mercenaries(new Mercenary(new Shooter(true), 2)); // Средний стрелок

			for (int i = 0; i < Constants::capacity; i++) 
			{ 
				int type = rand() % 5;

				switch(type)
				{
					case(0):
						set_add_mercenaries(new Mercenary(new Swordsman(), 0));
					case(1):
						set_add_mercenaries(new Mercenary(new Swordsman(false), 0));
				
					case(2):
						set_add_mercenaries(new Mercenary(new Mage(1), 1));

					case(3):
						set_add_mercenaries(new Mercenary(new Mage(2), 1));

					case(4):
						set_add_mercenaries(new Mercenary(new Shooter(true), 2));
				}
			}
		}

		/*
		 * Добавление наемника в мою группу
		 *
		 * @param mercenary наемник
		 */

		void set_add_mercenaries_group(Mercenary* mercenary) {
			if (size_group >= capacity_group)
				resize_mercenaries_group();

			group[size_group++] = mercenary;
		}

		/*
		 * Отображение списка наемников
		 *
		 */

		void get_show_mercenaries() const { 
			for (int i = 0; i < size_mercenaries; i++) 
				mercenaries[i]->get_mercenary_characteristic();
		}

		/*
		 * Отображение списка моей группы наемников
		 *
		 */

		void get_show_group() const {
			for (int i = 0; i < size_group; i++)
				group[i]->get_mercenary_characteristic();
		}

		/*
		 * Составление собственной группы наемников
		 *
		 */

		void set_group() 
		{
			int choice = 12345;
			while (choice != 3)
			{
				std::cout << "----------------------------------------------------" << std::endl;
				std::cout << std::endl << "\tВыберите число:" << std::endl;
				std::cout << "\t\t1. Добавить наемника." << std::endl;
				std::cout << "\t\t2. Показать группу." << std::endl;
				std::cout << "\t\t3. Выход." << std::endl << std::endl;
				std::cout << "----------------------------------------------------" << std::endl;
				std::cin >> choice;

				if (choice == 1)
				{
					int counter_mercenary;
					std::cout << "Номер наемника в столбце: ";
					std::cin >> counter_mercenary;

					if (counter_mercenary > 0 && counter_mercenary <= size_mercenaries) 	{
						set_add_mercenaries_group(mercenaries[counter_mercenary - 1]);
						std::cout << "Наемник добавлен" << std::endl;
					}

					set_group();
				}
				else if (choice == 2)
				{
					std::cout << std::endl << "Группа:" << std::endl;
					get_show_group();
					set_group();
				} 
				else if (choice == 3) 
						break;
			}
		}
	
		/*
		 * Получение идеальной группы наемников
		 *
		 */
	 
		void get_ideal_group() 
		{
			std::vector<Mercenary*> ideal_group; 

			int max_cost; 
			std::cout << "Введите, сколько у вас денег: ";
			std::cin >> max_cost;

			int total_power = 0; 
			int total_durability = 0; 
			int total_cost = 0; 
			int near_distance_count = 0; 
			int mid_distance_count = 0;

			for (int i = 0; i < size_mercenaries; i++) 
			{
				Mercenary* mercenary = mercenaries[i];

				int current_power = 0;
				int current_durability = 0;
				int current_distance = 0;
				int current_cost = 0;

				switch(mercenary->type) 
				{
					case 0: 
						current_power = static_cast<Swordsman*>(mercenary->character)->get_power();
						current_durability = static_cast<Swordsman*>(mercenary->character)->get_durability();
						current_distance = static_cast<Swordsman*>(mercenary->character)->get_distance();
						current_cost = static_cast<Swordsman*>(mercenary->character)->get_cost();
						break;

					case 1: 
						current_power = static_cast<Mage*>(mercenary->character)->get_power();
						current_durability = static_cast<Mage*>(mercenary->character)->get_durability();
						current_distance = static_cast<Mage*>(mercenary->character)->get_distance();
						current_cost = static_cast<Mage*>(mercenary->character)->get_cost();
						break;

					case 2: 
						current_power = static_cast<Shooter*>(mercenary->character)->get_power();
						current_durability = static_cast<Shooter*>(mercenary->character)->get_durability();
						current_distance = static_cast<Shooter*>(mercenary->character)->get_distance();
						current_cost = static_cast<Shooter*>(mercenary->character)->get_cost();
						break;
				}

				if (total_cost + current_cost <= max_cost) 
				{
					ideal_group.push_back(mercenary);
					total_power += current_power;
					total_durability += current_durability;
					total_cost += current_cost;

					if (current_distance == 1)
						near_distance_count++;
					
					if (current_distance == 2)
						mid_distance_count++;
				}

				if (ideal_group.size() >= 5 &&
					total_durability >= 0.5 * total_power &&
					near_distance_count >= 1 &&
					mid_distance_count >= 1) 
						break;
			}

			if (ideal_group.size() >= 5) 
			{
				std::cout << "Идеальная группа:" << std::endl;
				
				for (Mercenary* mercenary : ideal_group)
					mercenary->get_mercenary_characteristic();
			} 
			else
				std::cout << "Не удалось сформировать идеальную группу." << std::endl;
		}	
};

#endif // GUILD_H	
