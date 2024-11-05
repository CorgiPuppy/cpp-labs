#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../include/Library.h"
#include "../include/Visitor.h"
#include "../include/Book.h"

void handle_client(int client_socket)
{
    Library library;
    library.add_book("1984", "Джордж Оруэлл", "Научная фантастика", 328, 16);
    library.add_book("Война и мир", "Лев Толстой", "Исторический роман", 1225, 12);
    library.add_book("Гарри Поттер", "Дж.К. Роулинг", "Фэнтези", 300, 12);
	library.add_book("Обломов", "Иван Гончаров", "Социально-психологический роман", 397, 12);
	library.add_book("Тайна сна миллионера", "Агата Кристи", "Детектив", 203, 16);
	library.add_book("Путешествия Гулливера", "Джонатан Свифт", "Приключения", 230, 6);
	library.add_book("Каштанка", "А.П. Чехов", "Рассказ", 32, 6);

    for (int day = Constants::the_first_day; day <= Constants::amount_of_days; day++)
	{
		char buffer[Constants::buffer_size] = {0};
		snprintf(buffer, sizeof(buffer), "\nДень %d:\n", day);
		send(client_socket, buffer, strlen(buffer), 0);

        int amount_of_visitors_today = rand() % Constants::max_amount_of_visitors + Constants::min_amount_of_visitors;

        for (int v = 0; v < amount_of_visitors_today; v++)
		{
            Visitor* visitor;
            visitor = visitor->create_random_visitor();
			library.add_visitor(visitor);

			snprintf(buffer, sizeof(buffer), "\nПосетитель:\n\tВозраст - %d\n\tЖелаемый жанр - %s\n\tЖелаемый объём - %d\n\tСкорость чтения - %d\n", visitor->get_age(), visitor->get_preferred_genre(), visitor->get_preferred_volume(), visitor->get_reading_speed());
			send(client_socket, buffer, strlen(buffer), 0);

            Book* book = library.find_book(visitor->get_age(), visitor->get_preferred_volume(), visitor->get_preferred_genre());
            if (book)
			{
                int reading_time = book->get_volume() / visitor->get_reading_speed();

                snprintf(buffer, sizeof(buffer), "Чтение книги \"%s\" займёт %d часов.\n", book->get_title(), reading_time);
				send(client_socket, buffer, strlen(buffer), 0);

                book->set_reading_time(reading_time);
				int rating = rand() % Constants::max_rating + Constants::min_rating;
                book->rate(rating);

				snprintf(buffer, sizeof(buffer), "Посетитель читает книгу...\n");
				send(client_socket, buffer, strlen(buffer), 0);

                delete visitor; 
            } 
			else
			{
                snprintf(buffer, sizeof(buffer), "Не удалось найти подходящую книгу для посетителя.\n");
				send(client_socket, buffer, strlen(buffer), 0);

                delete visitor;
            }
        }
    }

    library.print_statistics();
	close(client_socket);
}

int main() {
    srand((time(0)));

	int server_fd, new_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Ошибка при создании сокета" << std::endl;
        return -1;
    }

	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        std::cerr << "Ошибка при установке опций сокета" << std::endl;
        return -1;
    }

	address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(Constants::PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Ошибка при привязке" << std::endl;
        return -1;
    }

    if (listen(server_fd, 3) < 0) {
        std::cerr << "Ошибка в прослушивании" << std::endl;
        return -1;
    }

    std::cout << "Сервер запущен. Ожидание подключения клиента..." << std::endl;

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        std::cerr << "Ошибка при подключении клиента" << std::endl;
        return -1;
    }

	handle_client(new_socket);

	close(server_fd);

    return 0;
}
