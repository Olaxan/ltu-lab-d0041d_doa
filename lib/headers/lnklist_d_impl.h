#include "lnklist_d.h"

#include <sstream>
#include <iostream>

namespace efiilj
{

	template <typename T>
	DoublyLinkedList<T>::DoublyLinkedList() { }

	template<typename T>
	void DoublyLinkedList<T>::Insert(T val)
	{
		Node* n = new Node(val);

		if (_count > 0)
		{
			_head->_next = n;
			n->_prev = _head;
		}
		else
			_tail = n;

		_head = n;
		
		_count++;
	}

	template<typename T>
	bool DoublyLinkedList<T>::Remove(int index)
	{
		Node* n = GetNode(index);

		if (n != nullptr)
		{
			RemoveNode(n);
			_count--;
			return true;
		}

		return false;
	}

	template<typename T>
	bool DoublyLinkedList<T>::Remove(T val)
	{
		Node* n = GetNode(val);
		if (n != nullptr)
		{
			RemoveNode(n);
			_count--;
			return true;
		}
		return false;
	}

	template<typename T>
	std::string DoublyLinkedList<T>::ToString() const
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
	typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::GetNode(T val) const
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
	typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::GetNode(int index) const
	{
		if (index < 0 || index > _count - 1)
			return nullptr;
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

	template<typename T>
	inline void DoublyLinkedList<T>::RemoveNode(Node* node)
	{
		if (_count <= 1)
		{
			_head = nullptr;
			_tail = nullptr;
		}
		else
		{
			if (node == _head)
			{
				node->_prev->_next = nullptr;
				_head = node->_prev;
			}
			else if (node == _tail)
			{
				node->_next->_next = nullptr;
				_tail = node->_next;
			}
			else
			{
				node->_next->_prev = node->_prev;
				node->_prev->_next = node->_next;
			}
		}

		delete node;
	}

	template<typename T>
	T DoublyLinkedList<T>::Get(int index) const
	{
		return GetNode(index)->_value;
	}

	template <typename T>
	DoublyLinkedList<T>::~DoublyLinkedList() { }

}