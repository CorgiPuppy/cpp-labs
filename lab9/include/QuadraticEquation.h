#ifndef QUADRATIC_EQUATION_H
#define QUADRATIC_EQUATION_H

#include "Complex.h"

#include <algorithm>
#include <iterator>
#include <vector>

class QuadraticEquation
{
	private:
		Complex a, b, c;
		Complex root_1, root_2;

		void calculate_roots()
		{
	        Complex discriminant = b * b - Complex(4.0, 0.0) * a * c; 
            
			root_1 = (Complex(0.0, 0.0) - b + discriminant.sqrt()) / (Complex(2.0, 0.0) * a);
			root_2 = (Complex(0.0, 0.0) - b - discriminant.sqrt()) / (Complex(2.0, 0.0) * a);
		}

	public:
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

		bool has_root(const Complex& it) const
		{
			if (std::find_if(
					get_roots().begin(), get_roots().end(),
					[&it](const Complex& root)
					{ 
						const double epsilon = 1e-9;	
						return ((root.real - it.real) < epsilon) && ((root.imag - it.imag) < epsilon);
					}
				) != get_roots().end())
				return true;
			return false;
		}

		int count_smaller_roots(const Complex& it) const
		{
			return std::count_if(
                       get_roots().begin(), get_roots().end(),
                       [&it](const Complex& root)
					   {
                           return std::fabs(root.real) < std::fabs(it.real);
                       }
                   );
		}
	
		std::vector<Complex> get_roots() const { return {root_1, root_2}; };

		const Complex get_root_1() const { return root_1; }

		const Complex get_root_2() const { return root_2; }

		friend std::ostream& operator<<(std::ostream& os, const QuadraticEquation& qe)
		{
			os << std::endl << "\tУравнение: " << "(" << qe.a << ")" << "x^2 + " << "(" << qe.b << ")" << "x + " << "(" << qe.c << ") = 0" << std::endl;
			os << "\t\tКорень 1: " << qe.root_1 << std::endl;
			os << "\t\tКорень 2: " << qe.root_2;

			return os;
		}
};

#endif
