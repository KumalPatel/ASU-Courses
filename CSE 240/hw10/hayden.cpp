#include <string>
#include "hayden.h"
#include <iostream>

// Q2a: Define displayBook() for Hayden class (5 points)
// Define the function displayBook() that you declared within the Hayden class in the header file
// See expected output in question file.

// (displayList() function in hw10.cpp should call this function.)
// Include necessary header files

void Hayden::displayBook()
{
	cout << endl;
	cout << "Book name: " << Hayden::getName() << endl;
	cout << "Copies: " << Hayden::getCopies() << endl;
	cout << "Library: " << "Hayden" << endl;
	cout << endl;
}

