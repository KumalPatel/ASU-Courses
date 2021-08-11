//************************************************************************
// ASU CSE310 Assignment #7
// ASU ID: 1208493243
// Name: Kumal Patel
// Description: this is the main program that reads input from keyboard,
// it then use disjoint set data structure to perform Kruskal MST algorithm
// on the graph.
// //---- is where you need to add your own codes
//**************************************************************************

#include "Graph.h"

using namespace std;

void getArrCityInfo(string oneArrCityInfo, string& arrCityName, double& price);
City* searchCity(City* oneCityArray[],int size, string oneCityName);

int main()
{
    int V, E;        //number of vertices and edges

    cin >> V >> E;
    cin.ignore(20, '\n');

    //a City array used to store all vertices (Cities) of the graph
    City* cityArray[V];

    //an array used to store all edges of the graph
    Edge* edgeArray[E];

    for(int i = 0; i < V; i++)
    {
       cityArray[i] = NULL;
    }

    for(int i = 0; i < E; i++)
    {
       edgeArray[i] = NULL;
    }

    int i =0, j=0; //index for cityArray and edgeArray

    //local variables
    City* city1;
    City* city2;
    Edge* aNewEdge;

    double price;
    bool flag; // to check if city exisits
 
    string oneLine;
    string delimiter = ",";
    std::getline(cin, oneLine); 

    while(oneLine.compare("End") != 0)
    {
      //get one line of the input, extract the first token
      //create a City if it doesn't exist in cityArray,
      //insert it inside the cityArray; otherwise get a pointer
      //point to the City. This City will be the first point for
      //aNewEdge    
      string city;
      string arrCity;
      string cityName;

      int pos = 0;
      flag = true;
      pos = oneLine.find(delimiter);
      string token = oneLine.substr(0, pos); 
      city = token;
      oneLine.erase(0,pos+delimiter.length());

      for(int i = 0; i < V; i++)
      {
         if(cityArray[i] == NULL) //empty list
         {
            flag = true;
            break;
         }

          if(cityArray[i]->cityName == city) // city exists, so dont create city. set flag to false and break.
         {
            flag = false; 
            break;
         }
      }
 
      if(flag == true) // city doesnt exist so can add city to array
      {
         City* acity = new City(city);
         cityArray[i] = acity;
         city1 = acity; // not sure
         i++;
      }
      else
      {
         city1 = searchCity(cityArray, V, city);
      }
      
      //extract the arrival city info. check whether it exists in
      //cityArray or not, if not, create a new City, add it inside.
      //This city will be the second point for aNewEdge

      while(oneLine.substr(0, oneLine.find(delimiter)) != "")
      {

         flag = true;
         pos = oneLine.find(delimiter);
         token = oneLine.substr(0,pos);
         arrCity = token;
         oneLine.erase(0,pos+delimiter.length());
         getArrCityInfo(arrCity, cityName, price);

         for(int i = 0; i < V; i++)
         {
            if(cityArray[i] == NULL)
            {
               flag = true;
               break;
            }
         
            else if(cityArray[i]->cityName == cityName)
            {
               flag = false;
               break;
            }
         }

         if(flag == true)
         {
            City* acity = new City(cityName);
            cityArray[i] = acity;
            city2 = acity;
            i++;
         }
         else
         {
            city2 = searchCity(cityArray, V, cityName);
         }

         //by using the two cities we got above, create a new edge, add
         //it inside edgeArray
         aNewEdge = new Edge(city1, city2, price);
         edgeArray[j] = aNewEdge;
         j++;
      }
      //get next line
      std::getline(cin, oneLine);
    } //repeat until the 'End'

    //Create a Graph object by using cityArray and edgeArray
    Graph obj = Graph(V, E, cityArray, edgeArray);

    //Run Kruskal MST algorithm on above graph
    obj.MST_Kruskal();

}

//****************************************************************
//By giving a string, for example 'Dallas(456.5)', this function
//extract the arrival city name 'Dallas' and air ticket price '456.5'
//Note: the delimeter is left or right parenthesis
//****************************************************************
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, double& price)
{
   string delimiter1 = "(", delimiter2 = ")";
   int pos=oneArrCityInfo.find(delimiter1);
   string token = oneArrCityInfo.substr(0,pos);
   arrCityName = token;

   oneArrCityInfo.erase(0, pos+delimiter1.length());

   pos = oneArrCityInfo.find(delimiter2);
   token = oneArrCityInfo.substr(0,pos);
   price = stod(token);
   oneArrCityInfo.erase(0, pos+delimiter2.length());
}

//*********************************************************************
//Given a city name, this function searches cityArray and it return a
//pointer points to the City if it already exists, otherwise it returns NULL
//****************************************************************
City* searchCity(City* oneCityArray[], int arraySize, string oneCityName)
{
   struct City* temp;

   for(int i = 0; i < arraySize; i++)
   {
      if(oneCityArray[i]->cityName == oneCityName)
         return oneCityArray[i];
   }
      return NULL;
}

