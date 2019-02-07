#include "pch.h"
#include "menu.h"
#include "uinput.h"
#include "database.h"

#include <iostream>
#include <string>
#include <chrono>

using namespace std::chrono;

//IDatabase* db = new ArrayDB();
IDatabase* db = new LinkedListDB();
high_resolution_clock::time_point t1, t2;


bool MenuAddStudent()
{
	efiilj::UserInput<std::string> input = efiilj::UserInput<std::string>("Enter student name", "> ");
	input.exit = "c";

	if (input.Show())
	{
		t1 = high_resolution_clock::now();
		db->AddStudent(input.Value());
		t2 = high_resolution_clock::now();
		std::cout << "\nAdded student successfully in " << duration_cast<microseconds>(t2 - t1).count() << "MS.\n";
	}

	return false;
}

bool MenuRemoveStudent()
{
	if (db->CountStudents() > 0)
	{
		db->ShowStudents();

		efiilj::UserInput<int> input = efiilj::UserInput<int>("Enter student ID", "> ", 0, db->CountStudents() - 1);
		input.exit = "c";

		if (input.Show())
		{
			t1 = high_resolution_clock::now();
			if (db->RemoveStudent(input.Value()))
			{
				t2 = high_resolution_clock::now();
				std::cout << "\nRemoved successfully in " << duration_cast<microseconds>(t2 - t1).count() << "MS.\n";
			}
			else
				std::cout << "\nCould not remove student.\n";
		}
	}
	else
		std::cout << "No students in database.\n";

	return false;
}

bool MenuAddCourseToStudent()
{
	if (db->CountStudents() > 0)
	{
		efiilj::UserInput<int> student = efiilj::UserInput<int>("Enter student ID", "> ", 0, db->CountStudents() - 1);
		efiilj::UserInput<std::string> course = efiilj::UserInput<std::string>("Enter course ID", "> ");
		student.exit = "c";
		course.exit = "c";

		db->ShowStudents();

		if (student.Show())
		{
			db->ShowCourses();

			if (course.Show())
			{
				t1 = high_resolution_clock::now();
				if (db->AddCourseToStudent(student.Value(), db->GetCourse(course.Value())))
				{
					t2 = high_resolution_clock::now();
					std::cout << "\nAdded course successfully in " << duration_cast<microseconds>(t2 - t1).count() << "MS.\n";
				}
				else
					std::cout << "\nCould not add course.\n";
			}
		}
	}
	else
		std::cout << "No students in database.\n";

	return false;
}

bool MenuRemoveCourseFromStudent()
{
	if (db->CountStudents() > 0)
	{
		efiilj::UserInput<int> student = efiilj::UserInput<int>("Enter student ID", "> ", 0, db->CountStudents() - 1);
		efiilj::UserInput<std::string> course = efiilj::UserInput<std::string>("Enter course ID", "> ");
		student.exit = "c";
		course.exit = "c";

		db->ShowStudents();

		if (db->CountStudents() && student.Show())
		{
			db->ShowCourses();

			if (course.Show())
			{
				t1 = high_resolution_clock::now();
				if (db->RemoveCourseFromStudent(student.Value(), db->GetCourse(course.Value())))
				{
					t2 = high_resolution_clock::now();
					std::cout << "\nRemoved course successfully in " << duration_cast<microseconds>(t2 - t1).count() << "MS.\n";
				}
				else
					std::cout << "\nCould not remove course.\n";
			}
		}
	}
	else
		std::cout << "No students in database.\n";

	return false;
}

bool MenuShowStudents()
{
	if (db->CountStudents() > 0)
		db->ShowStudents();
	else
		std::cout << "No students in database.\n";

	return false;
}

bool MenuAddCourse()
{
	efiilj::UserInput<std::string> course = efiilj::UserInput<std::string>("Enter course name", "> ");
	course.exit = "c";

	if (course.Show())
	{
		t1 = high_resolution_clock::now();
		db->AddCourse(new Course(course.Value()));
		t2 = high_resolution_clock::now();
		std::cout << "\nAdded course successfully in " << duration_cast<microseconds>(t2 - t1).count() << "MS.\n";
		
	}

	return false;
}

bool MenuRemoveCourse()
{
	if (db->CountCourses() > 0)
	{
		db->ShowCourses();

		efiilj::UserInput<std::string> course = efiilj::UserInput<std::string>("Enter course name", "> ");
		course.exit = "c";

		if (course.Show())
		{
			t1 = high_resolution_clock::now();
			if (db->RemoveCourse(db->GetCourse(course.Value())))
			{
				t2 = high_resolution_clock::now();
				std::cout << "\nRemoved course successfully in " << duration_cast<microseconds>(t2 - t1).count() << "MS.\n";
			}
			else
				std::cout << "\nCould not remove course.\n";
		}
	}
	else
		std::cout << "No courses in database.\n";

	return false;
}

bool MenuShowCourses()
{
	if (db->CountCourses() > 0)
		db->ShowCourses();
	else
		std::cout << "No courses in database.\n";

	return false;
}

int main()
{
	efiilj::Menu main = efiilj::Menu("=== MAIN MENU");
	efiilj::Menu student = efiilj::Menu("=== STUDENT OPERATIONS");

	main.AddItem("Add new course", MenuAddCourse);
	main.AddItem("Remove course", MenuRemoveCourse);
	main.AddItem("Show courses", MenuShowCourses);
	main.AddItem("Edit students", &student);

	student.AddItem("Add new student", MenuAddStudent);
	student.AddItem("Remove student", MenuRemoveStudent);
	student.AddItem("Show students", MenuShowStudents);
	student.AddItem("Add course to student", MenuAddCourseToStudent);
	student.AddItem("Remove course from student", MenuRemoveCourseFromStudent);

	main.Show();

	delete db;
}