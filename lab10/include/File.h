#ifndef FILE_H
#define FILE_H

#include "FileSystemObject.h"

class File : public FileSystemObject
{
	private:
		std::string name;

	public:
		explicit File(const std::string& n) : name(n) {}
		std::string get_name() const override { return name; }
};

#endif
