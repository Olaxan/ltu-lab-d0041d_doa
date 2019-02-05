#pragma once

#include <string>

namespace efiilj
{

	template <typename T>
	class SortedArray
	{
	private:
		T* _items;
		int _count;

		void addAt(int index, T value);
		void remAt(int index);
		T getAt(int index);

		void resize(int newSize);

	public:

		SortedArray();

		//Comparator determines manner of sorting the array.
		//Should return 'true' if left-hand is greater than right-hand.
		//Use for data types where custom comparison is necessary.
		bool(*comparator)(T a, T b) = [](T a, T b) -> bool { return a > b; };

		//Default: false - items in ascending order.
		bool descending = false;

		int	find(T value);
		bool exists(T value);
		void insert(T value);
		void remove(T value);

		std::string to_string();

		int count();

		~SortedArray() { delete[] _items; }

	};

}

#include "sarray_impl.h"

