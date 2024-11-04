#ifndef LIBRARY_H
#define LIBRARY_H

#include "Constants.h"
#include "Book.h"

#include <iostream>

class Library
{
	private:
		Book* books[Constants::max_amount_of_books];
		int amount_of_books;

	public:
		Library()
		{
			amount_of_books = 0;
		}

		~Library()
		{
			for (int i = 0; i < amount_of_books; i++)
				delete books[i];
		}

		void add_book(const char* title, const char* author, const char* genre, int volume, int age_restriction)
		{
			if (amount_of_books < 30)
				books[amount_of_books++] = new Book(title, author, genre, volume, age_restriction);
		}

		void show_catalog()
		{
			std::cout << "Каталог:" << std::endl;
			
			for (int i = 0; i < amount_of_books; i++)
				std::cout << *books[i] << std::endl;
		}

		Book* find_book(int visitor_age, int preferred_volume, const char* preferred_genre)
		{
			for (int i = 0; i < amount_of_books; i++)
				if (books[i]->get_age_restriction() <= visitor_age &&
                    ((preferred_volume == 0 && books[i]->get_volume() < 100) ||
                     (preferred_volume == 1 && books[i]->get_volume() >= 100 && books[i]->get_volume() <= 500) ||
					 (preferred_volume == 2 && books[i]->get_volume() > 500)) &&
                    strcmp(preferred_genre, books[i]->get_genre()) == 0)
                    return books[i];

			return nullptr;
		}

		void print_statistics()
		{
			std::cout << std::endl << "Статистика по книгам:" << std::endl;
			for (int i = 0; i < amount_of_books; i++)
			{
				std::cout << "\tКнига - " << books[i]->get_title() << std::endl;
				std::cout << "\t\tСредняя оценка - " << books[i]->get_average_rating() << std::endl;
				std::cout << "\t\tСреднее время чтения - " << books[i]->get_average_reading_time() << " часов" << std::endl;
			}
		}

		Book* get_book(int index) const { return books[index]; }
		
		int get_amount_of_books() const { return amount_of_books; }
};

#endif
