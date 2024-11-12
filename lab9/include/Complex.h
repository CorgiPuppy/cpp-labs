#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>

class Complex
{
	public:
		double real;
		double imag;

	public:
		Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

		Complex operator+(const Complex& second)
		{
			return Complex(real + second.real, imag + second.imag);
		}

		Complex operator-(const Complex& second)
		{
			return Complex(real - second.real, imag - second.imag);
		}

		Complex operator*(const Complex& second)
		{
			return Complex(real * second.real - imag * second.imag,
                           real * second.imag + imag * second.real);
        }

		Complex operator/(const Complex& second)
		{
			double denominator = (second.real * second.real + second.imag * second.imag);	

			return Complex((real * second.real + imag * second.imag) / denominator,
                           (imag * second.real - real * second.imag) / denominator);
		}

		Complex sqrt()
		{
			double r = std::sqrt(std::sqrt(real * real + imag * imag));
			double theta = 0.5 * std::atan2(imag, real);
			return Complex(r * std::cos(theta), r * std::sin(theta));
		}

		double abs() const
		{
			return std::sqrt(real * real + imag * imag);
		}

		bool operator==(const Complex& second) const
		{
			const double epsilon = 1e-9;
			return ((real - second.real) < epsilon) && ((imag - second.imag) < epsilon);
		}

		bool operator<(const Complex& second) const
		{
			return ((real < second.real) && (imag < second.imag));
		}

		friend std::ostream& operator<<(std::ostream& os, const Complex& c)
		{
			if (c.imag >= 0)
				os << c.real << " + " << c.imag << "i";
			else
				os << c.real << " - " << -c.imag << "i";
			
			return os;
		}
};

#endif
