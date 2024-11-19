#include <iostream>

#include "../include/FileSystem.h"

int main()
{
	FileSystem fs;

	fs.create_directory("Документы");
	fs.create_file("Документы", "file_1.txt");
	fs.create_file("Документы", "file_2.txt");

    fs.remove_directory("Документы"); // Не удастся удалить, т.к. в ней есть файлы
    fs.remove_directory("NonExistentDir"); // Не удастся удалить, т.к. папка не существует

	return 0;
}
