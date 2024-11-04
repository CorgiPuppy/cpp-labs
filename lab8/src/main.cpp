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

    for (int i = 0; i < library.get_amount_of_books(); i++)
	{
        if (visitor.can_read(*library.get_book(i)))
		{
            visitor.read_book(i);
            library.get_book(i)->rate(5);
        }
    }

    std::cout << visitor << std::endl;

	return 0;
}
