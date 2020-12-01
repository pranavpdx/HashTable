#pragma once
class Student
{
public:
	// variables of student
	char* first = new char();
	char* last = new char();
	float gpa;
	int id;
	Student* next;
	// functions of student
	void setFirst(char* first);
	void setLast(char* last);
};

