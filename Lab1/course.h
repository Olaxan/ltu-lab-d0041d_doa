#pragma once

#include <string>

class Course
{
public:
	Course(std::string name = "<N/A>");

	std::string name;
	float credit;
	int grade;

	~Course();
};

