#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants
{
	const int PORT = 8080;
	const int buffer_size = 1024;
	const int backlog = 3;

	const int title_size = 100;
	const int author_size = 100;
	const int genre_size = 100;
	const int max_amount_of_ratings = 100;

	const int max_amount_of_books = 30;

	const int max_amount_of_authors = 100;

	const int max_age_of_visitors = 100;
	const int min_age_of_visitors = 10;

	const int amount_of_genres = 8;
	const char* genre_names[amount_of_genres] = {"Научная фантастика", "Фэнтези", "Исторический роман", "Детектив", "Coциально-психологический роман", "Приключения", "Рассказ", "Сатирическая повесть"};

	const int amount_of_preferred_volumes = 3;

	const int max_reading_speed = 100;
	const int min_reading_speed = 10;

	const int the_first_day = 1;
	const int amount_of_days = 30;

	const int max_amount_of_visitors = 5; 
	const int min_amount_of_visitors = 1;

	const int max_rating = 10;
	const int min_rating = 1;
}

#endif

