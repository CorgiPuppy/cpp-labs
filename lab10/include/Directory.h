#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "FileSystemObject.h"
#include "File.h"

#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <regex>
#include <vector>

class Directory : public FileSystemObject
{
	private:
		std::string name;
		Directory* parent;
		std::map<std::string, std::shared_ptr<FileSystemObject>> children;

	public:
		/*
		 * Конструктор класса папки
		 *
		 * @param n название папки
		 * @param p родительская директория 
		 */

		Directory(const std::string& n, Directory* p = nullptr) : name(n), parent(p) {}

		/*
		 * Добавление дочернего объекта директории
		 *
		 * @param child дочерний объект текущей папки
		 */

		void add_child(const std::shared_ptr<FileSystemObject>& child)
		{
			Directory* directory = dynamic_cast<Directory*>(child.get());

			if (directory)
				directory->parent = this;

			children[child->get_name()] = child;
		}

		/*
		 * Удаление дочернего объекта директории
		 *
		 * @param child_name название дочернего объекта
		 */

		void remove_child(const std::string& child_name)
		{
			if (children.count(child_name) > 0)
			{
				if (dynamic_cast<Directory*>(children[child_name].get()) &&
                    !static_cast<Directory*>(children[child_name].get())->get_children().empty())
					throw std::runtime_error("Нельзя удалить папку, содержащую файлы либо папки.");

				children.erase(child_name);
			}
			else
				throw std::runtime_error("Объект не найден.");
		}

		/*
		 * Очистка всех дочерних объектов папки
		 *
		 */

		void clear()
		{
			for (auto& [child_name, child_object] : children)
				if (Directory* directory = dynamic_cast<Directory*>(child_object.get()))
					directory->clear();

			children.clear();
		}

		/*
		 * Посмотреть дерево объектов
		 *
		 * @param depth глубина иерархии
		 */

		void show_tree(int depth = 0)
		{
			std::cout << std::string(depth, '-') << name << std::endl;
			
			for (const auto& [_, child_object] : children)
			{
				if (Directory* directory = dynamic_cast<Directory*>(child_object.get()))
					directory->show_tree(depth + 1);
				else
					std::cout << std::string(depth + 1, '-') << child_object->get_name() << std::endl;
			}
		}

		/*
		 * Поиск дочернего объекта
		 *
		 * @param child_name название дочернего объекта
		 *
		 * @return возвращает дочерний объект, если true, иначе - нулевой указатель
		 */

		std::shared_ptr<FileSystemObject> find_child(const std::string& child_name)
		{
			return children.count(child_name) > 0 ? children[child_name] : nullptr;
		}

		/*
		 * Поиск всех объектов
		 *
		 * @param pattern шаблон, по которому нужно искать название объекта
		 * @param results вектор всех названий объектов, удовлетворяющих шаблону
		 */

		void find_all(const std::string& pattern, std::vector<std::string>& results)
		{
			std::regex regex_pattern(convert_to_regex(pattern));

			for (const auto& [_, child_object] : children)
			{
				if (std::regex_match(child_object->get_name(), regex_pattern))
					results.push_back(child_object->get_path());

				if (Directory* directory = dynamic_cast<Directory*>(child_object.get()))
					directory->find_all(pattern, results);
			}
		}

		/*
		 * Преобразование шаблона в регулярное выражение
		 *
		 * @param pattern шаблон
		 *
		 * @return возвращает шаблон регулярного выражения
		 */

		std::string convert_to_regex(const std::string& pattern)
		{
			std::string regex = "^";

			bool asterisk_is_used = false;

			for (char c : pattern)
			{
				if (c == '*')
				{
					if (!asterisk_is_used)
					{
						regex += ".*";

						asterisk_is_used = true;
					}
				}
				else if (c == '?')
					regex += '.';
				else if (c == '|')
					regex += '|';
				else
				{
					regex += c;

					asterisk_is_used = false;
				}
			}

			regex += "$";

			return regex;
		}

		/*
		 * Подсчёт количества всех объектов, удовлетворяющих шаблону
		 *
		 * @param name_pattern шаблон, по которому нужно искать название объекта
		 * @param type тип объекта (файл, или папка, или пустой по умолчанию)
		 *
		 * @return возвращает количество найденных объектов
		 */

		int count_objects(const std::string& name_pattern, const std::string& type = "")
		{
			int count = 0;

			std::regex regex_pattern(convert_to_regex(name_pattern));

			for (const auto& [_, child] : children)
			{
				bool name_match = std::regex_match(child->get_name(), regex_pattern);
				bool type_match = type.empty() ||
                                  (type == "file" && dynamic_cast<File*>(child.get())) ||
                                  (type == "directory" && dynamic_cast<Directory*>(child.get()));

                if (name_match && type_match)
					count++;
			}

			return count;
		}

		/*
		 * Получение названия папки
		 *
		 * @return возвращает названия папки
		 */

		std::string get_name() const override { return name; }

		/*
		 * Получение пути папки
		 *
		 * @return возвращает путь папки
		 */
		
		std::string get_path() const override
		{
			return parent ? parent->get_path() + "/" + name : name;
		}

		/*
		 * Установка нового названия папки
		 *
		 * @param new_name новое название папки
		 */

		void set_name(const std::string& new_name) { name = new_name; }

		/*
		 * Получение родительной папки
		 *
		 * @return возвращает родительскую папку
		 */

		Directory* get_parent() const { return parent; }

		/*
		 * Получение дочерних объектов папки
		 *
		 * @return возвращает дочерние объекты папки
		 */

		const std::map<std::string, std::shared_ptr<FileSystemObject>>& get_children() const { return children; }
};

#endif
