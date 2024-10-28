#include <iostream>

#include "../include/Vector.h"

int main()
{
	Vector<int> my_vector;

	my_vector.push_back(2);

	std::cout << "Текущий вектор: " << my_vector << std::endl;

	return 0;
}
