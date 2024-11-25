#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include "Directory.h"
#include "Colors.h"

#include <thread>
#include <mutex>
#include <atomic>

std::mutex fs_mutex;

class FileSystem
{
	private:
		std::unique_ptr<Directory> root;
		Directory* current_directory;
		std::atomic<bool> running;

	public:
		FileSystem()
		{
			root = std::make_unique<Directory>("root");
			current_directory = root.get();
			running = true;
		}

		void create_dir(const std::string& name)
		{
			std::lock_guard<std::mutex> guard(fs_mutex);

			if (current_directory->find_child(name) != nullptr)
				throw std::runtime_error("Папка с таким именем уже существует.");

			current_directory->add_child(std::make_shared<Directory>(name, current_directory));
		}

		void create_file(const std::string& name, const std::string& description)
		{
			std::lock_guard<std::mutex> guard(fs_mutex);

			if (current_directory->find_child(name) != nullptr)
				throw std::runtime_error("Файл с таким именем уже существует.");

			current_directory->add_child(std::make_shared<File>(name, description));
		}

		void delete_object(const std::string& name)
		{
			std::lock_guard<std::mutex> guard(fs_mutex);

			std::shared_ptr<FileSystemObject> object = current_directory->find_child(name);
			if (object)
			{
				if (Directory* directory = dynamic_cast<Directory*>(object.get()))
					if (!directory->get_children().empty())
						throw std::runtime_error("Нельзя удалить папку, содержащую объекты.");

				current_directory->remove_child(name);
			}
			else
				throw std::runtime_error("Объект не найден.");
		}

		void rename_object(const std::string& old_name, const std::string& new_name)
		{
			std::lock_guard<std::mutex> guard(fs_mutex);

			std::shared_ptr<FileSystemObject> object = current_directory->find_child(old_name);
			if (!object)
				throw std::runtime_error("Объект для переименования не найден.");
			if (current_directory->find_child(new_name) != nullptr)
				throw std::runtime_error("Объект с таким именем уже существует.");

			if (Directory* directory = dynamic_cast<Directory*>(object.get()))
				directory->set_name(new_name);
			else
			{
				File* file = dynamic_cast<File*>(object.get());
				file->set_name(new_name);
			}
		}

		void change_dir(const std::string& name)
		{
			std::lock_guard<std::mutex> guard(fs_mutex);

			if (name == "..")
			{
				if (current_directory->get_path() != "root")
					current_directory = current_directory->get_parent();
			}
			else
			{
				std::shared_ptr<FileSystemObject> new_directory = current_directory->find_child(name);
				if (new_directory && dynamic_cast<Directory*>(new_directory.get()))
					current_directory = static_cast<Directory*>(new_directory.get());
				else
					throw std::runtime_error("Папка не найдена.");
			}
		}

		void move(const std::string& object_name, const std::string& target_directory_name)
		{
			std::lock_guard<std::mutex> guard(fs_mutex);

			Directory* target_directory = nullptr;

			if (target_directory_name == "..")
				target_directory = current_directory->get_parent();
			else
			{
				std::shared_ptr<FileSystemObject> target = current_directory->find_child(target_directory_name);
				if (target && dynamic_cast<Directory*>(target.get()))
					target_directory = static_cast<Directory*>(target.get());
				else
					throw std::runtime_error("Целевая папка не найдена.");
			}

			move_object(object_name, target_directory);
		}

