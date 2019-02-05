#pragma once

#include <string>

#include "lnklist_d.h"
#include "course.h"

class Student
{
public:
	Student(std::string name = "<N/A>");

	std::string name;
	
	efiilj::DoublyLinkedList<Course*> courses = efiilj::DoublyLinkedList<Course*>();

	~Student();
};

