#ifndef QUADRATIC_EQUATION_H
#define QUADRATIC_EQUATION_H

#include "Complex.h"

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

		std::vector<Complex> get_roots() const
		{
			return {root_1, root_2};
		}

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
