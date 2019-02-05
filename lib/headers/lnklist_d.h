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
		void Remove(int index);

		std::string ToString();
		int Count() const { return _count; };

		Node* Find(T val);
		Node* GetNode(int index);
		T Get(int index);
		
		//TODO: operators

		~DoublyLinkedList();
	};

}

#include "lnklist_d_impl.h"


