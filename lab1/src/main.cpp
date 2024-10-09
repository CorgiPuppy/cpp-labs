/*
 * Лабораторная работа номер 1
 * Вариант 3
 * Требуется написать программу, которая генерирует строку, состоящую из 1000 случайных символов английского алфавита.
 * Требуется реализовать игру в угадай слово (слово угадывается, выбирая буквы случайно), когда программа пытается подобрать аналогичную строку посимвольно, при этом угадываются символы только последовательно.
 * По итогу , нужно подсчитать и вывести сколько потребовалось итераций на подбор строки, и максимальное количество попыток угадать один символ.
 */	

#include <iostream>

using namespace std;

const int LEN = 1000;
const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

string random_string();
void find_string(const string &, string &, int &, int &);

int main()
{
	srand((time(nullptr)));

	string my_string = random_string();
	cout << endl << "My string: " << my_string << endl;

	string target_string;
	int max_counter = 0;
	int all_iterations = 0;

	find_string(my_string, target_string, all_iterations, max_counter);

	cout << endl << "New string: " << target_string << endl;
	cout << endl << "Max counter: " << max_counter << endl;
	cout << "Iterations: " << all_iterations << endl;

	return 0;
}

/*
 * Формирование случайной строки
 *
 * @return возвращает сформированную случайную строку.
 */

string random_string() 
{
	string temp_string;

	for (int i = 0; i < LEN; i++
		temp_string += alphabet[rand() % sizeof(alphabet)];

	return temp_string;
}

/*
 * Поиск аналогичной строки
 *
 * @param my_string сформированная случайная строка.
 * @param target_string целевая строка. 
 * @param all_iterations количество итераций на подбор строки.
 * @param max_counter максимальное количество попыток угадать один символ.
 */

void find_string(const string &my_string, string &target_string, int &all_iterations, int &max_counter)
{
	target_string = string(LEN, '0');

	for (int i = 0; i < LEN; i++)
	{
		int counter = 0;

		while (target_string[i] != my_string[i])
		{
			all_iterations++;
			target_string[i] = alphabet[rand() % sizeof(alphabet)];
			counter++;
		}
		
		max_counter = (counter > max_counter) ? counter : max_counter;
	}
}
