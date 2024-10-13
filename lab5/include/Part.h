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
			double replacement_cost,
			double single_repair_cost,
			double repair_time,
			double service_life,
			double deterioration_degree
		) : 
			this->replacement_cost(replacemt_cost), 
			this->single_repair_cost(single_repair_cost),
			this->repair_time(repair_time),
			this->service_life(service_life),
			this->deterioration_degree(deterioration_degree)
		{}

		virtual ~Part() {}

		virtual bool breaking() const = 0;

		virtual void working(double intensity) 
		{
			deterioration_degree += intensity;

			if (deterioration_degree >= service_life)
				deterioration_degree = service_life;
		}
		
		double get_replacement_cost() const { return replacement_cost; }

		double get_single_repair_cost() const { return repair_single_cost; {

		double get_repair_time() const { return repair_time; }

		double service_life() const { return service_life; }

		double deterioration_degree() const { return deterioration_degree; }

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
