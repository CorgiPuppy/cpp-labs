#ifndef LIBRARY_H
#define LIBRARY_H

#include "Constants.h"
#include "Book.h"
#include "Visitor.h"

#include <iostream>

class Library
{
	private:
		Book* books[Constants::max_amount_of_books];
		int amount_of_books;
		Visitor** visitors;
		int amount_of_visitors;

	public:
		/*
		 * Конструктор класса
		 *
		 */

		Library()
		{
			amount_of_books = 0;
			visitors = new Visitor*[Constants::max_amount_of_visitors]();
			amount_of_visitors = 0;
		}

		/*
		 * Деструктор класса
		 *
		 */

		~Library()
		{
			for (int i = 0; i < amount_of_books; i++)
				delete books[i];

			for (int i = 0; i < amount_of_visitors; i++)
				delete visitors[i];
			delete [] visitors;
		}

		/*
		 * Добавление книги
		 *
		 * @param title название книги
		 * @param author имя автора книги
		 * @param genre название жанра книги
		 * @param volume объём книги
		 * @param age_restriction возрастное ограничение для чтения книги
		 */

		void add_book(const char* title, const char* author, const char* genre, int volume, int age_restriction)
		{
			if (amount_of_books < Constants::max_amount_of_books)
				books[amount_of_books++] = new Book(title, author, genre, volume, age_restriction);
		}

		/*
		 * Добавление посетителя
		 *
		 * @param visitor посетитель
		 */

		void add_visitor(Visitor* visitor)
		{
			if (amount_of_visitors < Constants::max_amount_of_visitors)
				visitors[amount_of_visitors++] = visitor;
		}

		/*
		 * Показать каталог
		 *
		 */

		void show_catalog()
		{
			std::cout << "Каталог:" << std::endl;
			
			for (int i = 0; i < amount_of_books; i++)
				std::cout << *books[i] << std::endl;
		}

		/*
		 * Поиск подходящей книги
		 *
		 * @param visitor_age возраст посетителя
		 * @param preferred_volume желаемый объем книги посетителя
		 * @param preferred_genre желаемое название жанра книги посетителя
		 *
		 * @return возвращает либо подходящую книгу, либо ничего 
		 */

		Book* find_book(int visitor_age, int preferred_volume, const char* preferred_genre)
		{
			for (int i = 0; i < amount_of_books; i++)
				if (books[i]->get_age_restriction() <= visitor_age &&
                    ((preferred_volume == 0 && books[i]->get_volume() < 100) ||
                     (preferred_volume == 1 && books[i]->get_volume() >= 100 && books[i]->get_volume() <= 500) ||
					 (preferred_volume == 2 && books[i]->get_volume() > 500)) &&
                    strcmp(preferred_genre, books[i]->get_genre()) == 0)
				{
					books[i]->increment_amount_of_borrows();
                    return books[i];
				}

			return nullptr;
		}

		/*
		 * Вывод в консоль статистики моделирования
		 *
		 */

		void print_statistics()
		{
			std::cout << std::endl << "Статистика по книгам:" << std::endl;
			for (int i = 0; i < amount_of_books; i++)
			{
				std::cout << "\tКнига - " << books[i]->get_title() << std::endl;
				std::cout << "\t\tСредняя оценка - " << books[i]->get_average_rating() << std::endl;
				std::cout << "\t\tСреднее время чтения - " << books[i]->get_average_reading_time() << " часов" << std::endl;
				std::cout << "\t\tКоличество взятий - " << books[i]->get_amount_of_borrows() << std::endl;
			}

			int max_amount_of_authors = Constants::max_amount_of_authors;
			char* authors[max_amount_of_authors] = { nullptr };
			int amount_of_borrows_author[max_amount_of_authors] = { 0 };
			int amount_of_authors = 0;
			for (int i = 0; i < amount_of_books; i++)
			{
				const char* author = books[i]->get_author();
				bool found = false;

				for (int j = 0; j < amount_of_authors; j++)
				{
					if (strcmp(authors[j], author) == 0)
					{
						amount_of_borrows_author[j] += books[i]->get_amount_of_borrows();
						found = !found;
						break;
					}
				}

				if (!found && amount_of_authors < max_amount_of_authors)
				{
					authors[amount_of_authors] = strdup(author);
					amount_of_borrows_author[amount_of_authors] = books[i]->get_amount_of_borrows();
					amount_of_authors++;
				}
			}

			std::cout << std::endl << "\tКоличество взятий книг по авторам:" << std::endl;
			for (int i = 0; i < amount_of_authors; i++)
			{
				std::cout << "\t\tАвтор - " << authors[i] << std::endl << "\t\t\tВзятий книг - " << amount_of_borrows_author[i] << std::endl;
				free(authors[i]);
			}
		}

		/*
		 * Получение книги
		 * 
		 * @param index индекс книги в каталоге
		 *
		 * @return возвращает книгу
		 */

		Book* get_book(int index) const { return books[index]; }
		
		/*
		 * Получение количества книг
		 *
		 * @return возвращает количество книг
		 */

		int get_amount_of_books() const { return amount_of_books; }
		
		/*
		 * Получение количества зарегистрированных посетителей
		 *
		 * @return возвращает количество зарегистрированных посетителей
		 */

		int get_amount_of_registered_visitors() const { return amount_of_visitors; }

		/*
		 * Получение зарегистрированного посетителя
		 *
		 * @param index индекс зарегистрированного посетителя
		 *
		 * @return возвращает зарегистрированного посетителя
		 */

		Visitor* get_registered_visitor(int index)
		{
			if (index >= 0 && index < amount_of_visitors)
				return visitors[index];

			return nullptr;
		}
};

#endif
