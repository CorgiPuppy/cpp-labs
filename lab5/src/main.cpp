#include <iostream>

#include "../include/Work.h"

int main()
{
	srand(time(nullptr));

	Work work;
	work.simulating();
	work.get_work_characteristic();

	return 0;
}	

