#include <stdio.h>
#include <stdlib.h>
#include "List.h"

//city
typedef struct City_List
{
    char cityName[128];
    int longitude;
    int latitude;
    int distanceFromStart; // 100000;
    int distanceToGoal; // 100000;
    List *neighbour;
}City;

//neighbours
typedef struct Neighbour_List
{
    City *city;
    char city_Name;
    int distance;
} Neighbour;


//void getCityByName(neighbour->name);

void searchCityNeighbours();

//coordinate

//doxygen -> for generating html files

