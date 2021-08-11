//************************************************************************
// ASU CSE310 Assignment #5
// productID of Author: Kumal Patel
// ASU ID: 1208493243
// Description: this is the main program that reads input from keyboard,
// it then execute various red-black tree operations which is given in the input.
//**************************************************************************

#include <iostream>
#include "RedBlackTree.h"

using namespace std;

//This function used to get the key of a Product
void getKey(string oneLine, string& productID, string& name,
	string& supplierID, string& categoryID);

//This function used to get all info. of a Product
void getProductInfo(string oneLine, string& productID, string& name, string& supplierID,
	string& categoryID, string& unit, double& price);

int main()
{
	string productID, name, supplierID, categoryID, unit;
	double price;
	string command, oneLine, token;
	string delimiter = ",";

	int pos = 0;

	RedBlackTree* rbTree = new RedBlackTree();
	do
	{
		getline(cin, oneLine);
		pos = oneLine.find(delimiter);
		token = oneLine.substr(0, pos);
		command = token;
		oneLine.erase(0, pos + delimiter.length());

		if (command.compare("quit") == 0)
		{
			cout << "\nCommand: quit" << endl;
			rbTree->~RedBlackTree();
			break;
		}
		else if (command.compare("tree_preorder") == 0)
		{
			cout << "\nCommand: tree_preorder" << endl;
			rbTree->preorder();
		}
		else if (command.compare("tree_inorder") == 0)
		{
			cout << "\nCommand: tree_inorder" << endl;
			rbTree->inorder();
		}
		else if (command.compare("tree_postorder") == 0)
		{
			cout << "\nCommand: tree_postorder" << endl;
			rbTree->postorder();
		}
		else if (command.compare("tree_minimum") == 0)
		{
			cout << "\nCommand: tree_minimum" << endl;
			rbTree->treeMinimum();
		}
		else if (command.compare("tree_maximum") == 0)
		{
			cout << "\nCommand: tree_maximum" << endl;
			rbTree->treeMaximum();
		}
		else if (command.compare("tree_predecessor") == 0)
		{
			getKey(oneLine, productID, name, supplierID, categoryID);
			cout << "\nCommand: tree_predecessor" << endl;
			rbTree->treePredecessor(productID, name, supplierID, categoryID);
		}
		else if (command.compare("tree_successor") == 0)
		{
			getKey(oneLine, productID, name, supplierID, categoryID);
			cout << "\nCommand: tree_successor" << endl;
			rbTree->treeSucessor(productID, name, supplierID, categoryID);
		}
		else if (command.compare("tree_search") == 0)
		{
			getKey(oneLine, productID, name, supplierID, categoryID);
			cout << "\nCommand: tree_search" << endl;
			rbTree->treeSearch(productID, name, supplierID, categoryID);
		}
		else if (command.compare("tree_insert") == 0)
		{
			getProductInfo(oneLine, productID, name, supplierID,
				categoryID, unit, price);
			cout << "\nCommand: tree_insert" << endl;
			cout << left;
			cout << setw(5) << productID
				<< setw(35) << name
				<< setw(15) << supplierID
				<< setw(15) << categoryID
				<< setw(25) << unit
				<< setw(5) << price << endl;

			rbTree->treeInsert(productID, name, supplierID, categoryID, unit, price);
		}
	} while (true);  //continue until 'quit'
	return 0;
}

//**************************************************************
//This function from one line, extracts the productID, name, supplierID
//and categoryID information of a Product.
void getKey(string oneLine, string& productID, string& name,
	string& supplierID, string& categoryID)
{
	string delimiter = ",";
	int pos = oneLine.find(delimiter);
	string token = oneLine.substr(0, pos);
	productID = token;
	oneLine.erase(0, pos + delimiter.length());

	pos = oneLine.find(delimiter);
	token = oneLine.substr(0, pos);
	name = token;
	oneLine.erase(0, pos + delimiter.length());

	pos = oneLine.find(delimiter);
	token = oneLine.substr(0, pos);
	supplierID = token;
	oneLine.erase(0, pos + delimiter.length());

	pos = oneLine.find(delimiter);
	token = oneLine.substr(0, pos);
	categoryID = token;
	oneLine.erase(0, pos + delimiter.length());
}

//**************************************************************
//This function from one line, get all Product's info.
void getProductInfo(string oneLine, string& productID, string& name, string& supplierID,
	string& categoryID, string& unit, double& price)
{
	string delimiter = ",";
	int pos = oneLine.find(delimiter);
	string token = oneLine.substr(0, pos);
	productID = token;
	oneLine.erase(0, pos + delimiter.length());

	pos = oneLine.find(delimiter);
	token = oneLine.substr(0, pos);
	name = token;
	oneLine.erase(0, pos + delimiter.length());

	pos = oneLine.find(delimiter);
	token = oneLine.substr(0, pos);
	supplierID = token;
	oneLine.erase(0, pos + delimiter.length());

	pos = oneLine.find(delimiter);
	token = oneLine.substr(0, pos);
	categoryID = token;
	oneLine.erase(0, pos + delimiter.length());

	pos = oneLine.find(delimiter);
	token = oneLine.substr(0, pos);
	unit = token;
	oneLine.erase(0, pos + delimiter.length());

	pos = oneLine.find(delimiter);
	token = oneLine.substr(0, pos);
	price = stod(token); //convert string into double
	oneLine.erase(0, pos + delimiter.length());
}