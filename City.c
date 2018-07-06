#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "City.h"
#include "status.h"

int element_1, element_2;
City *city;
Neighbour *neighbour;

//a comparison function to compare the elements
int compare_function (void *elet_1, void *elet_2)
{
    int *el_a = (int*) elet_1;
    int *el_b = (int*) elet_2;

    return (*el_a > *el_b) - (*el_a < *el_b);
}

//a function to print the element in a city
void printCity(void *element)
{
    City *city = (City *)element;
    printf("%s\n", city->cityName);
}

//a function to check if a file read is null or not
bool isFileNull(FILE *fileName)
{
    if (fileName == NULL)
    {
        return true;
    }
    return false;
}

//a function to read and search through a .MAP file for cities and its neighbours
void searchCityNeighbours()
{
    int num, longitude_distance, latitude_distance;
    char city_neighbour_name[128];

    //create a pointer to the file
    FILE *franceFile;
    franceFile = fopen("FRANCE.MAP", "r");

    //create a list of cities and neighbour
    List *map = newList(compare_function, printCity);

    //check if file is not null before reading contents
    if (isFileNull(franceFile) == true)
    {
        printf("Can't open input file FRANCE.MAP!\n");
        exit(1);
    }
    else
    {
        //read through the file with a loop
        while((num = fscanf(franceFile, "%s %d %d", city_neighbour_name, &longitude_distance, &latitude_distance)) != EOF)
        {
            if(num == 3)
            {
                //city found so add to city list
                city = (City *)malloc(sizeof(City));
                strcpy(city->cityName, city_neighbour_name);
                city->longitude = longitude_distance;
                city->latitude = latitude_distance;
                city->distanceFromStart = 100000;
                city->distanceToGoal = 100000;
                city->neighbour = newList(compare_function, printCity);

                //add city to map
                addList(map, city);

                //print result of the city
                printf("A City of %s is found.\n", city_neighbour_name);
            }
            else if(num == 2)
            {
                //neighbour found add to neighbour list
                //printf("%s %d %d\n", neighbour_name, distance_1, distance_2);
                neighbour = (Neighbour *)malloc(sizeof(Neighbour));
                neighbour->city_Name = city_neighbour_name;
                //neighbour->distance = (longitude_distance + latitude_distance) ;
                strcpy(neighbour->city_Name, city_neighbour_name);
                neighbour->city = 0; //newList(compare_function, printCity);

                addList(city->neighbour, neighbour);

                printf("A Neighbour of %s is found\n", city_neighbour_name);
            }
            else
            {
                //status.ERRUNKNOWN;
            }
        }

        //foreach loop to assign cities
        myFunctionLoop(map);

    //close the file resource
    fclose(franceFile);
}

void myFunctionLoop(List *map)
{

    Node *node = map->head;
    Node *neighbourNode;
    City *currentCity;
    Neighbour *currentNeighbour;

    while (node)
    {
        // loop through all cities
        currentCity = (City *)node->val;

        neighbourNode = (Node *)currentCity->neighbour;	// this is list of neighbours

        while (neighbourNode)
        {
            // loop through all neighbours
            currentNeighbour = (Neighbour *)neighbourNode->val;
            currentNeighbour->city = findCityByName(map, currentNeighbour->city_Name);
            neighbourNode = neighbourNode->next;
        }

        node = node->next;
    }
}

//find a city by its name to check its duplication
City *findCityByName(List *map, char *name_of_city)
{
    Node *node = map->head;
    while (node)
    {
        City *city = (City *)node->val;
        if (strcmp(city->cityName, name_of_city) == 0)
        {
            return city;
        }
        node = node->next;
    }
    return 0;
}

int main()
{
    searchCityNeighbours();
    return 0;
}
