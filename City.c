#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "City.h"
#include "status.h"


int compare_function (void *elet_1, void *elet_2)
{
    int *el_a = (int*) elet_1;
    int *el_b = (int*) elet_2;

    return (*el_a > *el_b) - (*el_a < *el_b);
}

void printCity(void *element)
{
    City *city = (City *)element;
    printf("%s\n", city->cityName);
}

bool isFileNull(FILE *fileName)
{
    if (fileName == NULL)
    {
        return true;
    }
    return false;
}

void searchCityNeighbours()
{
//    char scanf_city[128];
//    int scanf_dist_x;
//    int scanf_dist_y;
//
//    FILE *file = fopen("FRANCE.MAP", "r");
//    fscanf(file, "%s %d %d", scanf_city, &scanf_dist_x, &scanf_dist_x);
//    printf("We found: %s %d %d\n", scanf_city, scanf_dist_x, scanf_dist_y);

    int num, distance_1, distance_2;
    char neighbour_name[128];
    char city_name[128];

    //create a pointer to the file
    FILE *franceFile;
    franceFile = fopen("FRANCE.MAP", "r");

    int elt1, elt2;

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
                //printf("%s %d %d\n", city_name, distance_1, distance_2);
                 printf("print this string %s\n", city_name);
            }
            else if(num == 2)
            {
                //neighbour found add to neighbour list
                //printf("%s %d %d\n", neighbour_name, distance_1, distance_2);
                 printf("print this string %s\n", city_name);
            }
            else
            {
                //error
            }
        }
    }

    //close the file resource
    fclose(franceFile);
}

int main()
{
    //printf("Hello world!\n");
    searchCityNeighbours();
    return 0;
}
