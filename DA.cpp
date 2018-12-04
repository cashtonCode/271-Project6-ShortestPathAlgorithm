/*
 DIJKSTRA'S ALGORITHM

 NEEDS:
 - FILLED ADJACENCY LIST
 - SIZE OF A. LIST
 - QUEUE OF CONNECTED VERTICES
 - BEGINNING AND END OF CITY LINKED LIST
 - BEGINNING AND END OF PATH BACK
 - SIZE OF PATH BACK

*/

// SUPPOSE THERE IS ADJACENCY LIST: ADJACENCY_LIST
// SUPPOSE THERE IS AN PATH_BACK_ARRAY THAT STORES THE WEIGHT OF THE PATHS BACK TO SOURCE AND THE ABSTRACTED PATH BACK: PB_ONE[AMOUNT OF CITIES + 1][2]
// USE SOURCE_CITY AS AN INDEX
for (EVALUATE THE ADJACENCY_LIST[ SOURCE_CITY ] FROM BEGINNING; TO END; INCREMENT LIST)
{
  if (THE SIZE STORED IN THE NODE < THE SIZE STORED IN PB_ONE[ SOURCE_CITY ][0])
  {
    REPLACE THE SIZE STORED IN PB_ONE[ CITY STORED IN NODE ][0] WITH SIZE STORED IN NODE
    REPLACE THE RETURN INDEX IN PB_ONE[ CITY STORED IN NODE ][1] WITH SOURCE_CITY
    PUSH (CITY STORED IN NODE) ONTO THE QUEUE
  }
}


while (THE QUEUE IS NOT EMPTY)
{
  SAVE NEW_CITY # FROM QUEUE AND POP ITEM FROM QUEUE
  RESET TEMP_CITY TO NEW_CITY
  RESET LENGTH_TRACKER TO 0
  while (TEMP_CITY != SOURCE_CITY)
  {
    INCREMENT LENGTH_TRACKER BY PB_ONE[ TEMP_CITY ][0]
    CHANGE TEMP_CITY TO PB_ONE[ TEMP_CITY ][1]
  }

  for (EVALUATE THE ADJACENCY_LIST[ NEW_CITY ])
  {
    if (LENGTH_TRACKER + THE SIZE STORED IN THE NODE < THE SIZE STORED IN PB_ONE[ CITY STORED IN NODE ][0] )
    {
      REPLACE THE SIZE STORED IN PB_ONE[ CITY STORED IN NODE ][0] WITH SIZE STORED IN NODE
      REPLACE THE RETURN INDEX IN PB_ONE[ CITY STORED IN NODE ][1] WITH NEW_CITY
      PUSH (CITY STORED IN NODE) ONTO THE QUEUE
    }
  }
}








/*ESSENTILALLY, THE ALGORITHM DOES NOT WORK.
PLEASE RENAME ALL ASSOCIATED VARIABLES FOR MORE CLARITY
ALSO WRITE OUT THE STEPS INVOLVED IN THE ALGORITHM AS THAT IS BEING CONFUSING*/

/*
  //DIJKSTRA'S ALGORITHM
  double  tempLength = 0, compareLength, sizeAndPathBack[AdjacencyListBeta.size() + 1][2]; // USED TO HOLD DISTANCES AND THE PATH BACK TO START
  int tempCity, compareCity, tempIndex = cityWeStartAt, counter = 0;


  // INITIALIZING ARRAY
  for(int i = 0; i < AdjacencyListBeta.size() + 1; i++)
  {
    std::cout << i << " ";
    sizeAndPathBack[i][0] = 0;  // SIMPLY SETTING DISTANCE UNREASONABLY HIGH SO ANY INPUT SMALL WILL REPLACE IT
    sizeAndPathBack[i][1] = 0;  // SETTING PATH BACK TO BE 0 THAT WILL BE REPLACED BY ANY CITY WITH A DISTANCE SMALLER THAN ABOVE
    std::cout << i << ": "<< sizeAndPathBack[i][0] << " " << sizeAndPathBack[i][1] << std::endl;
  }
  std::cout << std::endl;




  dijkstraChecklist.push(cityWeStartAt);
  while(!dijkstraChecklist.empty())     // WHILE THERE ARE ITEMS IN THE QUEUE
  {
    tempCity = dijkstraChecklist.front();
    compareCity = tempCity;
    dijkstraChecklist.pop();

    compareLength = 0;
    for (tempNameIter = GraphOfCities[tempCity].begin(); tempNameIter != GraphOfCities[tempCity].end(); tempNameIter++) // EVALUATE THE LL AT THE LOCATION FROM QUEUE
    {
      while(sizeAndPathBack[compareCity][1] != tempCity)
      {
        compareLength += sizeAndPathBack[compareCity][0];
        compareCity = sizeAndPathBack[compareCity][1];
        if (compareCity == 0) break;
        std::cout << "test";
      }



      tempLength = tempNameIter->length + compareLength;
      if ( (sizeAndPathBack[tempCity][0] == 0) || (tempLength < sizeAndPathBack[tempCity][0]) )  // IF LENGTH IS DEFAULT |OR| NEW_LENGTH IS LESS THAN CURRENT_LENGTH
      {
        sizeAndPathBack[tempCity][0] = tempLength;  // SET CURRENT_LENGTH = NEW_LENGTH
        sizeAndPathBack[tempCity][1] = tempCity;    // SET TRACE_BACK TO CURRENT CITY
        dijkstraChecklist.push(tempNameIter->destination);  // PUSH ALTERED ARRAY SLOT INTO QUEUE

      }
    }
    std::cout << counter << std::endl;
    counter++;
  }


*/
