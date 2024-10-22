#ifndef TARGET_H
#define TARGET_H

class Target
{
	public:
		virtual double get_hit_chance(double distance) const = 0;
		virtual void take_damage(int hits) = 0;
		virtual bool availability() const = 0;
		virtual double get_size() const = 0;
		virtual ~Target() = default;
};

#endif
