#ifndef FILE_H
#define FILE_H

#include "FileSystemObject.h"

class File : public FileSystemObject
{
	private:
		std::string name;
		std::string description;

	public:
		File(const std::string& n, const std::string& d) : name(n), description(d) {}

		void set_name(const std::string& new_name) { name = new_name; }

		std::string get_name() const override { return name; }

		std::string get_path() const override { return name; }

		std::string get_description() const { return description; }
};

#endif
