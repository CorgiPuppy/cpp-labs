#ifndef STATICTARGET_H
#define STATICTARGET_H

#include "Target.h"

class StaticTarget : public Target
{
	private:
		double distance;
		double size;
		int max_hits;
		int current_hits;

	public:
		StaticTarget(double dist, double sz, int maxH) 
			: distance(dist), size(sz), max_hits(maxH), current_hits(0) {}

		double get_hit_chance(double distance) const override
		{
			return (distance / 100.0) < 1.0 ? (1.0 - (distance / 100.0)) : 0.0;
		}

		void take_damage(int hits) override
		{
			current_hits += hits;
		}

		bool availability() const override
		{
			return current_hits < max_hits;
		}

		double get_size() const override
		{
			return size;
		}

		friend std::ostream& operator<<(std::ostream& os, const StaticTarget& target)
		{
			os << "Цель" << std::endl << "{" << std::endl << "\tДальность: " << target.distance 
			   << " метров" << std::endl << "\tРазмер: " << target.size << " м^2" << std::endl << "\tКоличество попаданий - " << target.current_hits << "/" << target.max_hits << std::endl << "}";
			return os;
		}
};

#endif
