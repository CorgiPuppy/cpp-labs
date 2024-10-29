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

	public:
		void resize(int temp_capacity)
		{
			T* temp_data = new T[temp_capacity];

			for (int i = 0; i < size; i++)
				temp_data[i] = data[i];
				
			delete [] data;
			data = temp_data;
			capacity = temp_capacity;
		}

		Vector()
		:
			size(Constants::initial_size),
			capacity(Constants::initial_capacity)
		{
			data = new T[capacity];	
		}
		
		~Vector()
		{
			delete [] data;
		}
		
		bool is_empty() const
		{
			return size == 0;
		}

		int get_size() const
		{
			return size;
		}

		T& operator[](int index)
		{
			if (index >= size)
				std::cout << "Выход за пределы вектора" << std::endl;

			return data[index];
		}

		void push_back(const T& value)
		{
			if (size == capacity)
				resize(capacity * 2);

			data[size++] = value;
		}

		void pop_back()
		{
			if (is_empty())
				std::cout << "Вектор пуст" << std::endl;

			--size;
		}

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
				Iterator(T* p) : pointer(p) {}

				T& operator*()
				{
					return *pointer;
				}

				Iterator &operator++()
				{
					pointer++;
					return *this;
				}

				bool operator!=(const Iterator &it) const
				{
					return pointer != it.pointer;
				}
		};

		Iterator begin()
		{
			return Iterator(data);
		}

		Iterator end()
		{
			return Iterator(data + size);
		}
};

#endif
