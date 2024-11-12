#ifndef QUADRATIC_EQUATION_H
#define QUADRATIC_EQUATION_H

#include "Complex.h"

#include <algorithm>
#include <iterator>
#include <vector>
#include <set>

class QuadraticEquation
{
	private:
		Complex a, b, c;
		Complex root_1, root_2;
		
		/*
		 * Вычисление дискриминанта и корней квадратного уравнения
		 *
		 */

		void calculate_roots()
		{
	        Complex discriminant = b * b - Complex(4.0, 0.0) * a * c; 
            
			root_1 = (Complex(0.0, 0.0) - b + discriminant.sqrt()) / (Complex(2.0, 0.0) * a);
			root_2 = (Complex(0.0, 0.0) - b - discriminant.sqrt()) / (Complex(2.0, 0.0) * a);
		}

	public:
		/*
		 * Конструктор класса
		 *
		 * @param a коэффициент при x^2
		 * @param b коэффициент при x
		 * @param c свободный коэффициент
		 */

		QuadraticEquation
		(
			Complex a,
			Complex b,
			Complex c
		) :
			a(a),
			b(b),
			c(c)
		{
			calculate_roots();
		}

		/*
		 * Проверка на наличие такого же корня, что и заданный
		 *
		 * @param it заданное число
		 * @return возвращает true, если есть корень, иначе - false
		 */

		bool has_root(const Complex& it) const
		{
			/*
			const double epsilon = 1e-9;
			for (Complex& root : get_roots())
				if ((std::fabs(root.real - it.real) < epsilon) &&
                    (std::fabs(root.imag - it.imag) < epsilon))                   			return true;

			return false;
			*/
			std::vector<Complex> roots = get_roots();
			bool result = std::find_if(
								roots.begin(), roots.end(),
								[&it](const auto& root)
								{
									const double epsilon = 1e-9;
									return (std::fabs(root.real - it.real) < epsilon) &&
									       (std::fabs(root.real - it.real) < epsilon);
								}
							) != roots.end();
			return result;
		}
		
		/*
		 * Подсчёт количества корней, меньших по модуль заданного
		 *
		 * @param it заданное число для сравнения
		 * @return количество корней, удовлетворяющих условию
		 */

		int count_smaller_roots(const Complex& it) const
		{
			/*
			int count = 0;
			for (Complex& root : get_roots())
				if (root.abs() < it.abs())
					count++;

			return count;
			*/
			std::vector<Complex> roots = get_roots();	
			return std::count_if(
                       roots.begin(), roots.end(),
                       [&it](const Complex& root)
					   {
                           return std::fabs(root.real) < std::fabs(it.real);
                       }
                   );
			
		}
		
		static std::vector<Complex> get_unique_roots(const std::vector<QuadraticEquation>& equations)
		{
			std::set<Complex> unique_roots;

			for (const QuadraticEquation& equation : equations)
			{
				std::vector<Complex> roots = equation.get_roots();
				for (Complex root : roots)
					unique_roots.insert(root);
			}
			
			return std::vector<Complex>(unique_roots.begin(), unique_roots.end());
		}

		Complex sum_of_roots() const
		{
			return root_1 + root_2;
		}

		static void sort_equations_via_sum(std::vector<QuadraticEquation>& equations)
		{
			std::sort(
				equations.begin(), equations.end(),
				[](const QuadraticEquation& qe_1, const QuadraticEquation& qe_2)
				{
					return qe_1.sum_of_roots() < qe_2.sum_of_roots();
				}
			);
		}

		/*
		 * Геттер вектора корней
		 *
		 * @return возвращает вектора корней
		 */

		std::vector<Complex> get_roots() const { return {root_1, root_2}; };

		/*
		 * Геттер первого корня
		 *
		 * @return возвращает первый корень
		 */

		const Complex get_root_1() const { return root_1; }

		/*
		 * Геттер второго корня
		 *
		 * @return возвращает второй корень
		 */

		const Complex get_root_2() const { return root_2; }

		/*
		 * Вывод в поток характеристик уравнения
		 *
		 * @param os поток, в который записывается характеристика
		 * @param qe квадратное уравнение
		 *
		 * @return возвращает характеристику корня
		 */

		friend std::ostream& operator<<(std::ostream& os, const QuadraticEquation& qe)
		{
			os << std::endl << "\tУравнение: " << "(" << qe.a << ")" << "x^2 + " << "(" << qe.b << ")" << "x + " << "(" << qe.c << ") = 0" << std::endl;
			os << "\t\tКорень 1: " << qe.root_1 << std::endl;
			os << "\t\tКорень 2: " << qe.root_2;

			return os;
		}
};

#endif
