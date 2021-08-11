//************************************************************************
// ASU CSE310 Assignment #5
// Name of Author: Kumal Patel
// ASU ID: 1208493243
// Description: Red black tree implementation. See RedBlackTree.h
//              for the tree definition. You need to add your own
//              code at //---- position
//************************************************************************

#include "RedBlackTree.h"

using namespace std;

//*******************************************************************
//constructor
RedBlackTree::RedBlackTree()
{
	root = NULL;
}

//*******************************************************************
//destructor
RedBlackTree::~RedBlackTree()
{
	int nodeSize = deleteNode(root);
	cout << "The number of nodes deleted: " << nodeSize << endl;
}

//*******************************************************************
//delete the sub-tree rooted at 'node' and return number of nodes deleted
//This can be defined as a recursive function
int RedBlackTree::deleteNode(Node* node)
{
	int count = 0;
	if (node == NULL)
		return 0;
	else
	{
		count += deleteNode(node->leftChild);
		count += deleteNode(node->rightChild);
		count++;	
		delete(node);
		return count;
	}
}

//****************************************************************
//This is the general BST insertion operation.
//It does not care about the color of the newly added node.
void RedBlackTree::insertNode(Node* node)
{
	if (node == NULL)
		return;

	if (this->root == NULL) // if the tree is empty
	{
		root = node;
	}
	else
	{
		struct Node* y = NULL;
		struct Node* x = root;
		string key1 = x->productID + x->name + x->supplierID + x->categoryID;

		while (x != NULL)
		{
			y = x;
			string key2 = y->productID + y->name + y->supplierID + y->categoryID;
			
			if (compareNodes(node, key2) < 0)
				x = x->leftChild;
			else
				x = x->rightChild;
		}
			string key2 = y->productID + y->name + y->supplierID + y->categoryID;
			node->parent = y;

			if (y == NULL)
				root = node;
			else if (compareNodes(node, key2) < 0)
				y->leftChild = node;
			else
				y->rightChild = node;

			node->leftChild = NULL;
			node->rightChild = NULL;
			node->color = "RED";
	}

	//At the end, need to call fixup() in case the newly
	//added node's parent is also RED
	fixUp(node);
}

//*******************************************************************
//At beginning, each newly added node will always be red,
//this may violate the red-black tree property #4. fixUp()
//function will restore the property.
void RedBlackTree::fixUp(Node* z)
{
	struct Node* y;

	if (z == root)
	{
		z->color = "BLACK";
		return;
	}

	//if z's color is 'RED' and its parent's color is also 'RED'
	while (z->parent != NULL && z->parent->color.compare("RED") == 0) 
	{
		if (z->parent == z->parent->parent->leftChild)
		{
			y = z->parent->parent->rightChild;
			if (y != NULL && y->color == "RED")
			{
				z->parent->color = "BLACK";
				y->color = "BLACK";
				z->parent->parent->color = "RED";
				z = z->parent->parent;
			}
			else
			{
				if (z == z->parent->rightChild)
				{
					z = z->parent;
					leftRotate(z);
				}
				z->parent->color = "BLACK";
				// what if parent's parent is null?
				z->parent->parent->color = "RED";
				rightRotate(z->parent->parent);
			}
		}
		else // if z->parent == z->parent->parent->right
		{
			y = z->parent->parent->leftChild;
			if (y != NULL && y->color == "RED")
			{
				z->parent->color = "BLACK";
				y->color = "BLACK";
				z->parent->parent->color = "RED";
				z = z->parent->parent;
			}
			else 
			{
				if (z == z->parent->leftChild)
				{
					z = z->parent;
					rightRotate(z);
				}
				z->parent->color = "BLACK";
				z->parent->parent->color = "RED";
				leftRotate(z->parent->parent);
			}
		}
	}//end while

	//make sure the root is always 'BLACK'
	this->root->color = "BLACK";
}

//*****************************************************
//This function print the pre-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void RedBlackTree::preOrderTraversal(Node* node)
{
	if (node == NULL)
	{
		return;
	}
	else
	{
		print(node);
		preOrderTraversal(node->leftChild);
		preOrderTraversal(node->rightChild);
	}
}

//**************************************************
//This function print the in-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void RedBlackTree::inorderTraversal(Node* node)
{
	if (node == NULL)
	{
		return;
	}
	else
	{
		inorderTraversal(node->leftChild);
		print(node);
		inorderTraversal(node->rightChild);
	}
}

//**************************************************
//This function print the post-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void RedBlackTree::postOrderTraversal(Node* node)
{
	if (node == NULL)
	{
		return;
	}
	else
	{
		postOrderTraversal(node->leftChild);
		postOrderTraversal(node->rightChild);
		print(node);
	}
}

