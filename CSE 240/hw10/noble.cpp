#include <iostream>
#include <string>
#include "noble.h"
// Q2b: Define displayBook() for Noble class (5 points)
// Define the function displayBook() that you declared within the Noble class in the header file
// See expected output in question file.

// (displayList() function in hw10.cpp should call this function.)
// Include necessary header files

using namespace std;

void Noble::displayBook()
{
	cout << endl;
	cout << "Book name: " << Noble::getName() << endl;
	cout << "Copies: " << Noble::getCopies() << endl;
	cout << "Library: " << "Noble" << endl;
	cout << endl;
}