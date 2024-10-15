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

		void set_breaking(Part* part)
		{
			repair_cost += part->get_single_repair_cost();
			breaking_time += part->get_repair_time();
			breakages++;
		}

		void replacing_part(int index)
		{
			Part* old_part = parts[index];
			repair_cost += old_part->get_replacement_cost();
			breaking_time += 4;
			delete old_part;

			if (static_cast<Shaft*>(old_part))
				parts[index] = new Shaft();
			else if (static_cast<ElectricMotor*>(old_part))
				parts[index] = new ElectricMotor();
			else if (static_cast<ControlPanel*>(old_part))
				parts[index] = new ControlPanel();
			else if (static_cast<CuttingHead*>(old_part))
				parts[index] = new CuttingHead();
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
		{}

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

		void operating(int intensity, int hours)
		{
			for (int hour = 0; hour < hours; hour++)
			{
				for (int i = 0; i < amount_of_parts; i++)
				{
					parts[i]->working(intensity);
					if (parts[i]->breaking())
					{
						set_breaking(parts[i]);
						sum_breaking_time += parts[i]->get_repair_time();
						replacing_part(i);
					}
				}
			}
		}

		int get_repair_cost() const { return repair_cost; }
		
		int get_amount_of_breakages() const { return breakages; }

		int get_breaking_time() const { return breaking_time; }

		int get_sum_breaking_time() const { return sum_breaking_time; }
};

#endif
