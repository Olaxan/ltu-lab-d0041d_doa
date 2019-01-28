// Lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include "..\DSLib\lnklist_d.h"

#include <iostream>

int main()
{
	efiilj::DoublyLinkedList<float> list = efiilj::DoublyLinkedList<float>();

	list.Insert(0.1f);
	list.Insert(0.2f);
	list.Insert(0.3f);
	list.Insert(0.4f);
	list.Remove(0);
	list.Remove(0);

	std::cout << list.ToString();
}

