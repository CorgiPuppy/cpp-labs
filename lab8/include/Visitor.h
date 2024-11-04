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

		Visitor* create_random_visitor()
		{
			int age = rand() % Constants::max_age_of_visitors + Constants::min_age_of_visitors; 
			const char** genres = Constants::genre_names;
			const char* preferred_genre = genres[rand() % Constants::amount_of_genres];
			int preferred_volume = rand() % Constants::amount_of_preferred_volumes;
			int reading_speed = rand() % Constants::max_reading_speed + Constants::min_reading_speed;
			return new Visitor(age, preferred_genre, preferred_volume, reading_speed);
		}

		int get_age() const { return age; }
		
		const char* get_preferred_genre() const { return preferred_genre; }

		int get_preferred_volume() const { return preferred_volume; }

		int get_reading_speed() const { return reading_speed; }

		friend std::ostream& operator<<(std::ostream& os, const Visitor& v)
		{
			os << std::endl << "Посетитель" << std::endl << "{" << std::endl << "\tВозраст - " << v.age << std::endl << "\tЖелаемый жанр - " << v.preferred_genre << std::endl << "\tЖелаемый объём - " << v.preferred_volume << std::endl << "\tСкорость чтения - " << v.reading_speed << std::endl << "}" << std::endl;
			return os;
		}
};

#endif
