#ifndef PARTSTRATEGY_H
#define PARTSTRATEGY_H

class PartStrategy
{
	public:
		virtual ~PartStrategy() {}

		virtual void working(int& deterioration_degree, int intensity, int service_life) = 0;

		virtual bool breaking(int deterioration_degree, int service_life) const = 0;
};

#endif
