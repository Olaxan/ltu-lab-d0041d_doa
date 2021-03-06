#include "pch.h"
#include "menu.h"
#include "uinput.h"
#include "database.h"

#include <iostream>
#include <string>
#include <chrono>

using namespace std::chrono;


/* ============ IMPLEMENTATION SELECT ============
Uncomment one of these to change style of database
implementation (array-based or linked-list-based).
================================================*/

//IDatabase* db = new ArrayDB();
IDatabase* db = new LinkedListDB();

high_resolution_clock::time_point t1, t2;


bool MenuAddStudent()
{
	///Ask user for a student name, and add it to database.
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
	///Ask user for student id (after displaying list of users), then remove the user if possible.
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
	///Ask user for a student id, and a course ID, then add the course to the student if possible.
	if (db->CountStudents() > 0 && db->CountCourses() > 0)
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
		std::cout << "No students/courses in database.\n";

	return false;
}

bool MenuRemoveCourseFromStudent()
{
	///Ask user for a student ID and a course to remove, then remove it if possible.
	if (db->CountStudents() > 0 && db->CountCourses() > 0)
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
		std::cout << "No students/courses in database.\n";

	return false;
}

bool MenuShowStudents()
{
	///Show a list of all students.
	if (db->CountStudents() > 0)
		db->ShowStudents();
	else
		std::cout << "No students in database.\n";

	return false;
}

bool MenuAddCourse()
{
	///Add a new course to the database.
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
	///Remove a course from the database.
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
	///Show a list of all courses.
	if (db->CountCourses() > 0)
		db->ShowCourses();
	else
		std::cout << "No courses in database.\n";

	return false;
}

bool MenuRandomize()
{
	t1 = high_resolution_clock::now();

	for (int i = 0; i < 50; i++)
	{
		db->AddCourse(new Course("COURSE" + std::to_string(i)));
	}

	for (int i = 0; i < 800; i++)
	{
		db->AddStudent("STUDENT" + std::to_string(i));

		for (int j = 0; j < rand() % 5 + 1; j++)
		{
			db->AddCourseToStudent(i, db->GetCourse("COURSE" + std::to_string(j)));
		}
	}

	t2 = high_resolution_clock::now();

	std::cout << "\nDataset populated in " << duration_cast<microseconds>(t2 - t1).count() << "MS.\n";
	std::cout << "NOTE: This feature was REALLY rushed, so it's not working super great.\n";

	return false;
}

int main()
{
	///Setup main and submenus, and show to user. When loop is exited, delete database.

	efiilj::Menu main = efiilj::Menu("=== MAIN MENU");
	efiilj::Menu course = efiilj::Menu("=== COURSE OPERATIONS");
	efiilj::Menu student = efiilj::Menu("=== STUDENT OPERATIONS");

	main.AddItem("Edit students", &student);
	main.AddItem("Edit courses", &course);
	main.AddItem("Random dataset", MenuRandomize);

	course.AddItem("Add new course", MenuAddCourse);
	course.AddItem("Remove course", MenuRemoveCourse);
	course.AddItem("Show courses", MenuShowCourses);

	student.AddItem("Add new student", MenuAddStudent);
	student.AddItem("Remove student", MenuRemoveStudent);
	student.AddItem("Show students", MenuShowStudents);
	student.AddItem("Add course to student", MenuAddCourseToStudent);
	student.AddItem("Remove course from student", MenuRemoveCourseFromStudent);

	main.Show();

	delete db;
}