#ifndef LIBRARY_H
#define LIBRARY_H

#include "Constants.h"
#include "Book.h"

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

		Book* get_book(int index) const { return books[index]; }
		
		int get_amount_of_books() const { return amount_of_books; }
};

#endif
