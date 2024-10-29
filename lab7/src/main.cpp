#include <iostream>

#include "../include/Vector.h"

int main()
{
    Vector<int> my_vector; 

	int choice;
    int n, value, index;

    do {
        std::cout << "Выберите действие:" << std::endl;
        std::cout << "\t1. Создание пустого вектора на n элементов." << std::endl;
        std::cout << "\t2. Проверка, пустой ли вектор." << std::endl;
        std::cout << "\t3. Получить размер вектора." << std::endl;
        std::cout << "\t4. Получение произвольного элемента." << std::endl;
        std::cout << "\t5. Изменение размера вектора." << std::endl;
        std::cout << "\t6. Добавление нового элемента в конец вектора." << std::endl;
        std::cout << "\t7. Удаление последнего элемента из вектора." << std::endl;
		std::cout << "\t8. Вывод вектора." << std::endl;
		std::cout << "\t9. Обход вектора." << std::endl;
		std::cout << "\t10. Выход." << std::endl;

        std::cout << "Ваш выбор: ";
        std::cin >> choice;
		switch (choice) {
            case 1:
                std::cout << "Введите начальную вместимость (n): ";
                std::cin >> n;
                my_vector = Vector<int>(n);
				std::cout << "Создан вектор с вместимостью: " << n << std::endl;
                break;

            case 2:
                std::cout << "Вектор " << (my_vector.is_empty() ? "пустой." : "не пустой.") << std::endl;
                break;

            case 3:
                std::cout << "Размер вектора: " << my_vector.get_size() << std::endl;
                break;

			case 4:
                std::cout << "Введите индекс элемента: ";
                std::cin >> index;
                std::cout << "Элемент: " << my_vector[index] << std::endl; 
                break;

            case 5:
                std::cout << "Введите новую вместимость вектора: ";
                std::cin >> n;
                my_vector.resize(n);
                std::cout << "Вместимость вектора изменена на: " << n << std::endl;
                break;

            case 6:
                std::cout << "Введите значение для добавления: ";
                std::cin >> value;
                my_vector.push_back(value);
                std::cout << "Добавлено значение: " << value << std::endl;
                break;
			
			case 7:
                my_vector.pop_back();
                std::cout << "Последний элемент удален." << std::endl;
                break;

			case 8:
				std::cout << my_vector;
				break;

			case 9:
				std::cout << "Элементы вектора: ";
				for (auto& el : my_vector)
					std::cout << el << " ";
				std::cout << std::endl;
				break;

            case 10:
                std::cout << "Выход из программы." << std::endl;
                break;

            default:
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
                break;
        }
    } while (choice != 10);

    return 0;
}
