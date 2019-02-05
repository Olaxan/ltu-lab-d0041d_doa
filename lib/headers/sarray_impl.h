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
	void SortedArray<T>::addAt(int index, T value)
	{
		resize(_count + 1);
		memmove(_items + index + 1, _items + index, sizeof(T) * (_count - index));
		_items[index] = value;
		_count++;
	}

	template <typename T>
	void SortedArray<T>::remAt(int index)
	{
		memmove(_items + index, _items + index + 1, sizeof(T) * (_count - index));
		_count--;
	}

	template <typename T>
	T SortedArray<T>::getAt(int index)
	{
		return _items[index];
	}

	template <typename T>
	void SortedArray<T>::resize(int newSize)
	{
		T* _new = new T[newSize];
		memcpy_s(_new, newSize * sizeof(T), _items, _count * sizeof(T));
		delete[] _items;
		_items = _new;
	}

	template <typename T>
	int SortedArray<T>::find(T value)
	{
		int upper = _count - 1;
		int lower = 0;
		int mid;

		while (lower <= upper)
		{
			mid = (lower + upper) / 2;

			if (_items[mid] == value)
				return mid;

			if (descending ^ comparator(value, _items[mid]))
				lower = mid + 1;
			else
				upper = mid - 1;
		}

		return -1;
	}

	template <typename T>
	bool SortedArray<T>::exists(T value)
	{
		return (find(value) != -1);
	}

	template <typename T>
	void SortedArray<T>::insert(T value)
	{
		//TODO: This could use binary search for efficiency.
		for (int i = 0; i < _count; i++)
		{
			if (descending ^ comparator(_items[i], value))
			{
				addAt(i, value);
				return;
			}
		}
		addAt(_count, value);
	}

	template <typename T>
	void SortedArray<T>::remove(T value)
	{
		for (int i = 0; i < _count;)
		{
			if (_items[i] == value)
				remAt(i);
			else
				i++;
		}
	}

	template <typename T>
	std::string SortedArray<T>::to_string()
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
	int SortedArray<T>::count()
	{
		return _count;
	}
}