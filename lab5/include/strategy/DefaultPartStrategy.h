#ifndef DEFAULTPARTSTRATEGY_H
#define DEFAULTPARTSTRATEGY_H

#include "PartStrategy.h"

class DefaultPartStrategy : public PartStrategy
{
	public:
		void working(int& deterioration_degree, int intensity, int service_life) override
		{
			deterioration_degree += intensity;
			if (deterioration_degree >= service_life)
				deterioration_degree = service_life;
		}

		bool breaking(int deterioration_degree, int service_life) const override
		{
			return deterioration_degree >= service_life;
		}
};

#endif
