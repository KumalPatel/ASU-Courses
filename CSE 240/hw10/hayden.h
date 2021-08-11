#ifndef _HAYDEN_H
#define _HAYDEN_H
#include "book.h"
// Q1a: Create Hayden class (5 points)
// Part 1: Create a child class of the Book class named 'Hayden'

// Part2: Declare constructor which accepts the same 3 parameters as the parent class Book's constructor.
// Pass the 3 parameters to the super constructor of the Book class.

// Part 3: Re-declare the method displayBook (virtual method found inside of parent class Book)

class Hayden : public Book {
public:
	Hayden(string bookName, int noOfCopies, libraryType libType) : Book(bookName, noOfCopies, libType) {};
	virtual void displayBook();
};

#endif // _HAYDEN_H