#ifndef BOOK_H
#define BOOK_H

#include "include/Constants.h"

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

	public:
		Book(const char* title, const char* author, const char* genre, int volume, int age_restriction)
		{
			strncpy(this->title, title, sizeof(this->title));
			strncpy(this->author, author, sizeof(this->author));
			strncpy(this->genre, genre, sizeof(this->genre));
			this->volume = volume;
			this->age_restriction = age_restriction;
			this->ratings = new int[Constants::max_amount_of_ratings];	
			this->amount_of_ratings = 0;
		}
		
		~Book()
		{
			delete [] ratings;
		}

		void rate(int rating)
		{
			if (amount_of_ratings < 100)
				ratings[amount_of_ratings++] = rating;
		}

		friend std::ostream& operator<<(std::ostream& os, const Book& book)
		{
			os << "Книга { Название: " << book.title << ", Автор: " << book.author << ", Жанр: " << book.genre << ", Объём: " << book.volume << ", Возрастное ограничение: " << book.ageRestriction << ", Оценки: [";
			for (int i = 0; i < book.ratingsCount; i++)
			{
				os << book.ratings[i];
				if (i < book.ratingsCount - 1) os << ", ";
			}
			os << "] }";
			return os;
    	}
};

#endif
