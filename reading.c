/*CODREANU DAN GRUPA 311CB*/
#include "reading.h"

void read_add(T1 *rootT1, T2 *rootT2)
{
    char *title = strtok(NULL, ":");
    char *author = strtok(NULL, ":");
    char *rating = strtok(NULL, ":");
    char *pages = strtok(NULL, ":");

    // Crearea unei structuri cu informatiile obtinute despre carte
    CInfo info = (CInfo)malloc(sizeof(infoCarte));
    if (!info)
        return;
    info->titlu = (char *)malloc((strlen(title) + 1) * sizeof(char));
    info->autor = (char *)malloc((strlen(author) + 1) * sizeof(char));
    strcpy(info->titlu, title);
    strcpy(info->autor, author);
    info->rating = atoi(rating);
    info->pagini = atoi(pages);

    CInfo info2 = (CInfo)malloc(sizeof(infoCarte));
    if (!info2)
        return;
    info2->titlu = (char *)malloc((strlen(title) + 1) * sizeof(char));
    info2->autor = (char *)malloc((strlen(author) + 1) * sizeof(char));
    strcpy(info2->titlu, title);
    strcpy(info2->autor, author);
    info2->rating = atoi(rating);
    info2->pagini = atoi(pages);

    add_book(info, info2, *rootT1, *rootT2); // Adaugare carte in rootT1 si rootT2
}

void read_search(T1 *rootT1, char *numeFisierOut)
{
    char *title = strtok(NULL, "\n");
    if (title[strlen(title) - 1] == '\n')
        title[strlen(title) - 1] = '\0';
    if (title[strlen(title) - 1] == '\r')
        title[strlen(title) - 1] = '\0';

    char isTilda = title[strlen(title) - 1];

    if (isTilda != '~') // Verificare daca functia este una cu prefix sau nu
    {
        search(title, *rootT1, numeFisierOut); // Daca nu e cu prefix
    }
    else // Daca e cu prefix
    {
        title[strlen(title) - 1] = '\0'; // Eliminarea caracterului '~' din sir
        search_prefix(numeFisierOut, title, *rootT1);
    }
}

void read_list_author(T2 *rootT2, char *numeFisierOut)
{
    char *name = strtok(NULL, "\n");
    if (name[strlen(name) - 1] == '\n')
        name[strlen(name) - 1] = '\0';
    if (name[strlen(name) - 1] == '\r')
        name[strlen(name) - 1] = '\0';

    char isTilda = name[strlen(name) - 1];
    if (isTilda != '~') // Verificare daca functia este una cu prefix sau nu
    {
        // Obtinerea colectiei de carti a autorului dat, daca acesta exista
        T1 authorCollection = findAuthorCollection(*rootT2, name, numeFisierOut);
        if (authorCollection)
        {
            showAuthorCollection(authorCollection, numeFisierOut);
        }
    }
    else
    {
        name[strlen(name) - 1] = '\0'; // Eliminarea caracterului '~' din sir
        list_author_prefix(numeFisierOut, name, *rootT2);
    }
}

void read_search_by_author(T2 *rootT2, char *numeFisierOut)
{
    char *info = strtok(NULL, "\n");
    if (info[strlen(info) - 1] == '\n')
        info[strlen(info) - 1] = '\0';
    if (info[strlen(info) - 1] == '\r')
        info[strlen(info) - 1] = '\0';

    if (info[strlen(info) - 1] != '~') // Verificare daca '~' este prezenta la finalul sirului din input
    {
        char *name = strtok(info, ":");
        char *title = strtok(NULL, "\n");
        search_by_author(numeFisierOut, *rootT2, name, title);
    }
    else
    {
        if (isPoints(info)) // Verificare daca exista ':' in sir pentru a determina daca prefixul e pentru titlu de carte sau nume de autor
        {
            char *name = strtok(info, ":");
            char *title = strtok(NULL, "\n");
            title[strlen(title) - 1] = '\0'; // Eliminarea caracterului '~' din sir
            T1 authorCollection = findAuthorCollection(*rootT2, name, numeFisierOut);
            if (authorCollection)
            {
                search_prefix(numeFisierOut, title, authorCollection);
            }
        }
        else
        {
            info[strlen(info) - 1] = '\0'; // Eliminarea caracterului '~' din sir
            list_author_prefix(numeFisierOut, info, *rootT2);
        }
    }
}

void read_delete_book(T1 *rootT1, T2 *rootT2, char *numeFisierOut)
{
    char *title = strtok(NULL, "\n");
    if (title[strlen(title) - 1] == '\n')
        title[strlen(title) - 1] = '\0';
    if (title[strlen(title) - 1] == '\r')
        title[strlen(title) - 1] = '\0';

    char *name = delete_word(*rootT1, title, numeFisierOut); // Obtinerea numelui autorului cartii daca aceasta exista

    if (name)
    {
        T1 authorColl = findAuthorCollection(*rootT2, name, numeFisierOut);
        if (authorColl)
        {
            free(name);
            name = delete_word(authorColl, title, numeFisierOut); // Se sterge cartea si din trie aferent autorului
        }
        if (is_trie_empty(authorColl)) // Se verifica daca trie nu are noduri terminale, in cazz afirmativ este eliberata memoria
        {
            free_empty_T1V2(name, *rootT2);
        }
        free(name);
    }
}