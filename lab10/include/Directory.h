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
		Directory(const std::string& n, Directory* p = nullptr) : name(n), parent(p) {}

		void add_child(const std::shared_ptr<FileSystemObject>& child)
		{
			auto directory = dynamic_cast<Directory*>(child.get());

			if (directory)
				directory->parent = this;

			children[child->get_name()] = child;
		}

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

		void clear()
		{
			for (auto& [child_name, child_object] : children)
				if (Directory* directory = dynamic_cast<Directory*>(child_object.get()))
					directory->clear();

			children.clear();
		}

		void show_tree(int depth = 0)
		{
			std::cout << std::string(depth, '-') << name << std::endl;
			
			for (const auto& [_, child] : children)
			{
				if (auto dir = dynamic_cast<Directory*>(child.get()))
					dir->show_tree(depth + 1);
				else
					std::cout << std::string(depth + 1, '-') << child->get_name() << std::endl;
			}
		}

		std::shared_ptr<FileSystemObject> find_child(const std::string& child_name)
		{
			return children.count(child_name) > 0 ? children[child_name] : nullptr;
		}

		void find_all(const std::string& pattern, std::vector<std::string>& results)
		{
			std::regex regex_pattern(convert_to_regex(pattern));

			for (const auto& [_, child] : children)
			{
				if (std::regex_match(child->get_name(), regex_pattern))
					results.push_back(child->get_path());

				if (auto dir = dynamic_cast<Directory*>(child.get()))
					dir->find_all(pattern, results);
			}
		}

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

		std::string get_name() const override { return name; }

		std::string get_path() const override
		{
			return parent ? parent->get_path() + "/" + name : name;
		}

		void set_name(const std::string& new_name) { name = new_name; }

		Directory* get_parent() const { return parent; }

		const std::map<std::string, std::shared_ptr<FileSystemObject>>& get_children() const { return children; }
};

#endif
