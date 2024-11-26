#ifndef FILE_SYSTEM_OBJECT_H
#define FILE_SYSTEM_OBJECT_H

#include <string>

class FileSystemObject
{
	public:
		/*
		 * Деструктор класса объекта файловой системы
		 *
		 */

		virtual ~FileSystemObject() = default;
		
		/*
		 * Получение имени объекта
		 *
		 * @return возвращает имя объекта
		 */

		virtual std::string get_name() const = 0;
		
		/*
		 * Получение пути объекта
		 *
		 * @return возвращает путь объекта
		 */

		virtual std::string get_path() const = 0;
};

#endif
