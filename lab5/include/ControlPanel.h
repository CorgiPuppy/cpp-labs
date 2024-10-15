#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include "Part.h"

class ControlPanel : public Part
{
	public:
		ControlPanel() : Part
		(
			Constants::replacement_cost_control_panel, 
			Constants::repair_cost_control_panel,
			Constants::repair_time_control_panel,
			Constants::service_life_control_panel
		) {}

		bool breaking() const override
		{
			return deterioration_degree >= service_life;
		}

		friend std::ostream& operator << (std::ostream& os, const ControlPanel& cp);
};

std::ostream& operator << (std::ostream& os, const ControlPanel& cp)
{
	return os << "ControlPanel " << static_cast<const Part&>(cp);
}

#endif
