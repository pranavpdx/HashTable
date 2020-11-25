#include "Generator.h"
#include <iostream>
#include <fstream>
#include<string>
Generator::Generator() {
	ReadFirst();
	ReadLast();	
}

void Generator::ReadFirst() {
	FILE* pfile = NULL;
	char line[20];
	pfile = fopen("FirstNames.txt", "r");

	while (fgets(line, 20, pfile)) {
		char* pos = 0;
		if ((pos = strchr(line, '\n')) != NULL)
		{
			*pos = '\0';
		}
		char* firstname = new char[sizeof(line) + 1];
		memset(firstname, '\0', sizeof(firstname));
		strcpy(firstname, line);
		firstNames.push_back(firstname);
	}

}

Student* Generator::GetRandomStudent(vector<int> &vect){
	int randomFirst = rand() % 16;
	int randomLast = rand() % 14; 
	Student* student = new Student();
	student->first = firstNames.at(randomFirst);
	student->last = lastNames.at(randomLast);
	while (checkID(idstart, vect) == true) {
		idstart++;
	}
	student->id = idstart;
	vect.push_back(idstart);
	student->gpa = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 4.00));
	return student;
}
bool Generator::checkID(int id, vector<int> vect) {
	for (vector<int>::iterator it = vect.begin(); it != vect.end(); ++it) {
		if (*it == id) {
			return true;
		}
	}
	return false;
}
void Generator::ReadLast() {
	FILE* pfile = NULL;
	char line[20];
	pfile = fopen("LastNames.txt", "r");

	while (fgets(line, 20, pfile)) {
		char* pos = 0;
		if ((pos = strchr(line, '\n')) != NULL)
		{
			*pos = '\0';
		}
		char* lName = new char[sizeof(line) + 1];
		memset(lName, '\0', sizeof(lName));
		strcpy(lName, line);
		lastNames.push_back(lName);
	}

}

void Generator::printFirst() {
	for (vector<char*>::iterator it = firstNames.begin(); it != firstNames.end(); ++it) {
		cout << *it;
	}
}

void Generator::printLast() {
	for (vector<char*>::iterator it = lastNames.begin(); it != lastNames.end(); ++it) {
		cout << *it;
	}
}

int Generator::hashFunction(char* name, int hashsize) {
	int key = 0;
	int size = sizeof(name);
	for (int i = 0; i < size; i = i + 4) {
		key = key + (int)(*name + i);
	}

	key = key % hashsize;
	return key;
}