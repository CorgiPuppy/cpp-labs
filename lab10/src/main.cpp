#include "../include/FileSystem.h"

void commandLoop(FileSystem& fs)
{	
	std::cout << "\tВведите " << Colors::yellow << "команду" << Colors::reset << ", чтобы начать. " << std::endl << "\tНапишите " << Colors::green << "'help'" << Colors::reset << ", чтобы увидеть список возможных команд." << std::endl;

    std::string command;
    while (fs.is_running())
	{
        std::cout << Colors::yellow << "> " << Colors::reset;
        std::getline(std::cin, command);
        if (command.empty()) continue;

        std::istringstream iss(command);
        std::string action;
        std::string name;
        std::string type;
        std::string description;

        iss >> action;

        if (action == "create_dir")
		{
            iss >> name;
            std::thread([&fs, name]()
			{
                try
				{
                    fs.create_dir(name);
                }
				catch (const std::exception& e)
				{
                    std::cerr << Colors::red << "Ошибка: " << e.what() << Colors::reset << std::endl;
                }
            }).detach();
        }
		else if (action == "create_file")
		{
            iss >> name;
            std::getline(iss, description);
            std::thread([&fs, name, description]()
			{
                try
				{
                    fs.create_file(name, description);
                }
				catch (const std::exception& e)
				{
                    std::cerr << Colors::red << "Ошибка: " << e.what() << Colors::reset << std::endl;
                }
            }).detach();
        }
		else if (action == "delete")
		{
            iss >> name;
            std::thread([&fs, name]()
			{
                try
				{
                    fs.delete_object(name);
                }
				catch (const std::exception& e)
				{
                    std::cerr << Colors::red << "Ошибка: " << e.what() << Colors::reset << std::endl;
                }
            }).detach();
        }
		else if (action == "rename")
		{
            std::string oldName, newName;
            iss >> oldName >> newName;
            std::thread([&fs, oldName, newName]()
			{
                try
				{
                    fs.rename_object(oldName, newName);
                }
				catch (const std::exception& e)
				{
                    std::cerr << Colors::red << "Ошибка: " << e.what() << Colors::reset << std::endl;
                }
            }).detach();
        }
		else if (action == "change_dir")
		{
            iss >> name;
            std::thread([&fs, name]()
			{
                try
				{
                    fs.change_dir(name);
                }
				catch (const std::exception& e)
				{
                    std::cerr << Colors::red << "Ошибка: " << e.what() << Colors::reset << std::endl;
                }
            }).detach();
        }
		else if (action == "move")
		{
            std::string objectName, targetDirName;
            iss >> objectName >> targetDirName;
            std::thread([&fs, objectName, targetDirName]()
			{
                try
				{
                    fs.move(objectName, targetDirName);
                }
				catch (const std::exception& e)
				{
                    std::cerr << Colors::red << "Ошибка: " << e.what() << Colors::reset << std::endl;
                }
            }).detach();
        }
		else if (action == "find")
		{
            iss >> name;
            std::thread([&fs, name]()
			{
				try
				{
					fs.find_objects(name);
				}
				catch (const std::exception& e)
				{
                    std::cerr << Colors::red << "Ошибка: " << e.what() << Colors::reset << std::endl;
				}
            }).detach();
        }
		else if (action == "count")
		{
            std::string namePattern;
            iss >> namePattern;
            iss >> type;
            std::thread([&fs, namePattern, type]()
			{
                try
				{
                    fs.count_objects(namePattern, type);
                }
				catch (const std::exception& e)
				{
                    std::cerr << Colors::red << "Ошибка: " << e.what() << Colors::reset << std::endl;
                }
            }).detach();
        }
		else if (action == "show_tree")
		{
            iss >> name;
            std::thread([&fs, name]()
			{
				try
				{
					if (name.empty())
						fs.show_current_tree();
					else
						fs.show_tree(name);
				}
				catch (const std::exception& e)
				{
                    std::cerr << Colors::red << "Ошибка: " << e.what() << Colors::reset << std::endl;
				}
            }).detach();
        }
		else if (action == "help")
		{
			fs.help();
		}
		else if (action == "exit")
		{
            fs.stop();
            break;
        }
        else
            std::cout << Colors::red << "\tНеизвестная команда: " << Colors::reset << action << std::endl;
    }
}

int main() {
    FileSystem fs;
    std::thread inputThread(commandLoop, std::ref(fs));
    inputThread.join(); // Ждем завершения потока ввода команд
    return 0;
}
