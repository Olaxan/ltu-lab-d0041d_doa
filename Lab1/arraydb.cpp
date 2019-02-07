#include "pch.h"
#include "database.h"


ArrayDB::ArrayDB() { }

void ArrayDB::AddStudent(std::string name)
{
	students.Insert(new Student(name));
}

bool ArrayDB::RemoveStudent(int id)
{
	if (id >= 0 && id < CountStudents())
	{
		delete students[id];
		students.Remove(id);
		return true;
	}
	return false;
}

bool ArrayDB::AddCourseToStudent(int id, Course* course)
{
	if (id >= 0 && id < CountStudents() && course != nullptr)
	{
		students[id]->courses.Insert(course);
		return true;
	}

	return false;
}

bool ArrayDB::RemoveCourseFromStudent(int id, Course* course)
{
	int c = CountStudents();
	if (course != nullptr)
		students[id]->courses.Remove(course);
	return c > CountStudents();
}


void ArrayDB::ShowStudents()
{
	for (int i = 0; i < students.Count(); i++)
	{
		std::cout << students[i]->name << ", ID: " << i << " [";
		for (int j = 0; j < students[i]->courses.Count(); j++)
		{
			std::cout << students[i]->courses[j]->name << (j < students[i]->courses.Count() - 1 ? ", " : "");
		}
		std::cout << "]\n";
	}
}

int ArrayDB::CountStudents()
{
	return students.Count();
}

void ArrayDB::AddCourse(Course* course)
{
	courses.Insert(course);
}

bool ArrayDB::RemoveCourse(Course* course)
{
	int c = CountCourses();

	if (course != nullptr)
	{
		for (int i = 0; i < students.Count(); i++)
		{
			RemoveCourseFromStudent(i, course);
		}

		courses.Remove(course);
	}

	return c > CountCourses();
}

Course* ArrayDB::GetCourse(std::string name)
{
	//Fix this
	for (int i = 0; i < courses.Count(); i++)
	{
		if (courses[i]->name == name)
			return courses[i];
	}

	return nullptr;
}

void ArrayDB::ShowCourses()
{
	for (int i = 0; i < courses.Count(); i++)
	{
		std::cout << courses[i]->name << (i < courses.Count() - 1 ? ", " : ".\n");
	}
}

int ArrayDB::CountCourses()
{
	return courses.Count();
}

ArrayDB::~ArrayDB()
{
	for (int i = 0; i < CountStudents(); i++)
	{
		delete students[i];
	}
}
