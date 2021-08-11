// CSE240 Spring 2019 HW9
// Name: Kumal Patel
// Compiler: Visual Studio

// READ BEFORE YOU START:
// You are given a partially completed program which consist of a class 'Student' defined in student.h
// The definitions of class member functions are to be filled in student.cpp
// hw09q1.c (this file) creates an array of objects 's[]' and uses a menu driven program to add a stuent, display student info,
// sort the student list and to find the newest student(by enrollment year).
// You should start completing the program from from Q1. Question numbers are given around line 33.
// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// If you modify any of the given code, the return types, or the parameters, you risk getting compile error.
// You are not allowed to modify main ().

// ***** WRITE COMMENTS FOR IMPORANT STEPS OF YOUR CODE. *****
// ***** GIVE MEANINGFUL NAMES TO VARIABLES. *****

#include "student.h"
#include <iostream>
#include <string>

#define MAX_STUDENTS 5

using namespace std;

// forward declaration of functions (already implmented)
void executeAction(char);

// functions that need implementation:
// in student.cpp :
// Q1 Student constructor		// 2 points
// Q2 Student member functions // 18 points

// in this file (hw09q1.cpp) : Q3 to Q6
int addStudent(string name_input, float gpa_input, int enrollYear_input, int rollNumber_input); // 10 points
void displayStudents();				// 5 points
void sort();						// 10 points
void studentsAfterGivenYear();		// 5 points


Student s[MAX_STUDENTS];		// array of objects
int currentCount = 0;				// number of students in the list


int main()
{
	char choice = 'i';		// initialized to a dummy value
	do
	{
		cout<<"\nCSE240 HW9\n";
		cout << "Please select an action:\n";
		cout << "\t a: add a new student\n";
		cout << "\t d: display student list\n";
		cout << "\t s: sort the students by GPA\n";
		cout << "\t n: display students enrolled after given year\n";
		cout << "\t q: quit\n";
		cin >> choice;
		cin.ignore();			// ignores the trailing \n
		executeAction(choice);
	} while (choice != 'q');

	return 0;
}


// Ask for details from user for the given selection and perform that action
// Read the function case by case
void executeAction(char c)
{
	string name_input;
	float gpa_input;
	int enrollYear_input, rollNumber_input, result = 0;

	switch (c)
	{
	case 'a':	// add student
				// input student details from user
		cout << "Please enter student name: ";
		getline(cin, name_input);
		cout << "Please enter GPA: ";
		cin >> gpa_input;
		cin.ignore();
		cout << "Please enter enrollment year: ";
		cin >> enrollYear_input;
		cin.ignore();
		cout << "Please enter roll number: ";
		cin >> rollNumber_input;
		cin.ignore();

		// add the student to the list
		result = addStudent(name_input, gpa_input, enrollYear_input, rollNumber_input);
		if (result == 0)
			cout<<"\nThat student is already in the list or list is full! \n\n";
		else
			cout << "\nStudent successfully added to the list! \n\n";
		break;

	case 'd':		// display the list
		displayStudents();
		break;

	case 's':		// sort the list
		sort();
		break;

	case 'n':		// find and display newest student
		studentsAfterGivenYear();
		break;

	case 'q':		// quit
		break;

	default: cout << c <<" is invalid input!\n";
	}

}

// Q3 addStudent (10 points)
// This function adds a new student with the details given in function arguments.
// Add the student in 's' (array of objects) only if there is remaining capacity in the array and if the student does not already exist in the list
// This function returns 1 if the student is added successfully, else it returns 0 for the cases mentioned above.
// Assume user enters GPA in 0.0 - 4.0 range.
int addStudent(string name_input, float gpa_input, int enrollYear_input, int rollNumber_input)
{
	if (currentCount < MAX_STUDENTS) // check bounds of number of students
	{
		// search to see if student exists in the array
		for (int i = 0; i < currentCount; i++)
		{
			if (s[i].getName() == name_input && s[i].getGpa() == gpa_input && s[i].getEnrollYear() == enrollYear_input && s[i].getRollNumber() == rollNumber_input)
			{
				return 0; // if student exists
			}
		}
		// add student in the array
		for (int i = currentCount; i < MAX_STUDENTS; i++)
		{
			s[i] = Student(); // add student using constructor and set all releveant info
			s[i].setName(name_input);
			s[i].setGpa(gpa_input);
			s[i].setEnrollYear(enrollYear_input);
			s[i].setRollNumber(rollNumber_input);
		}
		currentCount++; // increment count
		return 1;
	}
		return 0; // if list is full
}

// Q4 displayStudents (5 points)
// This function displays the list of students.
// Parse the object array 's' and display the details of all students in the array. See expected output given in question file.
// You can call the class function 'displayStudent()' here. Note that these are two different functions.
// Student::displayStudent() displays details of one Student object, while displayStudents() should display all students
void displayStudents()
{
	for (int i = 0; i <= currentCount - 1; i++)
	{
		s[i].displayStudent(); // display info for each student
	}
}

// Q5 sort (10 points)
// This function sorts the students in descending order of GPA.
// You may use the 'temp' object for sorting logic, if needed.

void sort()
{
	// used insertion sort algorithim
	Student temp;
	int i, j;
	for (i = 1; i < currentCount; i++)
	{
		temp = s[i];
		j = i - 1;

		// move elements of s[0..i-1] that are less than temp to one position ahead
		while (j >= 0 && s[j].getGpa() < temp.getGpa())
		{
			s[j + 1] = s[j];
			j = j - 1;
		}
		s[j + 1] = temp;
	}
	cout << endl<< "Student list sorted! Use d option to see the sorted result."<< endl;
}

// Q6 studentsAfterGivenYear (5 points)
// This functions displays stduents enrolled after a given year. Ask the user for a year and store it in 'lowerBound'
// Parse the array to check if the student is enrolled in or after 'lowerBound' year.
// If the student is enrolled in or after 'lowerBound' year then copy that student's details (object's data members)
// to 'newStudent' object created using 'new' and display those student details using 'newStudent' object.
// Finally delete the 'newStudent' object.
// NOTE: You necessarily have to use the 'newStudent' object to store the student details in it and delete it after displaying.
//       You should not display student details using 'b[]' object.

void studentsAfterGivenYear()
{
	int lowerBound;	 // Ask the user for lower bound of enrollment year
	Student* newStudent = new Student;
	cout << "Enter the lower bound of enrollment year: ";
	cin >> lowerBound;

	// parse through the array to find which student contains enrollment year >= to lowerbound
	for(int i = 0; i < currentCount; i++)
	{
		if(s[i].getEnrollYear() >= lowerBound)
		{
			// copy s[i] info to newstudent 
			newStudent->setName(s[i].getName());
			newStudent->setGpa(s[i].getGpa());
			newStudent->setEnrollYear(s[i].getEnrollYear());
			newStudent->setRollNumber(s[i].getRollNumber());
			newStudent->displayStudent(); // display newstudent info
		}
	}
	delete newStudent;
}
