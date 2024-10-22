#ifndef STATICTARGET_H
#define STATICTARGET_H

#include "Target.h"

class StaticTarget : public Target
{
	private:
		double distance;
		double size;
		int maxHits;
		int currentHits;

	public:
		StaticTarget(double dist, double sz, int maxH) 
			: distance(dist), size(sz), maxHits(maxH), currentHits(0) {}

		double getHitChance(double distance) const override
		{
			return std::max(0.0, 1.0 - (distance / 100.0));
		}

		void takeDamage(int hits) override
		{
			currentHits += hits;
		}

		bool isAvailable() const override
		{
			return currentHits < maxHits;
		}

		double getSize() const override
		{
			return size;
		}

		friend std::ostream& operator<<(std::ostream& os, const StaticTarget& target)
		{
			os << "StaticTarget { Distance: " << target.distance 
			   << " m, Size: " << target.size << " m², Hits: " << target.currentHits << "/" << target.maxHits << " }";
			return os;
		}
};

#endif
