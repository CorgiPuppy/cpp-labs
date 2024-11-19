#ifndef FILE_SYSTEM_OBJECT_H
#define FILE_SYSTEM_OBJECT_H

#include <string>

class FileSystemObject
{
	public:
		virtual std::string get_name() const = 0;
		virtual ~FileSystemObject() = default;
};

#endif
