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
		Part() : replacement_cost(), single_repair_cost(), repair_time(), service_life(), deterioration_degree() {};

		void get_characteristic() const
		{
				
		}

		void breakdown_detection() 
		{
			if (service_life == 0)
			{
				std::cout << "Срок службы запчасти истёк" << std::endl;
				std::cout << "Степень изношенности: " << deteriorations_degree << std::endl;
			}
		}

		void working() 
		{
			
		}

};

#endif
