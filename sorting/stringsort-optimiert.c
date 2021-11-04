// Stringsort.c
/**
 * Stringsort erzeugt zufällige Ziffernstrings und gibt sie alphabetisch sortiert aus
 * @author V.Gaenshirt
 * @version 21.11.2019
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "bubblesort.h"

/**
 * argc ist der C-Ersatz für die Instanzvariable args.length
 */
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Aufruf: c Stringsort Anzahl\n");
        return 0;
    }

    int arr_size = atoi(argv[1]); 
    int space = strlen(argv[1])+1;
    char *arr =(char*) malloc(space * arr_size);
    if(arr == NULL) 
    {
        printf("kein Speicherplatz vorhanden");
        return 1;
    }


    srand((unsigned int) time(NULL));
    
    printf("Unsortiertes Array: \n");
    for(int i = 0; i < arr_size; ++i) 
    {
        int random = rand()%arr_size;
        sprintf(arr + (i * space), "%d", random);
        printf("%s ", arr + (i * space));      
    }

    printf("\n");
    bubblesort(arr, arr_size, space, (int (*)(const void *, const void *))strcmp);

    char *outputstr = (char*) malloc(space * arr_size);
    if(outputstr == NULL)
    {
    printf("kein Speicherplatz vorhanden");
    return 1;
    }
    
    strcpy(outputstr, arr);
    for(int i = 1; i < arr_size; ++i)
    {
        if(strcmp(arr + (i * space), arr + (i * space) - space) == 0)
        {
            strcat(outputstr, "*");
        }
        else
        {
            strcat(outputstr, " ");
            strcat(outputstr, arr + (i * space));
        }
    } 
    printf("Sortiertes Array: \n");
    printf("%s", outputstr);
    printf("\n");

    free(arr);
    free(outputstr);               

}

  