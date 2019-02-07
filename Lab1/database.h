#pragma once

#include "student.h"
#include "course.h"
#include "sarray.h"
#include "lnklist_d.h"

#include <string>

class IDatabase
{
public:
	virtual void AddStudent(std::string name) = 0;
	virtual bool RemoveStudent(int id) = 0;

	virtual bool AddCourseToStudent(int id, Course* course) = 0;
	virtual bool RemoveCourseFromStudent(int id, Course* course) = 0;

	virtual void ShowStudents() = 0;
	virtual int CountStudents() = 0;

	virtual void AddCourse(Course* course) = 0;
	virtual bool RemoveCourse(Course* course) = 0;
	virtual Course* GetCourse(std::string name) = 0;

	virtual void ShowCourses() = 0;
	virtual int CountCourses() = 0;

	virtual ~IDatabase() = 0 { };
};

class ArrayDB :
	public IDatabase
{
private:
	efiilj::SortedArray<Course*> courses = efiilj::SortedArray<Course*>();
	efiilj::SortedArray<Student*> students = efiilj::SortedArray<Student*>();

public:
	ArrayDB();

	void AddStudent(std::string name);
	bool RemoveStudent(int id);

	bool AddCourseToStudent(int id, Course* course);
	bool RemoveCourseFromStudent(int id, Course* course);

	void ShowStudents();
	int CountStudents();

	void AddCourse(Course* course);
	bool RemoveCourse(Course* course);
	Course* GetCourse(std::string name);

	void ShowCourses();
	int CountCourses();

	~ArrayDB();
};

class LinkedListDB :
	public IDatabase
{
private:
	efiilj::SortedArray<Course*> courses = efiilj::SortedArray<Course*>();
	efiilj::DoublyLinkedList<Student*> students = efiilj::DoublyLinkedList<Student*>();

public:
	LinkedListDB();

	void AddStudent(std::string name);
	bool RemoveStudent(int id);

	bool AddCourseToStudent(int id, Course* course);
	bool RemoveCourseFromStudent(int id, Course* course);

	void ShowStudents();
	int CountStudents();

	void AddCourse(Course* course);
	bool RemoveCourse(Course* course);
	Course* GetCourse(std::string name);

	void ShowCourses();
	int CountCourses();

	~LinkedListDB();
};


