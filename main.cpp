/*
* Author:   Cashton Christensen
* Date:     4/24/2018
* Purpose:  To find the shortest path from a given
*           start to a given end of a given graph
*/
#include <iostream>
#include <list>
#include <queue>    // Used in Dijkstra's Algorithm
#include <fstream>  // Used to read in files
#include <string>   // Used to get length of files

struct GraphEdge
{
  int destination;
  double length;
};

int main()
{
  std::ifstream cityFile;             // FOR I/O
  std::list<int> AdjacencyListFeed;   // FOR ADJACENCY LIST SIZE
  int cityWeStartAt, cityWeWantToGo;  // FOR FUTURE REFERENCE BEGIN AND END
  int vertex1, vertex2;               // FOR INSERTING EDGES INTO ADJACENCY LIST
  double lengthBetweenVertices;       // FOR INSERTING EDGES INTO ADJACENCY LIST

  int numberOfLines = 0;              // FOR SIZE OF FILE (USEFUL IN WHILE LOOP)
  std::string line;                   // FOR DETERMINING SIZE OF FILE

  // INITIAL READ FOR FILE LENGTH
  cityFile.open("//home//win.thackerw//271//cities.dat");
   if(!cityFile.is_open()){return 0;}
   while (std::getline(cityFile, line)) numberOfLines++;
  cityFile.close();

  // READ IN ALL RELEVANT DATA TO STRUCTS AND LISTS TO DETERMINE SIZE OF ADJACENCY LIST
  cityFile.open("//home//win.thackerw//271//cities.dat");
    if(!cityFile.is_open()){return 0;}
    cityFile >> cityWeStartAt;
    cityFile >> cityWeWantToGo;
    int lineCursor = 1;
    while(lineCursor < numberOfLines)
    {
      cityFile >> vertex1;
      cityFile >> vertex2;
      cityFile >> lengthBetweenVertices;
      lineCursor++;
      AdjacencyListFeed.push_back(vertex1);
      AdjacencyListFeed.push_back(vertex2);
    }
  cityFile.close();

  AdjacencyListFeed.sort();   // USED TO DETERMINE THE SIZE OF THE ADJACENCY LIST
  for(int i = 1; i < AdjacencyListFeed.back(); i++) AdjacencyListFeed.push_back(i); //FILLS IN ANY GAPS IN THE LIST FROM 1 TO END
  AdjacencyListFeed.sort();
  AdjacencyListFeed.unique(); // USED TO DETERMINE THE SIZE OF THE ADJACENCY LIST

  // ASEMBLE ADJACENCY LIST USING DATA
  std::list<GraphEdge> GraphOfCities[AdjacencyListFeed.size() + 1];  // ADJACENCY LIST (ARRAY OF LINKED LISTS) /// THE + 1 ALLOWS ME TO MATCH NUMBER WHILE SACRIFICING THE 0 INDEX
    GraphEdge insertEdge;    // FOR EACH EDGE'S DATA
    cityFile.open("//home//win.thackerw//271//cities.dat");
      if(!cityFile.is_open()){return 0;}
      cityFile >> cityWeStartAt;  // REDUNDANT BUT USED TO MOVE FILE CURSOR
      cityFile >> cityWeWantToGo; // REDUNDANT BUT USED TO MOVE FILE CURSOR
      lineCursor = 1;
      while (lineCursor < numberOfLines)
      {
        cityFile >> vertex1;
        cityFile >> vertex2;
        cityFile >> lengthBetweenVertices;
        lineCursor++;
        insertEdge.length = lengthBetweenVertices;  // DECLARING EDGE LENGTH
        insertEdge.destination = vertex1;           // DECLARING EDGE DESTINATION
        GraphOfCities[vertex2].push_back(insertEdge); // PUSHING A DIRECTED EDGE ONTO GRAPH
        insertEdge.destination = vertex2;           // REDECLARING EDGE DESTINATION
        GraphOfCities[vertex1].push_back(insertEdge); // PUSHING EDGE IN OTHER DIRECTION TO MAINTAIN UNDIRECTED
      }
  cityFile.close();

  // PREPARATIONS FOR DIJKSTRA'S ALGORITHM
  std::list<GraphEdge>::iterator GraphEdgeIter;
  std::queue<int> dijkstraQueue;
  double sizeAndPathBack[AdjacencyListFeed.size() + 1][2], length_tracker;
  int temp_city;

  // INITIALIZING ARRAY
  for(int i = 0; i < AdjacencyListFeed.size() + 1; i++)
  {
    sizeAndPathBack[i][0] = 999;  // SIMPLY SETTING DISTANCE UNREASONABLY HIGH SO ANY INPUT SMALL WILL REPLACE IT
    sizeAndPathBack[i][1] = cityWeStartAt;  // SETTING PATH BACK TO BE 0 THAT WILL BE REPLACED BY ANY CITY WITH A DISTANCE SMALLER THAN ABOVE
  }

  // DIJKSTRA'S ALGORITHM
  // ADJACENCY LIST: GraphOfCities[]
  // QUEUE: dijkstraQueue
  // PATH_BACK_ARRAY: sizeAndPathBack[][]
  // SOURCE_CITY: cityWeStartAt

  // PRIME PATH_BACK_ARRAY WITH SOURCE_CITY DATA
  for(GraphEdgeIter = GraphOfCities[cityWeStartAt].begin(); GraphEdgeIter != GraphOfCities[cityWeStartAt].end(); GraphEdgeIter++)
  {
    sizeAndPathBack[cityWeStartAt][0] = 0;
    sizeAndPathBack[cityWeStartAt][1] = cityWeStartAt;
    if(GraphEdgeIter->length < sizeAndPathBack[GraphEdgeIter->destination][0])
    {
      sizeAndPathBack[GraphEdgeIter->destination][0] = GraphEdgeIter->length;
      sizeAndPathBack[GraphEdgeIter->destination][1] = cityWeStartAt;
      dijkstraQueue.push(GraphEdgeIter->destination);   // POPULATES QUEUE WITH VERTEX TO ASSESS
    }
  }

  while(!dijkstraQueue.empty())
  {
    temp_city = dijkstraQueue.front();   // EXCLUSIVELY USED TO FIND CURRENT PATH LENGTH (FROM frontOfQueue TO cityWeStartAt)
    length_tracker = 0;     // EXCLUSIVELY HOLDS THE PATH LENGTH (FROM frontOfQueue TO cityWeStartAt)

    while(temp_city != cityWeStartAt) // USED TO FIND CURRENT BEST LENGTH BACK TO SOURCE_CITY
    {
      length_tracker += sizeAndPathBack[temp_city][0];
      temp_city = sizeAndPathBack[temp_city][1];
    }
    // UPDATE CURRENT SHORTEST PATHS BACK TO SOURCE_CITY BASED ON EACH NODE'S DATA
    for(GraphEdgeIter = GraphOfCities[dijkstraQueue.front()].begin(); GraphEdgeIter != GraphOfCities[dijkstraQueue.front()].end(); GraphEdgeIter++)
    {
      if(length_tracker + GraphEdgeIter->length < sizeAndPathBack[GraphEdgeIter->destination][0])
      {
        sizeAndPathBack[GraphEdgeIter->destination][0] = length_tracker + GraphEdgeIter->length;
        sizeAndPathBack[GraphEdgeIter->destination][1] = dijkstraQueue.front();
        dijkstraQueue.push(GraphEdgeIter->destination);   // POPULATES QUEUE WITH VERTEX TO ASSESS
      }
    }
    dijkstraQueue.pop();  // REMOVES ASSESSED VERTEX FROM QUEUE
  }

  // PRINT OFF RESULTS OF DIJKSTRA'S ALGORITHM
  std::list<int> path_back_list;
  std::list<int>::iterator intIter;
  temp_city = cityWeWantToGo;
  length_tracker = sizeAndPathBack[cityWeWantToGo][0];

  while(temp_city != cityWeStartAt)
  {
    path_back_list.push_front(temp_city);
    temp_city = sizeAndPathBack[temp_city][1];
  }
  path_back_list.push_front(cityWeStartAt);
  std::cout << "Shortest Path: ";
  for(intIter = path_back_list.begin(); intIter != path_back_list.end(); intIter++) std::cout << *intIter << " ";
  std::cout << "\nLength of Path: " << length_tracker << "\n";
}