//**************************************************************
//This function returns a pointer points to the minimum node from
//the current sub-tree rooted at 'node'. It's a recursive function
Node* RedBlackTree::findMinimumNode(Node* node)
{
	if (node == NULL)
	{
		cout << "Tree is empty, no MINIMUM." << endl;
		return node;
	}
	else
	{
		if (node->leftChild == NULL)
			return node;
		else
			findMinimumNode(node->leftChild);
	}
}

//**************************************************************
//This function returns a pointer points to the maximum node from
//the current sub-tree rooted at 'node'. It's a recursive function
Node* RedBlackTree::findMaximumNode(Node* node)
{
	if (node == NULL)
	{
		cout << "Tree is empty, no MAXIMUM." << endl;
		return node;
	}
	else
	{
		if (node->rightChild == NULL)
			return node;
		else
			findMaximumNode(node->rightChild);
	}
}

//**************************************************************
//This function search the tree for a given key of a Product
//Note: key is the combination of productID, name, supplierID
//and categoryID. It returns a pointer points to the node if founded
//otherwise return NULL
Node* RedBlackTree::treeSearch(string productID, string name, string supplierID, string categoryID)
{
	string key1 = productID + name + supplierID + categoryID;
	Node* node = root;
	while (node != NULL)
	{
		if (compareNodes(node,key1) == 0) // if found
			{
				 cout << left;
				 cout << setw(5) << productID
				<< setw(35) << name
				<< setw(15) << supplierID
				<< setw(15) << categoryID
				<< " is FOUND." << endl;
				return node;
			}
		else
		{
			if (compareNodes(node, key1) < 0)
				node = node->rightChild;
			else
				node = node->leftChild;
		}
		 key1 = productID + name + supplierID + categoryID;
	}
			cout << left;
			cout << setw(5) << productID
				<< setw(35) << name
				<< setw(15) << supplierID
				<< setw(15) << categoryID
				<< " is NOT FOUND." << endl;
			return NULL;
}

	//****************************************************
	//This function left-rotate the BST at 'node'
	void RedBlackTree::leftRotate(Node* node)
	{
		if (node == NULL)
			return;

		struct Node* y;

		y = node->rightChild;
		node->rightChild = y->leftChild;

		if (y->leftChild != NULL)
			y->leftChild->parent = node;
		y->parent = node->parent;
		if (node->parent == NULL)
			root = y;
		else if (node == node->parent->leftChild)
			node->parent->leftChild = y;
		else
			node->parent->rightChild = y;
		y->leftChild = node;
		node->parent = y;
	}

	//***************************************************
	//This function right-rotate the BST at 'node'
	void RedBlackTree::rightRotate(Node* node)
	{
		if (node == NULL)
			return;

		struct Node* y;

		y = node->leftChild;
		node->leftChild = y->rightChild;

		if (y->rightChild != NULL)
			y->rightChild->parent = node;
		y->parent = node->parent;
		
		if (node->parent == NULL)
			root = y;
		else if (node == node->parent->rightChild)
			node->parent->rightChild = y;
		else
			node->parent->leftChild = y;
		y->rightChild = node;
		node->parent = y;
	}


	//**************************************************************
	//This function finds the predecessor of the given 'node'
	//it prints the relevant predecessor info. on screen.
	Node* RedBlackTree::findPredecessorNode(Node* node)
	{
		Node* predn;

		if (node->leftChild != NULL)
		{
			predn = findMaximumNode(node->leftChild);
			cout << left;
			cout << "Its Predecessor is: " << endl;
			print(predn);
			return predn;
		}

		else  //not found
		{
			predn = node->parent;
			while (predn != NULL && node == predn->leftChild)
			{
				node = predn;
				predn = predn->parent;
			}
			if (predn == NULL)
			{
				cout << left;
				cout << "Its Predecessor does NOT EXIST" << endl;
				return predn;
			}
			else
			{
				cout << left;
				cout << "Its Predecessor is: " << endl;
				print(predn);
				return predn;
			}
		}
			
	}

	//**************************************************************
	//This function finds the successor of the given 'node'
	//it prints the relevant successor info. on screen.
	Node* RedBlackTree::findSuccessorNode(Node* node)
	{
		Node* sn;

		if (node->rightChild != NULL)
		{
				sn = findMinimumNode(node->rightChild);
				cout << left;
				cout << "Its Successor is: " << endl;
				print(sn);
				return sn;
		}
		else  
		{
			sn = node->parent;
			while (sn != NULL && node == sn->rightChild)
			{
				node = sn;
				sn = sn->parent;
			}
			if (sn == NULL)
			{
				cout << left;
				cout << "Its Successor does NOT EXIST" << endl;
				return sn;
			}
			else
			{
				cout << left;
				cout << "Its Successor is: " << endl;
				print(sn);
				return sn;
			}

		}
	}

	//**************************************************************
	//This function find the minimum node of the entire red-black tree
	//It print out the minimum node info. on screen if tree is not empty
	//or print 'Tree is empty' message on screen.
	void RedBlackTree::treeMinimum()
	{
		if (root == NULL)
		{
			cout << "Tree is empty. No Minimum." << endl;
			return;
		}
		cout << "The MINIMUM is:" << endl;
		print(findMinimumNode(root));
	}

	//**************************************************************
	//This function find the maximum node of the entire red-black tree
	//It print out the maximum node info. on screen if tree is not empty
	//or print 'Tree is empty' message on screen.
	void RedBlackTree::treeMaximum()
	{
		if (root == NULL)
		{
			cout << "Tree is empty. No Maximum." << endl;
			return;
		}
		cout << "The MAXIMUM is:" << endl;
		print(findMaximumNode(root));
	}

	//******************************************************************
	//This function print out the pre-order traversal of the entire tree
	void RedBlackTree::preorder()
	{
		if (root == NULL)
		{
			cout << "Tree is empty." << endl;
			return;
		}
		preOrderTraversal(root);
	}

	//******************************************************************
	//This function print out the in-order traversal of the entire tree
	void RedBlackTree::inorder()
	{
		if (root == NULL)
		{
			cout << "Tree is empty." << endl;
			return;
		}
		inorderTraversal(root);
	}

	//******************************************************************
	//This function print out the post-order traversal of the entire tree
	void RedBlackTree::postorder()
	{
		if (root == NULL)
		{
			cout << "Tree is empty." << endl;
			return;
		}
		postOrderTraversal(root);
	}

	//******************************************************************
	//Given a product's key, this function first check whether the
	//product is inside the tree or not, if it is inside, it will print
	//its predecessor info. on screen, if not, it print an error message
	void RedBlackTree::treePredecessor(string productID, string name,
		string supplierID, string categoryID)
	{
		struct Node* temp;

		if (root == NULL)
			cout << "Tree is empty. No Predecessor." << endl;
		else
		{
			temp = treeSearch(productID, name, supplierID, categoryID);
			
			if (temp == NULL) // not found
				cout << "Its Predecessor does NOT EXIST" << endl;
			else
				findPredecessorNode(temp);
		}
	}

	//******************************************************************
	//Given a product's key, this function first check whether the
	//product is inside the tree or not, if it is inside, it will print
	//its successor info. on screen, if not, it print an error message
	void RedBlackTree::treeSucessor(string productID, string name,
		string supplierID, string categoryID)
	{
		struct Node* temp;

		if (root == NULL)
			cout << "Tree is empty. No Successor." << endl;
		else
		{
			temp = treeSearch(productID, name, supplierID, categoryID);

			if (temp == NULL) // not found
				cout << "Its Successor does NOT EXIST" << endl;
			else
				findSuccessorNode(temp);
		}
	}

	//**************************************************************
	//This function create a node from the given info., then insert
	//the node inside the red-black tree. Note: at beginning, the newly
	//added node should always be 'RED'
	void RedBlackTree::treeInsert(string productID, string name, string supplierID,
		string categoryID, string unit, double price)
	{
		struct Node* node = new Node();
		node->productID = productID;
		node->name = name;
		node->supplierID = supplierID;
		node->categoryID = categoryID;
		node->unit = unit;
		node->price = price;

		insertNode(node);
	}

	//******************************************************************
	//Given a 'node', this function prints all its information on screen
	void RedBlackTree::print(Node* node)
	{
		cout << left;
		cout << setw(5) << node->productID
			<< setw(35) << node->name
			<< setw(15) << node->supplierID
			<< setw(15) << node->categoryID
			<< setw(25) << node->unit
			<< setw(7) << node->price
			<< setw(7) << node->color << endl;
	}

	//**************************************************************
	//Given a Node 'node1', this function compares it with another
	//node's key.
	//key is a string combination of productID + name + supplierID + categoryID
	//It returns a negative number if in alphabetical order, key2 is
	//in front of 'node1'; otherwise it returns a positive number
	int RedBlackTree::compareNodes(Node* node1, string key2)
	{
		string nodeKey = node1->productID + node1->name + node1->supplierID + node1->categoryID;

		if (nodeKey.compare(key2) < 0)
			return -1;
		else if (nodeKey.compare(key2) > 0)
			return 1;
		else
			return 0;
	}

	//**************************************************************
	//This function return the root of the red-black tree
	Node* RedBlackTree::getRoot()
	{
		return this->root;
	}