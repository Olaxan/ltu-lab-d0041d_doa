#pragma once

#include <algorithm>
#include <sstream>
#include <iostream>
#include "sarray.h"

namespace efiilj
{
	template <typename T>
	SortedArray<T>::SortedArray()
	{
		_items = new T[0];
		_count = 0;
	}

	template <typename T>
	void SortedArray<T>::AddAt(int index, T value)
	{
		///Expand array by one, and move existing elements as required. Then, add new element.
		Resize(_count + 1);
		memmove(_items + index + 1, _items + index, sizeof(T) * (_count - index));
		_items[index] = value;
		_count++;
	}

	template <typename T>
	void SortedArray<T>::RemoveAt(int index)
	{
		///Shift elements to cover deleted element.
		memmove(_items + index, _items + index + 1, sizeof(T) * (_count - index));
		_count--;
	}

	template <typename T>
	T SortedArray<T>::GetAt(int index) const
	{
		return _items[index];
	}

	template <typename T>
	void SortedArray<T>::Resize(int newSize)
	{
		///Create a new array of requsted size, and copy elements over from old array.
		T* _new = new T[newSize];
		memcpy_s(_new, newSize * sizeof(T), _items, _count * sizeof(T));
		delete[] _items;
		_items = _new;
	}

	template <typename T>
	int SortedArray<T>::Find(T value) const
	{
		///Find element in array by value, and return index.

		int upper = _count - 1;
		int lower = 0;
		int mid;

		//Binary search
		while (lower <= upper)
		{
			mid = (lower + upper) / 2;

			if (_items[mid] == value)
				return mid;

			if (descending ^ Comparator(value, _items[mid])) //XOR to invert result if "descending" is set.
				lower = mid + 1;
			else
				upper = mid - 1;
		}

		return -1;
	}

	template <typename T>
	bool SortedArray<T>::Exists(T value) const
	{
		return (Find(value) != -1);
	}

	template <typename T>
	void SortedArray<T>::Insert(T value)
	{
		//TODO: This could use binary search for efficiency.
		for (int i = 0; i < _count; i++)
		{
			if (descending ^ Comparator(_items[i], value))
			{
				AddAt(i, value);
				return;
			}
		}
		AddAt(_count, value);
	}

	template <typename T>
	void SortedArray<T>::Remove(T value)
	{
		///Go through array and remove matching elements.
		//TODO: Pass-by-reference, implement binary search.

		for (int i = 0; i < _count;)
		{
			if (_items[i] == value)
				RemoveAt(i);
			else
				i++;
		}
	}

	template<typename T>
	inline void SortedArray<T>::Remove(int index)
	{
		Remove(GetAt(index));
	}

	template <typename T>
	std::string SortedArray<T>::ToString() const
	{
		std::stringstream ss;
		ss << "[";

		for (int i = 0; i < _count; i++)
		{
			ss << _items[i];
			if (i < _count - 1)
				ss << ", ";
		}

		ss << "]";

		return ss.str();
	}

	template <typename T>
	int SortedArray<T>::Count() const
	{
		return _count;
	}
}