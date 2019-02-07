#pragma once

#include <string>

namespace efiilj
{

	template <typename T>
	class DoublyLinkedList
	{
	private:

		struct Node
		{
			Node(T val) { _value = val; };
			Node* _next = nullptr;
			Node* _prev = nullptr;
			T _value;
		};

		Node* _head = nullptr;
		Node* _tail = nullptr;

		int _count = 0;

	public:

		DoublyLinkedList();

		Node* Head() const { return _head; };
		Node* Tail() const { return _tail; };
		
		void Insert(T val);
		bool Remove(int index);
		bool Remove(T val);
		T Get(int index) const;

		std::string ToString() const;
		int Count() const { return _count; };

		Node* GetNode(T val) const;
		Node* GetNode(int index) const;
		void RemoveNode(Node* node);
		
		T operator [] (int index) const { return Get(index); }

		~DoublyLinkedList();
	};

}

#include "lnklist_d_impl.h"


