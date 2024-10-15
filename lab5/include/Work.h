#ifndef WORK_H
#define WORK_H

#include "MachineTool.h"

class Work
{
	private:
		int sum_repair_cost = 0;
		int sum_amount_of_breakages = 0;
		int sum_breaking_time = 0;
		int max_sum_breaking_time = 0;

	public:
		void simulating()
		{
			for (int month = 0; month < 12; month++)
			{
				int amount_of_machine_tools = rand() % 10 + 1;

				for (int i = 0; i < amount_of_machine_tools; i++)
				{
					MachineTool machine;
					machine.add_part(new Shaft());
					machine.add_part(new ElectricMotor());
					machine.add_part(new ControlPanel());
					machine.add_part(new CuttingHead());

					int intensity = rand() % 100 + 1;

					machine.operating(intensity, 12);

					sum_repair_cost += machine.get_repair_cost();
					sum_amount_of_breakages += machine.get_amount_of_breakages();
					sum_breaking_time += machine.get_breaking_time();
					max_sum_breaking_time = (max_sum_breaking_time > machine.get_sum_breaking_time()) ? max_sum_breaking_time : machine.get_sum_breaking_time();
				}
			}
		}
		
		void get_work_characteristic()
		{
			std::cout << "Количество заменяемых запчастей - " << " запчастей" << std::endl;
			std::cout << "Стоимость ремонта каждого станка - " << " денег" << std::endl;
			std::cout << "Количество поломок всех станков - " << sum_amount_of_breakages << " поломок" << std::endl;
			std::cout << "Количество поломок каждого станка - " << " поломок" << std::endl;
			std::cout << "Суммарный простой станков - " << sum_breaking_time << " часов" << std::endl;
			std::cout << "Максимальный суммарный простой одного станка - " << max_sum_breaking_time << " часов" << std::endl;
		}
};

#endif