		void move_object(const std::string& object_name, Directory* target_directory)
		{
			std::shared_ptr<FileSystemObject> object = current_directory->find_child(object_name);
			if (!object)
				throw std::runtime_error("Объект для перемещения не найден.");
			if (target_directory->find_child(object_name) != nullptr)
				throw std::runtime_error("Объект с таким именем уже существует в этой папке.");

			if (Directory* directory = dynamic_cast<Directory*>(object.get()))
			{
				if (directory == target_directory)
					throw std::runtime_error("Нельзя переместить папку в саму себя.");

				std::string temp_directory_name = directory->get_name();
				std::shared_ptr<Directory> temp_directory = std::make_shared<Directory>(temp_directory_name, target_directory);
				target_directory->add_child(temp_directory);

				for (auto& [child_name, child_object] : directory->get_children())
					temp_directory->add_child(child_object);

				directory->clear();
				current_directory->remove_child(object_name);
			}
			else
			{
				if (target_directory->find_child(object_name) != nullptr)
					throw std::runtime_error("Объект с таким именем уже существует в этой директории.");

				current_directory->remove_child(object_name);
				target_directory->add_child(object);
			}
		}

		void show_tree(const std::string& directory_name)
		{
			Directory* target_directory = find_directory(directory_name, root.get());
			if (target_directory)
				target_directory->show_tree();
			else
				std::cerr << Colors::red << "Директория не найдена." << Colors::reset << std::endl;
		}

		Directory* find_directory(const std::string& name, Directory* current)
		{
			if (current->get_name() == name)
				return current;

			for (const auto& [_, child_object] : current->get_children())
			{
				if (Directory* directory = dynamic_cast<Directory*>(child_object.get()))
				{
					Directory* is_found = find_directory(name, directory);
					
					if (is_found)
						return is_found;
				}
			}

			return nullptr;
		}

		void show_current_tree()
		{
			std::lock_guard<std::mutex> guard(fs_mutex);

			current_directory->show_tree();
		}

		void find_objects(const std::string& name)
		{
			std::vector<std::string> results;

			current_directory->find_all(name, results);
			if (results.empty())
				std::cout << Colors::red << "Не найдено объектов, удовлетворяющих паттерну - " << Colors::green << name << Colors::reset << std::endl;
			else
			{
				std::cout << Colors::red << "Найдены объекты, удовлетворяющие паттерну - " << Colors::green << name << Colors::reset << std::endl;

				for (const auto& path : results)
					std::cout << path << std::endl;
			}
		}

		void count_objects(const std::string& name_pattern, const std::string& type = "")
		{
			int amount_of_objects = current_directory->count_objects(name_pattern, type);

			std::cout << Colors::red << "Найдено " << Colors::green << amount_of_objects << Colors::red << " удовлетворяющих объектов." << Colors::reset << std::endl;
		}

		void help()
		{
			std::cout << "\tВозможные команды:" << std::endl
                      << Colors::yellow << "\t\tcreate_dir" << Colors::reset << " <name>\t" << "создать папку;" << std::endl
                      << Colors::yellow << "\t\tcreate_file" << Colors::reset << " <name>\t" << "создать файл;" << std::endl
                      << Colors::yellow << "\t\trename" << Colors::reset << " <name>\t\t" << "переименовать объект;" << std::endl
                      << Colors::yellow << "\t\tdelete" << Colors::reset << " <name>\t\t" << "удалить объект;" << std::endl
                      << Colors::yellow << "\t\tmove" << Colors::reset << " <name> <to>\t" << "переместить объект в папку;" << std::endl
                      << Colors::yellow << "\t\tchange_dir" << Colors::reset << " <name>\t" << "перейти в подпапку;" << std::endl
                      << Colors::yellow << "\t\tshow_tree" << Colors::reset << " <name>\t" << "просмотреть дерево папок от папки;" << std::endl
                      << Colors::yellow << "\t\tfind" << Colors::reset << " <name>\t\t" << "поиск всех объектов;" << std::endl
                      << Colors::yellow << "\t\tcount" << Colors::reset << " <name> <type>\t" << "подсчёт количества объектов в папке;" << std::endl
                      << Colors::yellow << "\t\texit" << Colors::reset << "\t\t\t" << "выход." << std::endl;
		}

		void stop()
		{
			running = false;
		}

		bool is_running() const
		{
			return running;
		}
};

#endif
