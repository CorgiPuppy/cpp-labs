#ifndef FILE_H
#define FILE_H

#include "FileSystemObject.h"

class File : public FileSystemObject
{
	private:
		std::string name;
		std::string description;

	public:
		/*
		 * Конструктор класса файла
		 *
		 * @param n имя файла
		 * @param d описание файла
		 */

		File(const std::string& n, const std::string& d) : name(n), description(d) {}

		/*
		 * Сеттер имени файла
		 *
		 * @param new_name новое имя файла
		 */

		void set_name(const std::string& new_name) { name = new_name; }

		/*
		 * Получение имени файла
		 *
		 * @return возвращает имя файла
		 */

		std::string get_name() const override { return name; }

		/*
		 * Получение пути файла
		 *
		 * @return возвращает путь файла
		 */

		std::string get_path() const override { return name; }

		/*
		 * Получение описания файла
		 *
		 * @return возвращает описание файла
		 */

		std::string get_description() const { return description; }
};

#endif
