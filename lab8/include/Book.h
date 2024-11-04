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
			if (amount_of_ratings < Constants::max_amount_of_ratings)
				ratings[amount_of_ratings++] = rating;
		}

		double get_average_rating()
		{
			if (amount_of_ratings == 0) return 0.0;
			
			int sum = 0;
			for (int i = 0; i < amount_of_ratings; i++)
				sum += ratings[i];

			return static_cast<double>(sum) / amount_of_ratings;
		}

		void set_reading_time(int time)
		{
			reading_times[amount_of_readings++] = time;
		}

		double get_average_reading_time()
		{
			if (amount_of_readings == 0) return 0.0;
				
			int total_time = 0;
			for (int i = 0; i < amount_of_readings; i++)
				total_time += reading_times[i];
			
			return static_cast<double>(total_time) / amount_of_readings;
		}

		const char* get_title() const { return title; }

		const char* get_genre() const { return genre; }

		int get_volume() const { return volume; }

		int get_age_restriction() const { return age_restriction; }

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
