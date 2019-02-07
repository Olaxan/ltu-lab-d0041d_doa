#include "pch.h"
#include "database.h"


LinkedListDB::LinkedListDB() { }

void LinkedListDB::AddStudent(std::string name)
{
	students.Insert(new Student(name));
}

bool LinkedListDB::RemoveStudent(int id)
{
	if (id >= 0 && id < CountStudents())
	{
		delete students[id];
		students.Remove(id);
		return true;
	}
	return false;
}

bool LinkedListDB::AddCourseToStudent(int id, Course * course)
{
	if (id >= 0 && id < CountStudents() && course != nullptr)
	{
		students[id]->courses.Insert(course);
		return true;
	}

	return false;
}

bool LinkedListDB::RemoveCourseFromStudent(int id, Course * course)
{
	int c = CountStudents();
	if (course != nullptr)
		students[id]->courses.Remove(course);
	return c > CountStudents();
}

void LinkedListDB::ShowStudents()
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

int LinkedListDB::CountStudents()
{
	return students.Count();
}

void LinkedListDB::AddCourse(Course * course)
{
	courses.Insert(course);
}

bool LinkedListDB::RemoveCourse(Course * course)
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

Course * LinkedListDB::GetCourse(std::string name)
{
	//Inefficiency.
	for (int i = 0; i < courses.Count(); i++)
	{
		if (courses[i]->name == name)
			return courses[i];
	}

	return nullptr;
}

void LinkedListDB::ShowCourses()
{
	for (int i = 0; i < courses.Count(); i++)
	{
		std::cout << courses[i]->name << (i < courses.Count() - 1 ? ", " : ".\n");
	}
}

int LinkedListDB::CountCourses()
{
	return courses.Count();
}

LinkedListDB::~LinkedListDB()
{
	for (int i = 0; i < CountStudents(); i++)
	{
		delete students[i];
	}
}