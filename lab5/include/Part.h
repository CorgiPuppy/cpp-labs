#ifndef PART_H
#define PART_H

#include "Constants.h"

class Part
{
	protected:
		int replacement_cost;
		int single_repair_cost;
		int repair_time;
		int service_life;
		int deterioration_degree;

	public:
		Part
		(
			int replacement_cost,
			int single_repair_cost,
			int repair_time,
			int service_life
		) : 
			replacement_cost(replacement_cost), 
			single_repair_cost(single_repair_cost),
			repair_time(repair_time),
			service_life(service_life),
			deterioration_degree(0)
		{}

		virtual ~Part() {}

		virtual bool breaking() const = 0;

		virtual void working(int intensity) 
		{
			deterioration_degree += intensity;

			if (deterioration_degree >= service_life)
				deterioration_degree = service_life;
		}
		
		int get_replacement_cost() const { return replacement_cost; }

		int get_single_repair_cost() const { return single_repair_cost; }

		int get_repair_time() const { return repair_time; }

		int get_service_life() const { return service_life; }

		int get_deterioration_degree() const { return deterioration_degree; }

		friend std::ostream& operator<< (std::ostream& os, const Part& p);
};

std::ostream& operator<< (std::ostream& os, const Part& p)
{
	return os << std::endl << "Запчасть" << std::endl << "{" << std::endl << "\tСтоимость замены - " << p.replacement_cost << "," << std::endl << "\tСтоимость однократной починки - " << p.single_repair_cost << "," << std::endl << "\tВремя починки - " << p.repair_time << "," << std::endl << "\tСрок службы - " << p.service_life << std::endl << "}";
}

#endif
