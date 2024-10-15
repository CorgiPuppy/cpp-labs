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

		void set_breaking(Part* part)
		{
			repair_cost += part->get_single_repair_cost();
			breaking_time += part->get_repair_time();
			breakages++;
		}

	public:
		MachineTool() 
		:
			repair_cost(0),
			breaking_time(0),
			breakages(0),
			parts(nullptr),
			amount_of_parts(0)	
		{}

		~MachineTool() 
		{
			for (int i = 0; i < amount_of_parts; i++)
				delete parts[i];

			delete [] parts;
		}

		void add_part(Part* part)
		{
			Part** temp_parts = new Part*[amount_of_parts++];

			for (int i = 0; i < amount_of_parts; i++)
				temp_parts[i] = parts[i];

			temp_parts[amount_of_parts] = part;
			delete [] parts;
			parts = temp_parts;
			
			amount_of_parts++;
		}

		void operate(int intensity, int hours)
		{
			for (int hour = 0; hour < hours; hour++)
			{
				for (int i = 0; i < amount_of_parts; i++)
				{
					parts[i]->working(intensity);
					if (parts[i]->breaking())
						set_breaking(parts[i]);
				}
			}
		}

		int get_repair_cost() const { return repair_cost; }
		
		int get_amount_of_breakages() const { return breakages; }

		int get_breaking_time() const { return breaking_time; }
};

#endif
