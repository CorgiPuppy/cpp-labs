#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <set>

#include "../include/QuadraticEquation.h"
#include "../include/Complex.h"

std::vector<Complex> get_unique_roots(const std::vector<QuadraticEquation>& equations) {
    std::set<Complex> unique_roots; 

    for (const auto& equation : equations) {
        unique_roots.insert(equation.get_root_1());
        unique_roots.insert(equation.get_root_2());
    }

    std::vector<Complex> roots_vector(unique_roots.begin(), unique_roots.end());
    return roots_vector;
}

int main()
{	
    int N;
    std::cout << "Введите число уравнений: ";
    std::cin >> N;

    std::vector<QuadraticEquation> equations;
    
    for (int i = 0; i < N; i++)
	{
        double a_r, a_i, b_r, b_i, c_r, c_i;
        std::cout << "Коэффициенты уравнения " << i + 1 << " (a, b, c) (реальная и мнимая части через пробел):\n";
        std::cin >> a_r >> a_i >> b_r >> b_i >> c_r >> c_i;

        Complex a(a_r, a_i);
        Complex b(b_r, b_i);
        Complex c(c_r, c_i);
        
        equations.emplace_back(a, b, c);
    }

	std::cout << "Корни уравнений:" << std::endl;
	std::copy(equations.begin(), equations.end(), std::ostream_iterator<QuadraticEquation>(std::cout, "\n"));

	double root_real, root_imag;
	std::cout << "Введите число для проверки наличия среди корней (реальная и мнимая части через пробел):" << std::endl;
	std::cin >> root_real >> root_imag;

	Complex user_root(root_real, root_imag);

	for (QuadraticEquation& equation : equations)
	{
		if (equation.has_root(user_root))
			std::cout << "Корень " << user_root << " есть в уравнении: " << equation << std::endl;
		else	
			std::cout << "Корня " << user_root << " нет в уравнении: " << equation << std::endl;
	}

	double root_real2, root_imag2;
	std::cout << "Введите число для сравнения с корнями уравнений (реальная и мнимая части через пробел):" << std::endl;
	std::cin >> root_real2 >> root_imag2;

	Complex smaller_root(root_real2, root_imag2);

	int count = 0;
	for (QuadraticEquation& equation : equations)
		count += equation.count_smaller_roots(smaller_root);

	std::cout << "Количество корней, меньших заданного - " << count << std::endl;

    std::vector<Complex> unique_roots = QuadraticEquation::get_unique_roots(equations);
    std::cout << "Уникальные корни:" << std::endl;
    for (Complex& root : unique_roots) {
        std::cout << root << std::endl;
    }
	
	QuadraticEquation::sort_equations_via_sum(equations);
	std::cout << "Сортировка уравнений по сумме корней уравнений:" << std::endl;
	std::copy(equations.begin(), equations.end(), std::ostream_iterator<QuadraticEquation>(std::cout, "\n"));

    return 0;
}
