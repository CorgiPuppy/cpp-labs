#include <iostream>

#include "../include/Library.h"
#include "../include/Visitor.h"
#include "../include/Book.h"

int main()
{
	Library library;
	library.add_book("1984", "George Orwell", "Научная фантастика", 328, 16);
    library.add_book("Война и мир", "Лев Толстой", "Исторический роман", 1225, 12);
    library.add_book("Гарри Поттер", "Дж.К. Роулинг", "Фэнтези", 300, 10);

    Visitor visitor(18, "Научная фантастика", 2, 50);

    library.show_catalog();

	Book* found_book = library.find_book(visitor.get_age(), visitor.get_preferred_volume(), visitor.get_preferred_genre());
	if (found_book)
		visitor.read_book(*found_book);
	else
		std::cout << "Книги, соответствующей заданным критериям, не найдено." << std::endl;

    std::cout << visitor << std::endl;

	return 0;
}
