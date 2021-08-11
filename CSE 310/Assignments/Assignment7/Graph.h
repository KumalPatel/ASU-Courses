//********************************************************************
// ASU CSE310 Assignment #7
// Name of Author: Kumal Patel
// ASU ID: 1208493243
// Description: This is the header file that defines an undirected graph
//********************************************************************

#include "Edge.h"

using namespace std;

class Graph
{
   private:
      int V, E;   //number of vertices and edges in the graph
      City** setOfCities;   //an array of cities
      Edge** setOfEdges; //an array of edges

   public:
      Graph(int numOfCities, int numOfEdges, City* cityArray[], Edge* edgeArray[]);
      void destructor();
      void make_set(City* aCity);
      City* find_set(City* aCity);
      void link(City* aCity, City* bCity);
      void Union(City* aCity, City* bCity);
      void printEdgeArray();
      void MergeSortEdges();
      void mergeSort(Edge* edgeArray[], int start, int end);
      void merge(Edge* edgeArray[], int start, int mid, int end);

      void MST_Kruskal();
};

//*******************************************************************
//Constructor
Graph::Graph(int numOfCities, int numOfEdges, City* cityArray[], Edge* edgeArray[])
{
   V = numOfCities;
   E = numOfEdges;

   setOfCities = cityArray;
   setOfEdges = edgeArray;
}

//*******************************************************************
//Destructor
void Graph::destructor()
{
   delete[] setOfCities;
   delete[] setOfEdges;
}

//*******************************************************************
//Given a City, this function creates a new set whose only member is
//the City.
void Graph::make_set(City* aCity)
{
	aCity->parent = aCity;
   aCity->rank = 0;
}

//*******************************************************************
//Given a City, this function returns a pointer to the representative
//of the (unique) set containing 'aCity'
City* Graph::find_set(City* aCity)
{
   if(aCity != aCity->parent)
   {      
      aCity->parent = find_set(aCity->parent);
   }
   return aCity->parent;
}

//*******************************************************************
//Given two cities, this function checks the dynamic sets that contain
//'aCity' and 'bCity' and update their rank and parent info. accordingly
void Graph::link(City* aCity, City* bCity)
{

	if(aCity->rank > bCity->rank)
   {
         bCity->parent = aCity;
   }
   else if (aCity->rank < bCity->rank)
   {
      aCity->parent = bCity;
   }

   else
   {
      bCity->parent = aCity;
      aCity->rank = aCity->rank + 1;
   }
}

//*******************************************************************
//Given two cities, this function unites the dynamic sets that contain
//'aCity' and 'bCity' into a new set that is the union of the two sets.
void Graph::Union(City* aCity, City* bCity)
{
   link(find_set(aCity),find_set(bCity));
}

//*******************************************************************
//This function print each of the edges of edge array. It can be
//used as an auxillary function to check the MergeSort result
void Graph::printEdgeArray()
{   
   for (int i = 0; i < E; i++)
   {
      setOfEdges[i]->printEdge();
   }
}

//*******************************************************************
//This function performs the Merge Sort on the graph edges according
//to the weight. Sort all edges in non-decreasing order
void Graph::MergeSortEdges()
{
   // include the weight
   int smallest, largest = setOfCities[0]->rank;
   for (int i = 0; i < V; i++)
   {
      if(setOfCities[i]->rank < smallest)
         smallest = setOfCities[i]->rank;
      if(setOfCities[i]->rank > largest)
         largest = setOfCities[i]->rank;
   }
	mergeSort(setOfEdges, smallest, largest);
}

//*******************************************************************
//This function performs the Merge Sort on a sub edgeArray.
void Graph::mergeSort(Edge* edgeArray[], int start, int end)
{
   if(start < end)
   {
      int mid = start+(end-start)/2;
      mergeSort(edgeArray, start, mid);
      mergeSort(edgeArray, mid+1, end);
      merge(edgeArray, start, mid, end);
   }
}

//*******************************************************************
//This function merges the two sorted sub edgeArray.
void Graph::merge(Edge* edgeArray[], int start, int mid, int end)
{
   int n1 = mid-start+1;  //get the length of the first half subarray
   int n2 = end-mid;      //get the length of the second half subarray
   int i, j, k;

   //Dynamically create two new arrays each stored the sorted half
	Edge** left = (Edge**)malloc(sizeof(Edge*) * n1);
	Edge** right = (Edge**)malloc(sizeof(Edge*) * n2);

   for(i = 0; i < n1; i++)
   {
      left[i] = edgeArray[start+i];
   }
   for(j = 0; j < n2; j++)
   {
      right[j] = edgeArray[mid+1+j];
   }

   i = 0, j = 0, k = 1;

   while(i < n1 && j < n2)
   {
      if(left[i] <= right[j])
      {
         edgeArray[k] = left[i];
         i++;
      }
      else
      {
         edgeArray[k] = right[j];
         j++;
      }
      k++;
   }

   while(i < n1)
   {
      edgeArray[k] = left[i];
      i++;
      k++;
   }

   while(j < n2)
   {
      edgeArray[k] = right[j];
      j++;
      k++;
   }

   //at the end, release the memory left and right occupied
   delete left;
   delete right;
}


//*******************************************************************
//This function performs the Kruskal algorithm on the graph.
void Graph::MST_Kruskal()
{
   cout << "MST Kruskal Algorithm Result\n" << endl;
   double totalWeight = 0.0;
   
   for (int i = 0; i < V; i++)
   {
      make_set(setOfCities[i]);
   }
   
   MergeSortEdges();
    
   for(int i = 0; i < E; i++)
   {
      if(find_set(setOfEdges[i]->getCity1()) != find_set(setOfEdges[i]->getCity2()))
      {
         setOfEdges[i]->printEdge();
         Union(setOfEdges[i]->getCity1(), setOfEdges[i]->getCity2());         
         totalWeight += setOfEdges[i]->getPrice();
      }
   }
   cout << "=================================================" << endl;
   cout << "Total Price: " << totalWeight << endl;
}
