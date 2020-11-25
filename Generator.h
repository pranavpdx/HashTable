#pragma once
#include <unordered_map>
#include "Student.h";

using namespace std;
class Generator
{
public:
	Generator();
	// id ticker so random generator can create an ID for students in increasing order
	int idstart = 0;
	// vector that holds the first and last names of students from file
	vector<char*> firstNames;
	vector<char*> lastNames;
	// reads files to store first and last names
	void ReadFirst();
	void ReadLast();
	// prints first and last names -- used to debug
	void printFirst();
	void printLast();
	// generates a random student using first and last name vectors, increasing ID, and random GPA
	Student* GetRandomStudent(vector<int> &vect);
	// makes sure ID doesn;t already exist when creating random students
	bool checkID(int id, vector<int> vect);
	// hashfunction that generates key
	int hashFunction(char* name, int size);
};

