//************************************************************************
// ASU CSE310 Assignment #6
// ASU ID: 1208493243
// Name: Kumal Patel
// Description: This class defines a directed graph
//********************************************************************

#include "CityList.h"

using namespace std;

class Graph
{
   private:
   int numOfNode;   //number of nodes in the graph
   int time;   //a global timer used to find each node dTime,fTime
   CityList* adjacentList; //a linked list of LinkedList

   public:
   Graph(int numOfNode, CityList* adjacentList);
   void destructor();

   void printGraph();
   void DFS();
   void DFS_Visit(Node *node);
   void printDFSResult();
};

//***************************************************************
//Constructor
Graph::Graph(int numOfNode, CityList* adjacentList)
{
	this->numOfNode = numOfNode;
	time = 0;
	this->adjacentList = adjacentList;
}

//*******************************************************************
//Destructor. We explicitly defines it as a function, in order to be
//able to call it from other functions, to make sure memory is released.
void Graph::destructor()
{

    struct Node *temp = adjacentList->getHead();

    while(temp != NULL)
    {
      adjacentList->destructor();
      temp = temp->next;
    }
}

//*******************************************************************
//This function prints the graph. The graph is represented by adjacency
//list. It will print the adjacency list.
void Graph::printGraph()
{
    adjacentList->CityListDisplay();
}

//*******************************************************************
//This function performs the DFS on the graph. Note: the DFS starts
//from the first node in adjacency list
void Graph::DFS()
{
  struct Node *temp = adjacentList->getHead();   // departure cities

  while(temp != NULL)
  {
    temp->color = "WHITE";
    temp->pi = "none";
    temp = temp->next;
  }
  time = 0;

  temp = adjacentList->getHead();

  while(temp != NULL)
  {
    if(temp->color == "WHITE")
    {
      DFS_Visit(temp);
    }
    temp = temp->next;
  }
}

//*******************************************************************
//This function performs the DFS-Visit from the parameterized node
void Graph::DFS_Visit(Node* node)
{
  time = time + 1;
  node->dTime = time;
  node->color = "GRAY";

//  struct Node *city = adjacentList->getHead();
  struct ArrCity *temp = node->arrCityList->getHead();  // (node type) = (arrCityList type)
  struct Node *city;

  while(temp != NULL)
  {
    city = adjacentList->CityListSearch(temp->arrCity);
      if(city->color == "WHITE")
      {
        city->pi = node->depCity; // pi is string
        DFS_Visit(city);
      }

      temp = temp->next;
  }

  node->color = "BLACK";
  time = time + 1;
  node->fTime = time;
}

//**************************************************************
//This function prints the parent, dTime & fTime info. of
//each node after DFS. Check our solution output.
void Graph::printDFSResult()
{
   struct Node *temp = adjacentList->getHead();

   cout << left;
   cout << setw(15) << "City Name" << setw(10) << "Parent"
   << setw(10) << "dTime" << setw(10) << "fTime" << endl;

   cout << setw(15) << "=========" << setw(10) << "======"
   << setw(10) <<"=====" <<setw(10) << "=====" << endl;

   while(temp != NULL)
   {
     cout << setw(15) << temp->depCity << setw(10) << temp->pi
     << setw(10) << temp->dTime << setw(10) << temp->fTime << endl;

     temp = temp->next;
   }
}
