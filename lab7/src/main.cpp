#include <iostream>

#include "../include/Vector.h"

int main()
{
    Vector<int> my_vector; 

	int choice;
    int n, value, index;

    do {
        std::cout << "Выберите действие:" << std::endl;
        std::cout << "\t1. Создание пустого вектора на n элементов" << std::endl;
        std::cout << "\t2. Проверка, пустой ли вектор" << std::endl;
        std::cout << "\t3. Получить размер вектора" << std::endl;
        std::cout << "\t4. Получение произвольного элемента" << std::endl;
        std::cout << "\t5. Изменение размера вектора" << std::endl;
        std::cout << "\t6. Добавление нового элемента в конец вектора" << std::endl;
        std::cout << "\t7. Удаление последнего элемента из вектора" << std::endl;
		std::cout << "\t0. Выход" << std::endl;

        std::cout << "Ваш выбор: ";
        std::cin >> choice;
		switch (choice) {
            case 1:
                std::cout << "Введите начальную вместимость (n): ";
                std::cin >> n;
                my_vector = Vector<int>(n); // Создаем новый вектор
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
                try {
                    std::cout << "Элемент: " << my_vector[index] << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cout << e.what() << std::endl;
                }
                break;

            case 5:
                std::cout << "Введите новую вместимость вектора: ";
                std::cin >> n;
                // Этот вариант нужно реализовать в вашем классе
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
                try {
                    my_vector.pop_back();
                    std::cout << "Последний элемент удален." << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cout << e.what() << std::endl;
                }
                break;

            case 0:
                std::cout << "Выход из программы." << std::endl;
                break;

            default:
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
