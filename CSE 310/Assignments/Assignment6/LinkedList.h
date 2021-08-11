//************************************************************************
// ASU CSE310 Assignment #6
// ASU ID: 1208493243
// Name: Kumal Patel
// Description: this is a linked list used to store arrival cities

#include <iostream>
#include <iomanip> //to format the output
#include <string>

using namespace std;

//struct ArrCity represents an arrival city information
struct ArrCity
{
   string arrCity;
   double price;
   struct ArrCity * next;
};

//class LinkedList will contains a linked list of arrival cities
class LinkedList
{
   private:
   struct ArrCity* head;

   public:
   LinkedList();
   ~LinkedList();
   ArrCity* getHead();
   bool isFound(string aCity);
   bool addArrCity(string aCity, double price);
   bool removeArrCity(string aCity);
   void printArrCityList();
};

//Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
   head = NULL;
}

//Destructor
//Before termination, the destructor is called to free the associated memory.
//It deletes all the ArrCitys including the head and finally prints the number
//of ArrCitys deleted by it.
LinkedList::~LinkedList()
{
	struct ArrCity* first = head;
	int cityCount = 0;

	while (first != NULL)
	{
		ArrCity* next = first->next;
		delete(first);
		first = next;
		cityCount++;
	}

	head = NULL;
	cout<< "The number of deleted arrival cities are: " << cityCount <<"\n";
}

//Accessor to the header of the linked list
ArrCity* LinkedList::getHead()
{
   return head;
}

//A function to check if the parameterized arrival city is
//inside the LinkedList or not. Return true if it exists and
//false otherwise.
bool LinkedList::isFound(string aCity)
{
	struct ArrCity* city = head;

	while (city != NULL)
	{
		if (city->arrCity == aCity)
			return true;
		city = city->next;
	}
	return false;
}

//Creates a new ArrCity and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of the ArrCitys
//while inserting it into the list. Note: you cannot insert duplicated ArrCitys
//Return value: true if it is successfully inserted and false otherwise
bool LinkedList::addArrCity(string aCity, double price)    /* NOT CHECKING DEPARTURE CITIES */
{
	struct ArrCity* city = head;
	struct ArrCity* newCity = new ArrCity();

	newCity->arrCity = aCity;
	newCity->price = price;
  newCity->next = NULL;

	if (head == NULL) // empty list
	{
		head = newCity;
		return true;
	}

  else if (newCity->arrCity.compare(head->arrCity) < 0) // new city is before current head, make new city head and next old head
  {
    newCity->next = head;
    head = newCity;
    return true;
  }

	while (city != NULL)
	{
    if (isFound(newCity->arrCity) == true) // duplicate city
        return false;

    if (city->next == NULL && newCity->arrCity.compare(city->arrCity) > 0) // new city must be greater then last node in the list, so insert at the end of the list
    {
      city->next = newCity;
      newCity->next = NULL;
      return true;
    }

    else if (newCity->arrCity.compare(city->next->arrCity) < 0) // new city is before current city, place new city before that current city
	{
		newCity->next = city->next;
		city->next = newCity;
		return true;
	}


		city = city->next;
	}
    return false; // if all other cases fail

}

//Removes the given ArrCity from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise.
bool LinkedList::removeArrCity(string aCity)
{
	struct ArrCity* city = head;
	struct ArrCity* temp = head;

  if(head == NULL) // not needed, but to prevent crashing. checks when list is empty
    return false;

	else if (head->arrCity == aCity) // delete head by setting head to next of list and deleted the old head
	{
		temp = head;
		head = temp->next;
		delete(temp);
		return true;
	}

	while (city != NULL)
	{
		if (city->next->arrCity == aCity) // delete city next by setting city next to the city next next
		{
			temp = city->next;
			city->next = temp->next;
			delete(temp);
			return true;
		}
		city = city->next;
	}
    return false;
}

//Prints all the arrival cities info. in the linked list starting from the head.
void LinkedList::printArrCityList()
{
   struct ArrCity *temp = head;
   if(head == NULL)
   {
      cout << "The arrival city list is empty\n";
      return;
   }
   while(temp!= NULL)
   {
      cout << temp->arrCity << fixed << setprecision(2) << "(" << temp->price << "), ";
      temp = temp->next;
   }
   cout <<"\n";
}
