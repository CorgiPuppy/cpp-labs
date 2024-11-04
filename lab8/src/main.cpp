#include <iostream>

#include "../include/Library.h"
#include "../include/Visitor.h"
#include "../include/Book.h"

int main() {
    srand((time(0)));

    Library library;
    library.add_book("1984", "George Orwell", "Научная фантастика", 328, 16);
    library.add_book("Война и мир", "Лев Толстой", "Исторический роман", 1225, 12);
    library.add_book("Гарри Поттер", "Дж.К. Роулинг", "Фэнтези", 300, 10);

    for (int day = Constants::the_first_day; day <= Constants::amount_of_days; day++) {
        std::cout << std::endl << "День " << day << ":" << std::endl;

        int amount_of_visitors = rand() % Constants::max_amount_of_visitors + Constants::min_amount_of_visitors;

        for (int v = 0; v < amount_of_visitors; v++) {
            Visitor* visitor;
			visitor = visitor->create_random_visitor();
            std::cout << *visitor;

            Book* book = library.find_book(visitor->get_age(), visitor->get_preferred_volume(), visitor->get_preferred_genre());
            if (book) {
                int reading_time = book->get_volume() / visitor->get_reading_speed();
                std::cout << "Чтение книги \"" << book->get_genre() << "\" займет " << reading_time << " часов." << std::endl;
                book->set_reading_time(reading_time);
				int rating = rand() % Constants::max_rating + Constants::min_rating;
                book->rate(rating);

				std::cout << "Посетитель читает книгу..." << std::endl;

                delete visitor; 
            } 
			else
			{
                std::cout << "Не удалось найти подходящую книгу для посетителя." << std::endl;
                delete visitor;
            }
        }
    }

    library.print_statistics();

    return 0;
}
