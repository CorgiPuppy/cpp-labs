#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>

class Complex
{
	public:
		double real;
		double imag;

	public:
		/*
		 * Конструктор класса
		 *
		 * @param r вещественная часть
		 * @param i мнимая часть
		 */

		Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

		/*
		 * Перегруженный оператор +
		 *
		 * @param second второе число
		 *
		 * @return возвращает сумму чисел
		 */

		Complex operator+(const Complex& second) const
		{
			return Complex(real + second.real, imag + second.imag);
		}

		/*
		 * Перегруженный оператор -
		 *
		 * @param second второе число
		 *
		 * @return возвращает разность чисел
		 */

		Complex operator-(const Complex& second) const
		{
			return Complex(real - second.real, imag - second.imag);
		}

		/*
		 * Перегруженный оператор *
		 *
		 * @param second второе число
		 *
		 * @return возвращает произведение чисел
		 */

		Complex operator*(const Complex& second) const
		{
			return Complex(real * second.real - imag * second.imag,
                           real * second.imag + imag * second.real);
        }

		/*
		 * Перегруженный оператор /
		 *
		 * @param second второе число
		 *
		 * @return возвращает частное чисел
		 */

		Complex operator/(const Complex& second) const
		{
			double denominator = (second.real * second.real + second.imag * second.imag);	

			return Complex((real * second.real + imag * second.imag) / denominator,
                           (imag * second.real - real * second.imag) / denominator);
		}

		/*
		 * Расчёт извелечения корня комплексного числа
		 *
		 * @return возвращает корень комплексного числа 
		 */

		Complex sqrt()
		{
			double r = std::sqrt(std::sqrt(real * real + imag * imag));
			double phi = 0.5 * std::atan2(imag, real);
			return Complex(r * std::cos(phi), r * std::sin(phi));
		}

		/*
		 * Расчёт модуля комплексного числа
		 *
		 * @return возвращает модуль комплексного числа
		 */

		double abs() const
		{
			return std::sqrt(real * real + imag * imag);
		}

		/*
		 * Перегруженный оператор ==
		 *
		 * @param second второе число
		 *
		 * @return возвращает true, если числа равны, иначе - false
		 */

		bool operator==(const Complex& second) const
		{
			const double epsilon = 1e-9;
			return ((real - second.real) < epsilon) && ((imag - second.imag) < epsilon);
		}

		/*
		 * Перегруженный оператор <
		 *
		 * @param second второе число
		 *
		 * @return возвращает true, если число меньше заданного, иначе - false
		 */

		bool operator<(const Complex& second) const
		{
			return ((real < second.real) && (imag < second.imag));
		}

		/*
		 * Перегруженная функция вывода в поток
		 *
		 * @param os поток, в который выводится характеристика
		 * @param c корень уравнения
		 *
		 * @return возвращает характерику корня
		 */

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
