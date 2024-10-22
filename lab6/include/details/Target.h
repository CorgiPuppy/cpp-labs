#ifndef TARGET_H
#define TARGET_H

class Target
{
	public:
		virtual double getHitChance(double distance) const = 0;
		virtual void takeDamage(int hits) = 0;
		virtual bool isAvailable() const = 0;
		virtual double getSize() const = 0;
		virtual ~Target() = default;
};

#endif
