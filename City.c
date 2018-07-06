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

void printCity(void *element){
    City *city = (City *)element;
    printf("%s\n", city->cityName);
}

bool isFileNull(char* fileName)
{
    if (fileName == NULL)
    {
        return true;
    }
}

void searchCityNeighbours()
{
    //create a pointer to the file
    FILE *franceFile;
    franceFile = fopen("FRANCE.MAP", "r");

    int elt1, elt2;

    List *map = newList(compare_function, printCity);

    //check if file is not null before reading contents
    if (isFileNull(franceFile) == true)
    {
        fprintf(stderr, "Can't open input file FRANCE.MAP!\n");
        exit(1);
    }
    else
    {
        //read through the file with a loop
        int num, distance_1, distance_2;
        char* city_name, neighbour_name;

        while((num = fscanf(franceFile, "%s %d %d")), !EOF)
        {
            if(num == 3)
            {
                //city found so add to city list
                fprintf(num, "%s %d %d\n", city_name, distance_1, distance_2);
            }
            else if(num == 2)
            {
                //neighbour found add to neighbour list
                fprintf(num, "%s %d %d\n", neighbour_name, distance_1, distance_2);
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
