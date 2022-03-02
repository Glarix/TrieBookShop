#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "tries.h"
#include "reading.h"


void citesteInput(char *numeFisier, char *numeFisierOut, T1 rootT1, T2 rootT2)
{
    FILE *f;
    char *line = NULL;
    size_t len = 0;

    //deschiderea fisierului de intrare
    f = fopen(numeFisier, "rt");
    if (f == NULL)
        return;

    while (getline(&line, &len, f) != -1)
    {
        char *comanda = strtok(line, " ");

        if (!strcmp(comanda, "add_book"))
        {
            read_add(&rootT1, &rootT2);
        }
        else if (!strcmp(comanda, "search_book"))
        {
            read_search(&rootT1, numeFisierOut);
        }
        else if (!strcmp(comanda, "list_author"))
        {
            read_list_author(&rootT2, numeFisierOut);
        }
        else if (!strcmp(comanda, "search_by_author"))
        {
            read_search_by_author(&rootT2, numeFisierOut);
        }
        else if (!strcmp(comanda, "delete_book"))
        {
            read_delete_book(&rootT1, &rootT2, numeFisierOut);
        }
    }

    fclose(f);
    if (line)
        free(line); //eliberarea memoriei pentru line
}

int main(int argc, char *argv[])
{

    T1 rootT1 = AllocT1();
    T2 rootT2 = AllocT2();

    citesteInput(argv[1], argv[2], rootT1, rootT2);
    
    free_T1(&rootT1);
    free_T2(&rootT2);
    return 0;
}