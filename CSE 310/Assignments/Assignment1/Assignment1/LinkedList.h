// Assignment: #1 (ASU Fall 2019)
// Name: Kumal Patel
// ASU ID: 1208493243
// ASU Email Address: kspatel8@asu.edu
// Description: Constructs LinkedList and is able to manipulate to its desires. Add in alphabetical orde,
// remove, and etc.

#include <iostream>
#include <iomanip> //to format the output
#include <string>
#include <stdio.h>

using namespace std;

//struct Product represents certain product information
struct Product
{
	string name;
	int id;
	double price;
	struct Product* next;
};

//class LinkedList will contains a linked list of Products
class LinkedList
{
private:
	struct Product* head;

public:
	LinkedList();
	~LinkedList();
	bool isFound(int productId);
	bool addProduct(string productName, int productId, double productPrice);
	bool removeProduct(int productId);
	bool changeProductName(int productId, string newProductName);
	bool changeProductPrice(int productId, double newPrice);
    void printProductList();
};

//Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
	head = NULL;
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the existing linked list.
//It deletes all the nodes including the head and finally prints the number of nodes deleted by it.
//Return value: Prints the number of nodes deleted by it.
LinkedList::~LinkedList()
{
	int productCount = 0;
	struct Product* list = head;

	while (list != NULL) // traverse
	{
		struct Product* newList = list->next; // set newList to next after head, and delete list. and set list to newList
		delete list;
		productCount++;
		list = newList;
	}
	head = NULL;
	cout << "The number of deleted products is: " << productCount << "\n";
}

//A function to identify if the parametered Product is inside the LinkedList or not.
//Return true if it exists and false otherwise.
bool LinkedList::isFound(int productId)
{
	struct Product* start = head;
	bool found = false;
	while (start != NULL)
	{
		if (start->id == productId)
		{
			found = true;
			break;
		}
		else
			start = start->next;
	}
	return found;
}

//Creates a new node and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of the Products by their names
//while inserting it into the list. Note: you cannot insert duplicated products
//Return value: true if it is successfully inserted and false in case of failures.
bool LinkedList::addProduct(string productName, int productId, double productPrice)
{
	bool flag = false;

	try {

		struct Product* newProduct = new Product;
		struct Product* list = head;
		struct Product* prev = head;
		struct Product* temp = head;

		newProduct->id = productId;
		newProduct->name = productName;
		newProduct->price = productPrice;

		if (head == NULL) // if list is empty
		{
			head = newProduct;
			head->next = NULL;
			return true;
		}

		// when only one node in list
		else if (head->next == NULL)
		{
			// if newproduct is less than head
			if (productName.compare(list->name) < 0)
			{
				prev = newProduct;
				prev->next = list;
				head = prev;
				list->next = NULL;
				return true;
			}
			else
			{
				list = newProduct;
				head->next = list;
				list->next = NULL;
				return true;
			}
		}

		// traverse list to add if the next > then prev
		while (list->next != NULL)
		{	
			while (temp != NULL)
			{
				if (temp->id == productId)
					return false;
				else
					temp = temp->next;
			}
			
			if (productName.compare(head->name) < 0)
			{
				prev = newProduct;
				head = newProduct;
				prev->next = list;
				flag = true;
				break;
			}

			else if (productName.compare(list->name) < 0) // add in between nodes
			{
				prev->next = newProduct;
				newProduct->next = list;
				flag = true;
				break;
			}

			else if (list != head)
				prev = prev->next;

			list = list->next;

			if (productName.compare(list->name) < 0) // add in between nodes
			{
				prev->next = newProduct;
				newProduct->next = list;
				flag = true;
				break;
			}
			
			else if (list->next == NULL) // add to end of list
			{
				list->next = newProduct;
				newProduct->next = NULL;
				flag = true;
				break;
			}

		}
		}
		catch  (const bad_alloc&) // if runs out of memory to create new object
		{
			return false;
		}

		return flag;
	}
//Removes the given Product from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise.
bool LinkedList::removeProduct(int productId)
{
	struct Product* list = head;
	struct Product* removed = head;

	while (removed != NULL)
	{	
		if (removed->id == productId)
		{
			if (removed == head)
			{
				head = list->next;
				list = list->next;
				delete(removed);
				return true;
			}

			list->next = removed->next;
			delete(removed);
			return true;
		}
		
		removed = removed->next;

		if (removed->id != productId)
		{
			list = list->next;

			if (removed->next == NULL)
				return false;
		}
	}
}

//Modifies the data of the given Product.
//Return true if it modifies successfully and false otherwise.
bool LinkedList::changeProductName(int oldProductId, string newProductName)
{
	struct Product* list = head;
	struct Product* p = head;
	struct Product* q = head;
	struct Product* temp = head;

	while (list != NULL)
	{
		if (list->id == oldProductId)
		{
			list->name = newProductName;
			p = list;
			break;
		}
		q = list;
		list = list->next;
	}
	q->next = list->next; // removed connection of old name
	
	list = head;

	while (temp != NULL)
	{
		if (p->name.compare(temp->name) < 0)
		{
			list->next = p;
			p->next = temp;
			return true;
		}
		
		else if (temp->next == NULL) // if at end and to end of list
		{
			temp->next = p;
			p->next = NULL;
			return true;
		}
		
		else if (p->name.compare(temp->name) > 0)
		{
			list = temp;
			temp = temp->next;

		}
		else if (p == temp) // if p is in head and in correct order
			return true;
	}
}

bool LinkedList::changeProductPrice(int productId, double newPrice)
{
	// search list with id, if found change product price and return true, else return false
	struct Product* list = head;

	while(list != NULL)
	{
		if (list->id == productId)
		{
			list->price = newPrice;
			return true;
		}
		list = list->next;
	}
	return false;
}

//Prints all the elements in the linked list starting from the head node.
void LinkedList::printProductList()
{
	struct Product* list = head;

	while (list != NULL)
	{
		cout << list->id << ", ";
		cout << list->name << ", $";
		printf("%.2f\n", list->price);
		list = list->next;
	}
}
