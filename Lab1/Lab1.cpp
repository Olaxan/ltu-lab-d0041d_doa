#include "pch.h"
#include <iostream>
#include <string>

#include "menu.h"

bool MenuAddStudent()
{
	return false;
}

bool MenuRemoveStudent()
{
	return false;
}

bool MenuAddCourseToStudent()
{
	return false;
}

bool MenuRemoveCourseFromStudent()
{
	return false;
}

bool MenuAddCourse()
{
	return false;
}

bool MenuRemoveCourse()
{
	return false;
}

int main()
{
	efiilj::Menu main = efiilj::Menu("Main Menu");
	efiilj::Menu student = efiilj::Menu("Student operations");

	main.AddItem("Add new course", MenuAddCourse);
	main.AddItem("Remove course", MenuAddCourse);
	main.AddItem("Edit students", &student);

	student.AddItem("Add new student", MenuAddStudent);
	student.AddItem("Remove student", MenuRemoveStudent);
	student.AddItem("Add course to student", MenuAddCourseToStudent);
	student.AddItem("Remove course from student", MenuRemoveCourseFromStudent);

	main.Show();
}