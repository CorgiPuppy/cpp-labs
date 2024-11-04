#ifndef VISITOR_H
#define VISITOR_H

#include "Constants.h"
#include "Book.h"

class Visitor
{
	private:
		int age;
		char preferred_genre[Constants::genre_size];
		int preferred_volume;
		int reading_speed;
		bool* read_books;
		int amount_of_read_books;

	public:
		Visitor(int age, const char* preferred_genre, int preferred_volume, int reading_speed)
		{
			this->age = age;
			strncpy(this->preferred_genre, preferred_genre, sizeof(this->preferred_genre));
			this->preferred_volume = preferred_volume;
			this->reading_speed = reading_speed;
			this->read_books = new bool[Constants::max_amount_of_books];
			this->amount_of_read_books = 0;
		}

		~Visitor()
		{
			delete [] read_books;
		}

		bool can_read(const Book& book)
		{
			if (book.get_age_restriction() > age)
				return false;

			if ((preferred_volume == 0 && book.get_volume() < 100) ||
                 (preferred_volume == 1 && book.get_volume() >= 100 && book.get_volume() <= 500) ||
				 (preferred_volume == 2 && book.get_volume() > 500))
                return false;

			if (strcmp(preferred_genre, book.get_genre()) != 0)
				return false;

			return true;
		}
	
		void read_book(const Book& book)
		{
			if (can_read(book))
			{
				int reading_time = book.get_volume() / reading_speed;
				std::cout << "Чтение книги \"" << book.get_genre() << "\" займет " << reading_time << " часов." << std::endl;
			}
			else
				std::cout << "Вы не можете прочитать эту книгу." << std::endl;
		}

		int get_age() const { return age; }
		
		const char* get_preferred_genre() const { return preferred_genre; }

		int get_preferred_volume() const { return preferred_volume; }

		friend std::ostream& operator<<(std::ostream& os, const Visitor& v)
		{
			os << std::endl << "Посетитель" << std::endl << "{" << std::endl << "\tВозраст - " << v.age << std::endl << "\tЖелаемый жанр - " << v.preferred_genre << std::endl << "\tЖелаемый объём - " << v.preferred_volume << std::endl << "\tСкорость чтения - " << v.reading_speed << std::endl << "}" << std::endl;
			return os;
		}
};

#endif
