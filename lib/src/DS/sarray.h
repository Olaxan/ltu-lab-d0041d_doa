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

		void AddAt(int index, T value);
		void RemoveAt(int index);
		T GetAt(int index) const;

		void Resize(int newSize);

	public:

		SortedArray();

		//Comparator determines manner of sorting the array.
		//Should return 'true' if left-hand is greater than right-hand.
		//Use for data types where custom comparison is necessary.
		bool(*Comparator)(T a, T b) = [](T a, T b) -> bool { return a > b; };

		//Default: false - items in ascending order.
		bool descending = false;

		int	Find(T value) const;
		bool Exists(T value) const;
		void Insert(T value);
		void Remove(T value);
		void Remove(int index);

		std::string ToString() const;
		int Count() const;

		T operator [] (int index) const { return GetAt(index); }

		~SortedArray() { delete[] _items; }

	};

}

//Include template implementation file (for organization purposes).
#include "sarray_impl.h"

