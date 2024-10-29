#ifndef VECTOR_H
#define VECTOR_H

#include "Constants.h"

template <typename T> 
class Vector
{
	private:
		T* data;	
		int size;
		int capacity;

		int amount_of_modifications;

	public:
		
		/*
		 * Изменение размера вектора
		 *
		 * @param temp_capacity временная переменная вместимости
		 */

		void resize(int temp_capacity)
		{
			T* temp_data = new T[temp_capacity];

			for (int i = 0; i < size; i++)
				temp_data[i] = data[i];
				
			delete [] data;
			data = temp_data;
			capacity = temp_capacity;
		}

		/*
		 * Конструктор класса
		 *
		 * @param initial_capacity начальная емкость вектора
		 */

		Vector(int initial_capacity = Constants::initial_capacity)
		:
			size(Constants::initial_size),
			capacity(initial_capacity),
			amount_of_modifications(Constants::amount_of_modifications)
		{
			data = new T[capacity];	
		}
	
		/*
		 * Деструктор класса
		 *
		 */

		~Vector()
		{
			delete [] data;
		}

		/*
		 * Проверка на пустоту вектора
		 *
		 * @return возвращает правду, если пуст, иначе - ложь
		 */
		
		bool is_empty() const
		{
			return size == 0;
		}

		/*
		 * Получение размера вектора
		 *
		 * @return возвращает размер вектора
		 */

		int get_size() const
		{
			return size;
		}

		/*
		 * Получение элемента по его индексу через перегруженный оператор []
		 *
		 * @param index индекс вектора
		 *
		 * @return возвращает элемент вектора
		 */

		T& operator[](int index)
		{
			if (index < 0 || index >= size)
			{
				std::cout << "Выход за пределы вектора." << std::endl;
				exit(EXIT_FAILURE);
			}

			return data[index];
		}

		/*
		 * Добавление элемента в конец вектора
		 *
		 * @param value число, которое добавится в вектор
		 */

		void push_back(const T& value)
		{
			if (size == capacity)
				resize(capacity * 2);

			data[size++] = value;

			amount_of_modifications++;
			if (amount_of_modifications >= Constants::resize_threshold)
			{
				resize(capacity * 2);
				amount_of_modifications = 0;
			}
		}

		/*
		 * Удаление последнего элемента из вектора
		 *
		 */

		void pop_back()
		{
			if (is_empty())
			{
				std::cout << "Вектор пуст." << std::endl;
				return;
			}

			size--;

			if (size <= (capacity / 4))
				resize(capacity / 2);

		}

		/*
		 * Отображение всех элементов вектора
		 *
		 * @param os поток, куда записывается вывод
		 * @param v вектор
		 *
		 * @return возвращает поток вывода
		 */

		friend std::ostream &operator<<(std::ostream &os, const Vector<T>& v)
		{
			os << "Вектор " << "{";
			for (int i = 0; i < v.size; i++)
			{
				os << v.data[i];
				if (i < v.size - 1) os << ", ";
			}
			os << "}" << std::endl;
			return os;
		}

		class Iterator
		{
			private:
				T* pointer;

			public:
				/*
				 * Конструктор класса
				 *
				 * @param p указатель на текущий элемент
				 */

				Iterator(T* p) : pointer(p) {}

				/*
				 * Перегрузка оператора *
				 *
				 * @return возвращает текущий элемент
				 */
				 
				T& operator*()
				{
					return *pointer;
				}

				/*
				 * Перегрузка оператора ++
				 *
				 * @return возвращает следующий элемент
				 */

				Iterator &operator++()
				{
					pointer++;
					return *this;
				}

				/*
				 * Перегрузка оператора !=
				 *
				 * @param it другой элемент
				 *
				 * @return возвращает правду, если не равны, иначе - ложь
				 */

				bool operator!=(const Iterator &it) const
				{
					return pointer != it.pointer;
				}
		};

		/*
		 * Итератор, указывающий на начало вектора
		 *
		 * @return возвращает итератор начала вектора
		 */
		 
		Iterator begin()
		{
			return Iterator(data);
		}

		/*
		 * Итератор, указывающий на конец вектора
		 *
		 * @return возвращает итератор конца вектора
		 */

		Iterator end()
		{
			return Iterator(data + size);
		}
};

#endif
