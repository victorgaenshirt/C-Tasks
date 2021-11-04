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
void bubblesort(char **arr, int arr_size);

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

    int arr_size = atoi(argv[1]); //statt Integer.parseInt
    //---------------------------------------------------- Zahlen einlesen
    char **arr =(char**) malloc(sizeof (char*) * arr_size);
    if(arr == NULL)
    {
        printf("kein Speicherplatz vorhanden");
        return 1;
    }

    int max = strlen(argv[1]) + 1;
    int outlen = 0;
    srand((unsigned int) time(NULL));
    
    printf("Unsortiertes Array: \n");
    for(int i = 0; i < arr_size; ++i)
     
    {
        int random = rand()%arr_size +1;
        arr[i] = (char*) malloc(max);
        if(arr[i] == NULL)
        {
        printf("kein Speicherplatz vorhanden");
        return 1;
        }
        sprintf(arr[i], "%d", random);
        printf("%s ", arr[i]);
        outlen += strlen(arr[i]) + 1;
      
    }

    printf("\n");
    
    bubblesort(arr, arr_size);

    char *outputstr = (char*) malloc(outlen);
    if(outputstr == NULL)
    {
    printf("kein Speicherplatz vorhanden");
    return 1;
    }
    strcpy(outputstr, arr[0]);
    for(int i = 1; i < arr_size; ++i)
    {
        if(strcmp(arr[i], arr[i-1]) == 0)
        {
            strcat(outputstr, "*");
        }
        else
        {
            strcat(outputstr, " ");
            strcat(outputstr, arr[i]);
        }
    } 
    printf("Sortiertes Array: \n");
    printf("%s", outputstr);
    for(int i = 0; i < arr_size; ++i) 
    {
        free(arr[i]);
    }
    free(arr);
    free(outputstr);
}               


void bubblesort(char *arr[], int arr_size)
{
     for (int i = arr_size; i > 1; --i) {
            // groessten Wert nach hinten schieben
            for (int j = 0; j < i - 1; ++j) {
                if (strcmp(arr[j],arr[j + 1]) > 0) {
                    // Werte tauschen
                    char *tmp = arr[j + 1];
                    arr[j + 1] = arr[j];
                    arr[j] = tmp;
            } 
        } 
    }        
}    