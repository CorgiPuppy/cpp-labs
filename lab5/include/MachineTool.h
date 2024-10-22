#ifndef MACHINETOOL_H
#define MACHINETOOL_H

#include "PartFactory.h"

class MachineTool 
{
	private:
		Part** parts;
		int breaking_time;
		int repair_cost;
		int breakages;
		int amount_of_part_replacements;
		int sum_breaking_time;
		int individual_breakages[Constants::amount_of_machine_tools];

		void set_breaking(Part* part)
		{
			repair_cost += part->get_single_repair_cost();
			breaking_time += part->get_repair_time();
		}

		void replacing_part(int index_part, int index_machine)
		{
			Part* old_part = parts[index_part];
			repair_cost += old_part->get_replacement_cost();
			breaking_time += Constants::replacement_hours;	
			amount_of_part_replacements++;

			individual_breakages[index_machine]++;

			delete old_part;

			switch (index_part)
			{
				case 0: 
					parts[index_part] = new Shaft();
					break;
				
				case 1:
					parts[index_part] = new ElectricMotor();
					break;

				case 2:
					parts[index_part] = new ControlPanel();
					break;

				case 3:
					parts[index_part] = new CuttingHead();
					break;
			}
		}

	public:
		MachineTool() 
		:
			repair_cost(0),
			breaking_time(0),
			breakages(0),
			amount_of_part_replacements(0),
			sum_breaking_time(0)
		{
			parts = new Part*[4];
			parts[0] = PartFactory::createPart("Shaft");
			parts[1] = PartFactory::createPart("ElectricMotor");
			parts[2] = PartFactory::createPart("ControlPanel");
			parts[3] = PartFactory::createPart("CuttingHead");

			for (int i = 0; i < Constants::amount_of_machine_tools; i++)
				individual_breakages[i] = 0;
		}

		~MachineTool() 
		{
			for (int i = 0; i < Constants::amount_of_parts; i++)
				delete parts[i];

			delete [] parts;
		}
/*
		void add_part(Part* part)
		{
			Part** temp_parts = new Part*[amount_of_parts + 1];

			for (int i = 0; i < amount_of_parts; i++)
				temp_parts[i] = parts[i];

			temp_parts[amount_of_parts] = part;
			delete [] parts;
			parts = temp_parts;
			
			amount_of_parts++;
		}
*/
		int operating(int intensity)
		{
			int hours = 0;

			for (int i = 0; i < Constants::amount_of_parts; i++)
			{
				parts[i]->working(intensity);

				if (parts[i]->breaking())
				{
					hours += Constants::replacement_hours;
					breaking_time += Constants::replacement_hours;
					repair_cost += parts[i]->get_replacement_cost();
					amount_of_part_replacements++;

					return hours;
				}
				else if (rand() % 100 < 5)
				{
					hours += parts[i]->get_repair_time();
					breaking_time = parts[i]->get_repair_time();
					repair_cost += parts[i]->get_replacement_cost();
					breakages++;

					return hours;
				}
			}
			
			return 1;
		}

		int get_repair_cost() const { return repair_cost; }
		
		int get_amount_of_breakages() const { return breakages; }

		int get_breaking_time() const { return breaking_time; }
		
		int get_amount_of_part_replacements() const { return amount_of_part_replacements; }

		int get_individual_breakage(int index) const { return individual_breakages[index]; }

		friend void print_parts(MachineTool& mt);
};

void print_parts(MachineTool& mt)
{
	std::cout << std::endl << "Запчасти в станке:" << std::endl;

	for (int i = 0; i < Constants::amount_of_parts; i++)
		std::cout << *mt.parts[i] << std::endl; 
}

#endif
