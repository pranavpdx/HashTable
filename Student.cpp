#include "Student.h"
#include <cstring>
#pragma warning(disable : 4996)
void Student::setFirst(char* first1) {
	first = new char[strlen(first1) + 1];
	strcpy(first, first1);
}

void Student::setLast(char* first1) {
	last = new char[strlen(first1) + 1];
	strcpy(last, first1);
}