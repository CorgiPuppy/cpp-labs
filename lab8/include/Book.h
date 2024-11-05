#ifndef BOOK_H
#define BOOK_H

#include <cstring>

#include "Constants.h"

class Book
{
	private:
		char title[Constants::title_size];
		char author[Constants::author_size];
		char genre[Constants::genre_size];
		int volume;
		int age_restriction;
		int* ratings;
		int amount_of_ratings;

		int reading_times[Constants::max_amount_of_ratings];
		int amount_of_readings;
		int amount_of_borrows;

	public:
		/*
		 * Конструктор класса
		 *
		 * @param title название книги
		 * @param author имя автора
		 * @param genre название жанра
		 * @param volume объем книги
		 * @param age_restriction книжное ограничение по возрасту 
		 */

		Book(const char* title, const char* author, const char* genre, int volume, int age_restriction)
		{
			strncpy(this->title, title, sizeof(this->title));
			strncpy(this->author, author, sizeof(this->author));
			strncpy(this->genre, genre, sizeof(this->genre));
			this->volume = volume;
			this->age_restriction = age_restriction;
			this->ratings = new int[Constants::max_amount_of_ratings];	
			this->amount_of_ratings = 0;
			this->amount_of_borrows = 0;
		}

		/*
		 * Деструктор класса
		 *
		 */
		
		~Book()
		{
			delete [] ratings;
		}

		/*
		 * Увеличение количества взятий книги
		 *
		 */

		void increment_amount_of_borrows() { amount_of_borrows++; }
		
		/*
		 * Оценить книгу
		 *
		 * @param rating оценка книги
		 */

		void rate(int rating)
		{
			if (amount_of_ratings < Constants::max_amount_of_ratings)
				ratings[amount_of_ratings++] = rating;
		}

		/*
		 * Получить среднее арифметическое рейтинга книги
		 *
		 * @return возвращает средний рейтинг книги
		 */

		double get_average_rating()
		{
			if (amount_of_ratings == 0) return 0.0;
			
			int sum = 0;
			for (int i = 0; i < amount_of_ratings; i++)
				sum += ratings[i];

			return static_cast<double>(sum) / amount_of_ratings;
		}

		/*
		 * Время чтения книги
		 *
		 * @param time время чтения
		 */

		void set_reading_time(int time)
		{
			reading_times[amount_of_readings++] = time;
		}

		/*
		 * Получение среднего арифметического времени чтения книги
		 *
		 * @return возвращает среднее время чтения
		 */

		double get_average_reading_time()
		{
			if (amount_of_readings == 0) return 0.0;
				
			int total_time = 0;
			for (int i = 0; i < amount_of_readings; i++)
				total_time += reading_times[i];
			
			return static_cast<double>(total_time) / amount_of_readings;
		}

		/*
		 * Получение количества взятий книги
		 *
		 * @return возвращает количество взятий книги
		 */

		int get_amount_of_borrows() const { return amount_of_borrows; }

		/*
		 * Получение имени автора
		 *
		 * @return возвращает имя автора
		 */

		const char* get_author() const { return author; }

		/*
		 * Получение названия книги
		 *
		 * @return возвращает названия книги 
		 */

		const char* get_title() const { return title; }

		/*
		 * Получение названия жанра книги
		 *
		 * @return возвращает название жанра книги
		 */

		const char* get_genre() const { return genre; }

		/*
		 * Получение объёма книги
		 *
		 * @return возвращает объём книги
		 */

		int get_volume() const { return volume; }

		/*
		 * Получение ограничения по возрасту для чтения книги 
		 *
		 * @return возвращает ограничение по возрасту для чтения книги
		 */

		int get_age_restriction() const { return age_restriction; }

		/*
		 * Вывод через перегруженный оператор характеристики книги
		 *
		 * @param os поток, куда выводится характеристика книги
		 * @param b книга
		 *
		 * @return возвращает характеристику книги
		 */

		friend std::ostream& operator<<(std::ostream& os, const Book& b)
		{
			os << std::endl << "Книга" << std::endl << "{" << std::endl << "\tНазвание - " << b.title << std::endl << "\tАвтор - " << b.author << std::endl << "\tЖанр - " << b.genre << std::endl << "\tОбъём - " << b.volume << std::endl << "\tВозрастное ограничение - " << b.age_restriction << std::endl << "\tОценки - [";
			for (int i = 0; i < b.amount_of_ratings; i++)
			{
				os << b.ratings[i];
				if (i < b.amount_of_ratings - 1) os << ", ";
			}
			os << "]" << std::endl << "}";
			return os;
    	}
};

#endif
