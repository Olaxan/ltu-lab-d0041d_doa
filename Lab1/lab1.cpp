// Lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include "..\DSLib\lnklist_d.h"
#include "menu.h"

#include <iostream>

bool addRecord()
{
	return false;
}

bool removeRecord()
{
	return false;
}

bool addCourse()
{
	return false;
}

bool removeCourse()
{
	return false;
}


int main()
{
	efiilj::Menu main = efiilj::Menu("Student record manager 2000");
	main.AddItem("Add student record", addRecord);
	main.AddItem("Remove student record", removeRecord);
	main.AddItem("Add course to student", addCourse);
	main.AddItem("Remove course from student", removeRecord);
}

