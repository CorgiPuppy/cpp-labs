#ifndef PART_H
#define PART_H

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
			service_life(service_life)
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

		friend std::ostream& operator << (std::ostream& os, const Part& part)
		{
			os << "Part " << std::endl;
			os << "{" << std::endl;
			os << "\treplacement_cost - " << part.replacement_cost << ";" << std::endl;
			os << "\tsingle_repair_cost - " << part.single_repair_cost << ";" << std::endl;
			os << "\trepair_time - " << part.repair_time << ";" << std::endl;
			os << "\tservice_life - " << part.service_life << ";" << std::endl;
			os << "\tdeterioration_degree - " << part.deterioration_degree << ";" << std::endl;
			os << "}" << std::endl;	
			return os;
		}
};

#endif
