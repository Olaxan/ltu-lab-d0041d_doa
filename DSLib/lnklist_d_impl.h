#include "lnklist_d.h"

#include <stdexcept>
#include <sstream>
#include <iostream>

namespace efiilj
{
	template<typename T>
	typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::GetNode(int index)
	{
		if (index < 0 || index > _count - 1)
			throw std::out_of_range("Linked list index out of range");
		else
		{
			Node* n = _head;

			for (int i = 0; i < index; i++)
			{
				n = n->_prev;
			}

			return n;
		}
	}

	template <typename T>
	DoublyLinkedList<T>::DoublyLinkedList()
	{

	}

	template<typename T>
	void DoublyLinkedList<T>::Insert(T val)
	{
		Node* n = new Node(val);

		if (_head != nullptr)
		{
			_head->_next = n;
			n->_prev = _head;
		}

		_head = n;
		
		_count++;
	}

	template<typename T>
	void DoublyLinkedList<T>::Remove(int index)
	{
		_count--;

		Node* n = GetNode(index);

		if (n == _head)
		{
			n->_prev->_next = nullptr;
			_head = n->_prev;
		}
		else if (n == _tail)
		{
			n->_next->_next = nullptr;
			_tail = n->_next;
		}
		else
		{
			n->_next->_prev = n->_prev;
			n->_prev->_next = n->_next;
		}

		delete n;
	}

	template<typename T>
	std::string DoublyLinkedList<T>::ToString()
	{
		std::stringstream ss;

		for (int i = 0; i < _count - 1; i++)
		{
			ss << Get(i) << ", ";
		}
		ss << Get(_count - 1);

		return ss.str();
	}

	template<typename T>
	typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::Find(T val)
	{
		Node* n = _head;

		for (int i = 0; i < _count; i++)
		{
			if (n->_value == val)
				return n;
		}

		return nullptr;
	}

	template<typename T>
	T DoublyLinkedList<T>::Get(int index)
	{
		return GetNode(index)->_value;
	}

	template <typename T>
	DoublyLinkedList<T>::~DoublyLinkedList()
	{
	}

}