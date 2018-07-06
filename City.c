#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
    int num, distance_1, distance_2;
    char neighbour_name[128];
    char city_name[128];

    //create a pointer to the file
    FILE *franceFile;
    franceFile = fopen("FRANCE.MAP", "r");

    //int elt1, elt2;

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
        while((num = fscanf(franceFile, "%s %d %d", city_name, &distance_1, &distance_2)) != EOF)
        {
            if(num == 3)
            {
                //city found so add to city list
                city = (City *)malloc(sizeof(City));
                city->longitude = distance_1;
                city->latitude = distance_2;
                city->distanceFromStart = 100000;
                city->distanceToGoal = 100000;
                city->neighbour = newList(compare_function, printCity);

                //add city to map
                addList(map, city);

                //print result of the city
                printf("These are the Cities found %s\n", city_name);
            }
            else if(num == 2)
            {
                //neighbour found add to neighbour list
                //printf("%s %d %d\n", neighbour_name, distance_1, distance_2);
                neighbour = (Neighbour *)malloc(sizeof(Neighbour));
                neighbour->city_Name = city_name;
                neighbour->distance = distance_1 + distance_2 ;
                neighbour->city = newList(compare_function, printCity);

                addList(map, neighbour);

                printf("These are the Neighbours found %s\n", neighbour_name);//must I use neighbour_name or city_name?
            }
            else
            {
                //status.ERRUNKNOWN;
            }
        }
    }

    //close the file resource
    fclose(franceFile);
}

int main()
{
    searchCityNeighbours();
    return 0;
}
