//*******************************************************************
// ASU CSE310 Assignment #6
// ASU ID: 1208493243
// Name: Kumal Patel
// Description: this is a linked list of LinkedList used to represent
// the adjacency list of a graph.
//*****************************************************************

#include "LinkedList.h"

using namespace std;

//Node represents a departure city info. this includes
//the departure city name, its arrival city list and
//other DFS info.
struct Node
{
   string depCity;
   string color, pi;   //pi is the parent
   int dTime, fTime;   //discover & finish time

   LinkedList* arrCityList;
   struct Node* next;
};

class CityList
{
   private:
   struct Node* head;

   public:
   CityList();
   void destructor();
   Node* getHead();
   bool CityListInsert(string deptCityName, LinkedList* arrCityList);
   bool CityListDelete(string deptCityName);
   Node* CityListSearch(string deptCityName);
   void CityListDisplay();
};

//constructor
CityList::CityList()
{
   head = NULL;
}

//Destructor
void CityList::destructor()
{
	struct Node* first = head;
	int cityCount = 0;

	while (first != NULL)
	{
		struct Node* next = first->next;
		delete(first);
		first = next;
		cityCount++;
	}

   head = NULL;
   cout<< "The number of deleted departure cities is: " << cityCount <<"\n";
}

//This function is accessor for head
Node* CityList::getHead()
{
   return head;
}

//Given a departure city name, this function searches
//the adjacency list and return a pointer that points
//to it, otherwise it return NULL
Node* CityList::CityListSearch(string deptCityName)
{
	struct Node* city = head;

	while (city != NULL)
	{
		if (city->depCity == deptCityName)
			return city;

		city = city->next;
	}

	return NULL;
}

//This function inserts a departure city with its arrival city list into
//the cityList. It returns true if the data is inserted successfully
//and false otherwise. Note: departure cities are inserted in alphabetical
//order
bool CityList::CityListInsert(string deptCityName, LinkedList* arrCityList )
{
  struct Node* temp = head;
	struct Node* newCity = new Node();

  newCity->arrCityList = arrCityList;
	newCity->depCity = deptCityName;
  newCity->color = "WHITE";
  newCity->pi = "NULL";
  newCity->dTime = 0;
  newCity->fTime = 0;


  if(head == NULL) // adjacentList is empty
  {
    head = newCity;
    return true;
  }

  else if(newCity->depCity.compare(head->depCity) < 0) // newCity is before head
  {
    newCity->next = head;
    head = newCity;
    return true;
  }

  while(temp != NULL)
  {
    if(newCity->depCity.compare(temp->depCity) == 0) // duplicate 0
      {
        return false;
      }

    if(temp->next == NULL && newCity->depCity.compare(temp->depCity) > 0) // last city in adjacentList, insert at the end
    {
      temp->next = newCity;
      newCity->next = NULL;
      return true;
    }

    else if(newCity->depCity.compare(temp->next->depCity) < 0) // newCity is before current city, place newCity before that current city
    {
      newCity->next = temp->next;
      temp->next = newCity;
      return true;
    }

    temp = temp->next;
  }
    return false;
}

//Given a departure city name, this function deletes it from the CityList.
//it returns true if it is deleted successfully and false otherwise
bool CityList::CityListDelete(string deptCityName)
{
  struct Node* city = head;
  struct Node* temp = head;

  if(head == NULL)
    return false;

  else if(head->depCity == deptCityName) // removing head
  {
    temp = head;
    head = temp->next;
    delete(head);
    return true;
  }

  while(city != NULL)
  {
    if(city->next->depCity == deptCityName)
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

//This function print the CityList on screen. It will
//print departure cities in alphabetical order, and for
//each departure city's reachable arrival city, it will
//also display them in alphabetical order
void CityList::CityListDisplay()
{
   struct Node* temp = head;

   if(head == NULL)
   {
     cout << "The departure city list is empty" << endl;
     return;

   }

   while(temp != NULL)
   {
     cout << left;
     cout << setw(15) << temp->depCity;
	   temp->arrCityList->printArrCityList();
     temp = temp->next;
  }
    cout << "\n";

}
