#include "bubblesort.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void bubblesort(void *a,int arr_size, int space, int (*cmp)(const void *, const void *))
{
    char *arr = (char *) a;
    char *temp = malloc(space); 
    if(arr == NULL) 
    {
        printf("kein Speicherplatz vorhanden");
        exit(1);
    }  
    for (int i = arr_size; i > 1; --i) 
    {
        for (int j = 0; j < i - 1; ++j)
        {
            if(cmp(arr + (j*space),arr + ((j+1) * space)) > 0) 
            {
                memcpy(temp, arr + (j+1) * space, space);
                memcpy(arr + (j+1) * space, arr + j * space, space);
                memcpy(arr + j * space, temp, space);
            } 
        } 
    }
    free(temp); 
}