#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <iostream>
#include <string>

#include "File.h"
#include "Directory.h"

class FileSystem
{
	private:
		Directory** directories;
		int directories_length;
		int directories_capacity;

		Directory* find_directory(const std::string& name)
		{
			for (int i = 0; i < directories_length; i++)
				if (directories[i]->get_name() == name)
					return directories[i];

			return nullptr;
		}

		void resize()
		{
			directories_capacity *= 2;
			Directory** temp_directories = new Directory*[directories_capacity];

			for (int i = 0; i < directories_length; i++)
				temp_directories[i] = directories[i];

			delete [] directories;
			directories = temp_directories;
		}

	public:
		FileSystem()
		:
			directories_length(0),
			directories_capacity(2)
		{
			directories = new Directory*[directories_capacity];
		}

		~FileSystem()
		{
			for (int i = 0; i < directories_length; i++)
				delete directories[i];

			delete [] directories;
		}

		void create_file(const std::string& dir_name, const std::string& file_name)
		{
			try
			{
				Directory* dir = find_directory(dir_name);
				
				if (dir)
				{
					dir->add_object(new File(file_name));
					std::cout << "Файл создан: " << file_name << " в "<< dir_name << std::endl;
				}
				else
					throw std::runtime_error("Директории не существует - " + dir_name);
			}
			catch (const std::runtime_error& e)
			{
				std::cerr << "Ошибка - " << e.what() << std::endl;
			}
		}

		void create_directory(const std::string& dir_name)
		{
			if (directories_length == directories_capacity)
				resize();

			directories[directories_length++] = new Directory(dir_name);
			std::cout << "Директория создана - " << dir_name << std::endl;
		}

		void remove_directory(const std::string& dir_name)
		{
			try
			{
				Directory* dir = find_directory(dir_name);

				if (dir)
				{
					if (dir->get_objects_length() > 0)
						throw std::runtime_error("Не получается удалить директория с файлами: " + dir_name);

					delete dir;

					for (int i = 0; i < directories_length; i++)
					{
						if (directories[i]->get_name() == dir_name)
						{
							directories[i] = directories[directories_length - 1];
							directories_length--;
							break;
						}
					}

					std::cout << "Удалена директория - " << dir_name << std::endl;
				}
				else
					throw std::runtime_error("Не существует директории - " + dir_name);
			}
			catch (const std::runtime_error& e)
			{
				std::cerr << "Ошибка: " << e.what() << std::endl;
			}
		}
};

#endif
