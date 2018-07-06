#include <stdio.h>
#include <stdlib.h>
#include "List.h"

//city
typedef struct City_List
{
    char cityName[128];
    int longitude;
    int latitude;
    int distanceFromStart; // 100000 a big value assigned;
    int distanceToGoal; // 100000 a big value assigned;
    List *neighbour;
}City;

//neighbours
typedef struct Neighbour_List
{
    City *city;
    char city_Name;
    int distance;
} Neighbour;


bool isFileNull(FILE *fileName);

void printCity(void *element);

int compare_function (void *elet_1, void *elet_2);

void myFunctionLoop(List *map);

City *findCityByName(List *map, char *name_of_city);



//a function to search for cities and neighbours
void searchCityNeighbours();

//doxygen -> for generating html files

