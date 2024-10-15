#ifndef MACHINETOOL_H
#define MACHINETOOL_H

#include "Shaft.h"
#include "ElectricMotor.h"
#include "ControlPanel.h"
#include "CuttingHead.h"

class MachineTool 
{
	private:
		Part** parts;
		int amount_of_parts;
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
			breakages++;
		}

		void replacing_part(int index_part, int index_machine)
		{
			Part* old_part = parts[index_part];
			repair_cost += old_part->get_replacement_cost();
			breaking_time += Constants::replacement_hours;	
			amount_of_part_replacements++;
			delete old_part;

			if (static_cast<Shaft*>(old_part))
				parts[index_part] = new Shaft();
			else if (static_cast<ElectricMotor*>(old_part))
				parts[index_part] = new ElectricMotor();
			else if (static_cast<ControlPanel*>(old_part))
				parts[index_part] = new ControlPanel();
			else if (static_cast<CuttingHead*>(old_part))
				parts[index_part] = new CuttingHead();

			individual_breakages[index_machine]++;
		}

	public:
		MachineTool() 
		:
			repair_cost(0),
			breaking_time(0),
			breakages(0),
			parts(nullptr),
			amount_of_parts(0),
			amount_of_part_replacements(0),
			sum_breaking_time(0)
		{
			for (int i = 0; i < Constants::amount_of_machine_tools; i++)
				individual_breakages[i] = 0;
		}

		~MachineTool() 
		{
			for (int i = 0; i < amount_of_parts; i++)
				delete parts[i];

			delete [] parts;
		}

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

		void operating(int intensity, int index_machine)
		{
			for (int day = 0; day < Constants::days; day++)
			{
				for (int hour = 0; hour < Constants::hours; hour++)
				{
					for (int i = 0; i < amount_of_parts; i++)
					{
						parts[i]->working(intensity);
						if (parts[i]->breaking())
						{
							set_breaking(parts[i]);
							sum_breaking_time += parts[i]->get_repair_time();
							replacing_part(i, index_machine);
						}
					}
				}
			}
		}

		int get_repair_cost() const { return repair_cost; }
		
		int get_amount_of_breakages() const { return breakages; }

		int get_breaking_time() const { return breaking_time; }

		int get_sum_breaking_time() const { return sum_breaking_time; }
		
		int get_amount_of_part_replacements() const { return amount_of_part_replacements; }

		int get_individual_breakage(int index) const { return individual_breakages[index]; }
};

#endif
