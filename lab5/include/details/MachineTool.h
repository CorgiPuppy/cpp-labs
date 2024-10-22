#ifndef MACHINETOOL_H
#define MACHINETOOL_H

#include "../factory/PartFactory.h"

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

		void set_breaking(Part* part, int &hours)
		{
			hours += Constants::replacement_hours;
			breaking_time += Constants::replacement_hours;
			repair_cost += part->get_replacement_cost();
			amount_of_part_replacements++;
		}

		void replacing_part(Part* part, int &hours)
		{
			hours += part->get_repair_time();
			breaking_time = part->get_repair_time();
			repair_cost += part->get_replacement_cost();
			breakages++;
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
		
		int operating(int intensity)
		{
			int hours = 0;

			for (int i = 0; i < Constants::amount_of_parts; i++)
			{
				parts[i]->working(intensity);

				if (parts[i]->breaking())
				{
					set_breaking(parts[i], hours);

					return hours;
				}
				else if (rand() % Constants::max_intensity < intensity)
				{
					replacing_part(parts[i], hours);

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
