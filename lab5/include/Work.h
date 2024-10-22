#ifndef WORK_H
#define WORK_H

#include "MachineTool.h"

class Work
{
	private:	
		MachineTool* machines;
		int sum_repair_cost;
		int sum_amount_of_breakages;
		int sum_breaking_time;
		int max_sum_breaking_time;
		int sum_amount_of_part_replacements;
		int* sum_repair_cost_per_machine;
		int* breakages_per_machine; 

	public:
		Work()
		:
			sum_repair_cost(0),
			sum_amount_of_breakages(0),
			sum_breaking_time(0),
			max_sum_breaking_time(0),
			sum_amount_of_part_replacements(0)
		{
			MachineTool* machines = new MachineTool[Constants::amount_of_machine_tools];
			int* sum_repair_cost_per_machine = new int[Constants::amount_of_machine_tools]{0};
			int* breakages_per_machine = new int[Constants::amount_of_machine_tools]{0}; 
		}
		
		~Work()
		{
			delete [] machines;
			delete [] sum_repair_cost_per_machine;
			delete [] breakages_per_machine;
		}

		void simulating()
		{	
			int hours = Constants::hours * Constants::days * Constants::months;

			while (hours > 0)
			{
				int intensity = rand() % Constants::max_intensity + 1;

				for (int i = 0; i < Constants::amount_of_machine_tools; i++)
					hours -= machines[i].operating(intensity);
			}

			for (int i = 0; i < Constants::amount_of_machine_tools; i++)
			{
				sum_repair_cost += machines->get_repair_cost();
				sum_amount_of_breakages += machines->get_amount_of_breakages();
				sum_breaking_time += machines->get_breaking_time();
				max_sum_breaking_time = (max_sum_breaking_time > machines->get_sum_breaking_time()) ? max_sum_breaking_time : machines->get_sum_breaking_time();
				sum_amount_of_part_replacements += machines->get_amount_of_part_replacements();
				sum_repair_cost_per_machine[i] += machines->get_repair_cost();
				breakages_per_machine[i] += machines->get_individual_breakage(i);	

				//print_parts(machines);
			}
		}
		
		void get_work_characteristic()
		{
			std::cout << "Количество заменяемых запчастей - " << sum_amount_of_part_replacements << " запчастей" << std::endl;

			std::cout << "Стоимость ремонта каждого станка:" << std::endl;
			for (int i = 0; i < Constants::amount_of_machine_tools; i++)
				std::cout << "\tСтанок " << i + 1 << " - " << sum_repair_cost_per_machine[i] << " денег" << std::endl;
			
			std::cout << "Количество поломок каждого станка:" << std::endl;
			for (int i = 0; i < Constants::amount_of_machine_tools; i++)
				std::cout << "\tСтанок " << i + 1 << " - " << breakages_per_machine[i] << " поломок" << std::endl;

			std::cout << "Количество поломок всех станков - " << sum_amount_of_breakages << " поломок" << std::endl;

			std::cout << "Суммарный простой станков - " << sum_breaking_time << " часов" << std::endl;

			std::cout << "Максимальный суммарный простой одного станка - " << max_sum_breaking_time << " часов" << std::endl;
		}
};

#endif
