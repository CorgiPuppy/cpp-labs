#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include "Part.h"

class ControlPanel : public Part
{
	public:
		ControlPanel() : Part(500, 100, 1, 200) {}

		bool breaking() const override
		{
			return deterioration_degree >= service_life;
		}

		friend std::ostream& operator << (std::ostream& os, const ControlPanel& controlpanel)
		{
			os << "ControlPanel " << static_cast<const Part&>(controlpanel);
			return os;
		}
};

#endif
