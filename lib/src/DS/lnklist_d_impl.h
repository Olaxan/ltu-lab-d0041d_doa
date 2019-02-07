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

		if (_count > 0) //If the list isn't empty...
		{
			_head->_next = n; //The current head needs a next-pointer to new link...
			n->_prev = _head; //And the new link needs pointer to current head.
		}
		else
			_tail = n; //If the list is empty, the new link will also be the tail of the chain.

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

		for (int i = 0; i < _count; i++) //Iterate list until a match is found.
		{
			if (n->_value == val)
				return n;

			n = n->_prev;
		}

		return nullptr; //Return nullptr if no match is found.
	}

	template<typename T>
	typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::GetNode(int index) const
	{
		if (index < 0 || index > _count - 1) //Return nullptr if out of range; may be better to throw?
			return nullptr;
		else
		{
			Node* n = _head;

			for (int i = 0; i < index; i++) //Iterate to requested index and return node pointer.
			{
				n = n->_prev;
			}

			return n;
		}
	}

	template<typename T>
	inline void DoublyLinkedList<T>::RemoveNode(Node* node)
	{
		if (_count <= 1) //If the list is now empty, no tail and no head remains.
		{
			_head = nullptr;
			_tail = nullptr;
		}
		else
		{
			if (node == _head) //Assign a new head if this is the current head.
			{
				node->_prev->_next = nullptr;
				_head = node->_prev;
			}
			else if (node == _tail) //Assign a new tail if this is the current tail.
			{
				node->_next->_next = nullptr;
				_tail = node->_next;
			}
			else //Update neighbouring node pointers if this is in the middle of the chain.
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