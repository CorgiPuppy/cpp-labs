#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "FileSystemObject.h"

class Directory : public FileSystemObject
{
	private:
		std::string name;
		FileSystemObject** objects;
		int objects_length;
		int objects_capacity;

		void resize()
		{
			objects_capacity *= 2;
			FileSystemObject** temp_objects = new FileSystemObject*[objects_capacity];
			
			for (int i = 0; i < objects_length; i++)
				temp_objects[i] = objects[i];

			delete [] objects;
			objects = temp_objects;
		}

	public:
		explicit Directory(const std::string& n)
		:
			name(n),
			objects_length(0),
			objects_capacity(0)
		{
			objects = new FileSystemObject*[objects_capacity];
		}
		
		~Directory()
		{
			for (int i = 0; i < objects_length; i++)
				delete objects[i];

			delete [] objects;
		}

		std::string get_name() const override { return name; }

		void add_object(FileSystemObject* obj)
		{
			if (objects_length == objects_capacity)
				resize();

			objects[objects_length++] = obj;
		}

		void remove_object(const std::string& object_name)
		{
			for (int i = 0; i < objects_length; i++)
			{
				if (objects[i]->get_name() == object_name)
				{
					delete objects[i];

					for (int j = i; j < objects_length - 1; j++)
						objects[j] = objects[j + 1];

					objects_length--;
					
					return;
				}
			}
			
			throw std::runtime_error("Объект не найден: " + object_name);
		}

		FileSystemObject** get_objects() const { return objects; }

		int get_objects_length() const { return objects_length; }
};

#endif
