// HashTable.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Creates a student database using hastables!
// Author: Pranav Sharma
// Date: 11/25/20
#pragma warning(disable : 4996)
#include <iostream>
#include "Student.h"
#include "Generator.h"
#include <iomanip>
#include <vector>
#include <cstring>
using namespace std;
// main functions
bool askInfo(Student*& student, vector<int>& ids);
void add(Student* student, Student**& studentArray, int hashSize, Generator* generator);
void deleteStudent(int id, Student**& studentArray, int hashSize);
void print(Student**& studentArray, int hashSize);
void rehash(Student**& studentArray, int hashSize, Generator* generator);
int main()
{
	// variables
	Generator* generator = new Generator();
	int hashSize = 100;
	vector<int> ids;// stores the ids to make sure there are no repeats
	Student** studentArray = new Student * [hashSize];
	// initilizes array to make sure they are all NULL
	for (int i = 0; i < hashSize; i++) {
		studentArray[i] = NULL;
	}
	char* input = new char();
	bool playing = true;
	// runs while user inidctaes they would like to use program
	while (playing) {
		cout << "What would you like to do? (ADD, PRINT, DELETE, RANDOM, or QUIT)\n";
		cin.getline(input, 80, '\n');
		// if user adds to database...
		if (strcmp(input, "ADD") == 0) {
			//creates a student and asks for the stduents info
			Student* student = new Student();
			bool repeat = askInfo(student, ids);
			// if they enter a new ID, student gets added. If not, program alerts user and the student is deleted
			if (repeat == false) {
				add(student, studentArray, hashSize, generator);
			}
			else {
				cout << "Sorry! There is another student with this ID\n";
				delete student;
			}
		}
		// if user would like to delete...
		else if (strcmp(input, "DELETE") == 0) {
			int id;
			// asks for ID then deletes
			cout << "Which ID would you like to delete?\n";
			cin >> id;
			cin.get();
			deleteStudent(id, studentArray, hashSize);
		}
		// if user would like to print, all students are printed by key
		else if (strcmp(input, "PRINT") == 0) {
			print(studentArray, hashSize);
		}
		// if user wants to add random students... they enter the amount of students and random students are generated
		else if (strcmp(input, "RANDOM") == 0) {
			int num = 0;
			int start = 1;
			cout << "How many random students would you like to generate?\n";
			cin >> num;
			cin.get();
			while (start <= num) {
				add(generator->GetRandomStudent(ids), studentArray, hashSize, generator);
				start++;
			}
		}
		// if user wants to quit database the program ends
		else if (strcmp(input, "QUIT") == 0) {
			cout << "Thank you for playing!";
			playing = false;
		}
		//else they didn;t type a proper command... sad :(
		else {
			cout << "You did not enter a proper command :(\n";
		}
	}

}
// deletes students by looping through hashtable and through corresponding linked lists to find ID
void deleteStudent(int id, Student** &studentArray, int hashSize) {
	Student* ptr = NULL;
	Student* last = NULL;
	// loops through hashtable
	for (int i = 0; i < hashSize; i++) {
		if (studentArray[i] != NULL) {
			ptr = studentArray[i];
			// loops through linked list
			while (ptr != NULL) {
				if (ptr->id == id) {
					if (last != NULL) {
						// once ID is found, the node is skipped and deleted
						last->next = ptr->next;
						delete ptr;
						ptr = NULL;
					}
					else {
						// if the node to be deleted is the first in the linked list, the second node becomes and head and forst ndoe is deleted. 
						studentArray[i] = ptr->next;
						delete ptr;
						ptr = NULL;
					}
				}
				else {
					// moves to next node in linked list
					last = ptr;
					ptr = ptr->next;
				}
			}
		}
		// resets variables
		ptr = NULL;
		last = NULL;
	}
}
// prints all students
void print(Student** &studentArray, int hashSize) {
	// loops through hastab;e
	for (int i = 0; i < hashSize; i++) {
		Student* ptr = studentArray[i];
		// loops through linked list 
		while (ptr != NULL) {
			// prints each student and moves to next student in list
			cout << "Key: " << i << " Name: " << ptr->first << " " << ptr->last  << ", ID: " << ptr->id << ", GPA: " << fixed << setprecision(2) << ptr->gpa << endl;
			ptr = ptr->next;
		}

	}
}
// adds a student
void add(Student* student, Student** &studentArray, int hashSize, Generator* generator) {
	int count = 0;
	// gets a key that is generated by our hashfunction based on first name
	int key = generator->hashFunction(student->first, hashSize);
	// ptr1 is then assigned to whatever node is in thet spot int he hashtable
	Student* ptr1 = (studentArray)[key];
	// if that spot was empty, our student gets added to that spot
	if (ptr1 == NULL) {
		studentArray[key] = student;
	}
	// if its not empty, loops through key's linked list and gets added to the end
	else {
		while (ptr1->next != NULL) {
			count++;
			ptr1 = ptr1->next;
		}
		ptr1->next = student;
		student->next = NULL;
		// count = 1 if there are three students in the linkedlist... the table is then rehashed
		if (count == 1) {
			rehash(studentArray, hashSize, generator);
		}
	}
}
// function rehashes hashtable
void rehash(Student** &studentArray, int hashSize, Generator* generator) {
	// creates a temp array and sets it equal to hashtable
	Student** temp = new Student* [hashSize];
	for (int i = 0; i < hashSize; i++) {
		temp[i] = studentArray[i];
	}
	// hashsize multiplies by 2
	 hashSize = hashSize * 2;
	 // new hashtable is created and everything in it is set to NULL
	 studentArray = new Student* [hashSize];
	 for (int i = 0; i < hashSize; i++) {
		 studentArray[i] = NULL;
	 }
	 // adds everything in old hashtable to new hashtable
	 for (int i = 0; i < (hashSize/2); i++) {
		 if (temp[i] != NULL) {
			 add(temp[i], studentArray, hashSize, generator);
		 }
	 }
	 // old hashtable is deleted
	 delete temp;
}
// function akss info to fill in details for a student
bool askInfo(Student* &student, vector<int> &ids) {
	char input[20];
	cout << "Enter the student's first name: \n";
	cin >> input;
	student->setFirst(input);
	cout << "Enter the student's last name: \n";
	cin >> input;
	student->setLast(input);
	cout << "Enter the student's GPA: \n";
	cin >> student->gpa;
	cout << "Enter the student's ID: \n";
	cin >> student->id;
	cin.get();
	// if ID alread exists, returns true as in yes, there is a duplicate and this student won't be added to hashtable
	for (vector<int>::iterator it = ids.begin(); it != ids.end(); ++it) {
		if (*it == student->id) {
			return true;
		}
	}
	// else, adds to the vector of ids and returns false, as in no repeats
	ids.push_back(student->id);
	return false;
}


