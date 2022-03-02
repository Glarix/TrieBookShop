/*CODREANU DAN GRUPA 311CB*/
#include "tries.h"

int LetterIndex(const char letter)
{
    const char *letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
    int index;

    for (index = 0; index < ALPH_LEN; index++)
    {
        if (letter == letters[index])
            return index;
    }
    return -1;
}

char IndexToLetter(int index)
{
    const char *letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
    return letters[index];
}

void FreeInfo(CInfo to_free) // functia elibereaza memoria ocupata de o celula cu informatii
{
    free(to_free->titlu);
    free(to_free->autor);
    free(to_free);
    to_free = NULL;
}

int EmptyArray(struct trie1 *Map[ALPH_LEN])
{
    int i;
    for (i = 0; i < ALPH_LEN; i++)
    {
        if (Map[i])
            return 0;
    }
    return 1;
}

int isPoints(char* string) // Functia verifica daca un sir contine sau nu caracterul ':'
{
    int len = strlen(string);
    int i;
    for ( i = 0; i < len; i++)
    {
        if (string[i] == ':')
        {
            return 1;
        }
    }
    return 0;
}

T1 AllocT1()
{
    T1 book_collection;
    book_collection = (T1)malloc(sizeof(Trie1));
    if (!book_collection)
        return NULL;

    book_collection->info = NULL;
    int i;
    for (i = 0; i < ALPH_LEN; i++)
    {
        book_collection->Map[i] = NULL; // Setarea initiala a fiecarui pointer din array la NULL
    }

    return book_collection;
}

T2 AllocT2()
{
    T2 Author;
    Author = (T2)malloc(sizeof(Trie2));
    if (!Author)
        return NULL;

    Author->author_books = NULL;
    int i;
    for (i = 0; i < ALPH_LEN; i++)
    {
        Author->Map[i] = NULL; // Setarea initiala a fiecarui pointer din array la NULL
    }
    return Author;
}

int addT1(T1 rootT1, CInfo info_book)
{
    const char *title = info_book->titlu;
    int title_len = strlen(title);
    int depth;
    int index;

    T1 aux = rootT1;
    for (depth = 0; depth < title_len; depth++) // Pentru fiecare litera din cuvant se creeaza o celula noua spre care
                                                //pointeaza pointerul cu indexul potrivit din array
    {
        index = LetterIndex(title[depth]);
        if (!aux->Map[index])
        {
            aux->Map[index] = AllocT1();
        }

        aux = aux->Map[index];
    }
    if (!aux->info)
    {
        aux->info = info_book; // La ultima celula se face legatura catre structura cu informatiile cartii
    }
    else
    {
        FreeInfo(info_book);
    }

    return 1;
}

int addT2(T2 rootT2, CInfo info_book)
{
    const char *author = info_book->autor;
    int author_len = strlen(author);
    int depth;
    int index;

    T2 aux = rootT2;
    for (depth = 0; depth < author_len; depth++)
    {
        index = LetterIndex(author[depth]);
        if (!aux->Map[index])
        {
            aux->Map[index] = AllocT2();
        }

        aux = aux->Map[index];
    }

    if (!aux->author_books) // Daca nu exista un T1 la sfarsitul numelui unui autor se creeaza unul
    {
        T1 author_books = AllocT1();
        aux->author_books = author_books;
    }

    addT1(aux->author_books, info_book); // Se adauga cartea in T1 corespunzator autorului
    return 1;
}

void add_book(CInfo info_book1, CInfo info_book2, T1 rootT1, T2 rootT2)
{
    addT1(rootT1, info_book1);
    addT2(rootT2, info_book2);
}

void search(const char *title, T1 rootT1, char *numeFisierOut)
{
    FILE *f;
    //deschiderea fisierului cu optiunea append
    f = fopen(numeFisierOut, "at");
    if (f == NULL)
        return;

    int title_len = strlen(title);
    int depth;
    int index;

    T1 aux = rootT1;
    for (depth = 0; depth < title_len; depth++)
    {
        index = LetterIndex(title[depth]);
        if (!aux->Map[index]) // Daca o litera din denumirea cartii nu este prezenta in T1 cartea nu exista
        {
            fprintf(f, "Cartea %s nu exista in recomandarile tale.\n", title);
            fclose(f);
            return;
        }

        aux = aux->Map[index];
    }
    if (!aux->info) // Daca celula finala nu are o legatura catre o structura cu informatii, cartea nu exista
    {
        fprintf(f, "Cartea %s nu exista in recomandarile tale.\n", title);
        fclose(f);
        return;
    }
    else
    {
        fprintf(f, "Informatii recomandare: %s, %s, %d, %d\n", aux->info->titlu, aux->info->autor, aux->info->rating, aux->info->pagini);
        fclose(f);
        return;
    }
}

T1 findAuthorCollection(T2 rootT2, char *authorName, char *numeFisierOut)
{
    FILE *f;
    //deschiderea fisierului cu optiunea append
    f = fopen(numeFisierOut, "at");
    if (f == NULL)
        return NULL;

    T2 aux = rootT2;

    int name_len = strlen(authorName);
    int depth;
    int index;
    for (depth = 0; depth < name_len; depth++)
    {
        index = LetterIndex(authorName[depth]);
        if (!aux->Map[index]) // Daca o litera din numele autorului nu este prezenta in calea sa din T2, autorul nu exista
        {
            fprintf(f, "Autorul %s nu face parte din recomandarile tale.\n", authorName);
            fclose(f);
            return NULL;
        }

        aux = aux->Map[index];
    }
    if (aux->author_books)
    {
        fclose(f);
        return aux->author_books;
    }
    fprintf(f, "Autorul %s nu face parte din recomandarile tale.\n", authorName);
    fclose(f);
    return NULL;
}

void showAuthorCollection(T1 authorCollection, char *numeFisierOut)
{
    T1 aux = authorCollection;

    if (aux->info) // Daca e o celula terminala se afiseaza titlul cartii
    {
        FILE *f;
        //deschiderea fisierului cu optiunea append
        f = fopen(numeFisierOut, "at");
        if (f == NULL)
            return;
        fprintf(f, "%s\n", aux->info->titlu);
        fclose(f);
    }

    int i;
    for (i = 0; i < ALPH_LEN; i++) // Fiecare cale se parcurge recursiv pana toate cartile din T1 sunt afisate
    {
        if (aux->Map[i])
        {
            T1 extraAux = aux->Map[i];
            showAuthorCollection(extraAux, numeFisierOut);
        }
    }
}

void search_by_author(char *numeFisierOut, T2 rootT2, char *name, char *title)
{
    T1 authorCollection = findAuthorCollection(rootT2, name, numeFisierOut);
    if (authorCollection)
    {
        search(title, authorCollection, numeFisierOut);
    }
}

void showSearch_prefix(T1 prefixedT1, char *numeFisierOut, int *booksShown, int *found)
{
    if (*booksShown > 2) // Daca s-au afisat 3 carti nu se mai afiseaza nici o carte
        return;
    T1 aux = prefixedT1;

    if (aux->info) // La ajungerea la un nod terminal se afiseaza denumirea cartii
    {
        FILE *f;
        //deschiderea fisierului cu optiunea append
        f = fopen(numeFisierOut, "at");
        if (f == NULL)
            return;
        fprintf(f, "%s\n", aux->info->titlu);
        fclose(f);
        *booksShown += 1;
        *found = 1;
    }

    int i;
    for (i = 0; i < ALPH_LEN; i++) // Se parcurge recursiv fiecare carte din T1
    {
        if (aux->Map[i])
        {
            T1 extraAux = aux->Map[i];
            showSearch_prefix(extraAux, numeFisierOut, booksShown, found);
        }
    }
}

void search_prefix(char *numeFisierOut, char *prefix, T1 rootT1)
{
    T1 aux = rootT1;

    int prefix_len = strlen(prefix);
    int depth;
    int index;
    for (depth = 0; depth < prefix_len; depth++) // Daca prefixul exista se ajunge la nodul urmator dupa prefix
    {
        index = LetterIndex(prefix[depth]);
        if (!aux->Map[index])
        {
            FILE *f;
            //deschiderea fisierului cu optiunea append
            f = fopen(numeFisierOut, "at");
            if (f == NULL)
                return;
            fprintf(f, "Nicio carte gasita.\n");
            fclose(f);
            return;
        }
        aux = aux->Map[index];
    }
    int a = 0, found = 0;
    int *j = &a; // Counter pentru numarul de carti afisate
    showSearch_prefix(aux, numeFisierOut, j, &found);
    if (!found)
    {
        FILE *f;
        //deschiderea fisierului cu optiunea append
        f = fopen(numeFisierOut, "at");
        if (f == NULL)
            return;
        fprintf(f, "Nicio carte gasita.\n");
        fclose(f);
        return;
    }
}

void show_author_prefix(T2 prefixedT2, char *numeFisierOut, int *authorsShown, char auth_name[50], int auth_index, int* found)
{
    if (*authorsShown > 2) // Daca au fost afisati 3 autori
        return;

    T2 aux = prefixedT2;

    if (aux->author_books) // Daca este nod terminal se printeaza numele autorului din auth_name
    {
        FILE *f;
        //deschiderea fisierului cu optiunea append
        f = fopen(numeFisierOut, "at");
        if (f == NULL)
            return;
        int num;
        for (num = 0; num < auth_index; num++)
        {
            fprintf(f, "%c", auth_name[num]);
        }
        fprintf(f, "\n");
        fclose(f);
        *authorsShown += 1;
        *found = 1;
    }

    int i;
    for (i = 0; i < ALPH_LEN; i++)
    {
        // Se parcurge fiecare nod ce contine caractere si se obtine caracterul corespunzator indexului
        // caracterul fiind inserat in auth_name
        if (aux->Map[i])
        {
            char addChar = IndexToLetter(i);
            auth_name[auth_index] = addChar;
            auth_index++;
            T2 extraAux = aux->Map[i];
            show_author_prefix(extraAux, numeFisierOut, authorsShown, auth_name, auth_index, found);
            auth_index--;
        }
    }
}

void list_author_prefix(char *numeFisierOut, char *prefix, T2 rootT2)
{
    T2 aux = rootT2;
    int prefix_len = strlen(prefix);
    int depth;
    int index;
    char auth_name[50];
    int auth_index = 0;
    for (depth = 0; depth < prefix_len; depth++) // Deplasarea pana la nodul de dupa prefix
    {
        index = LetterIndex(prefix[depth]);
        if (!aux->Map[index])
        {
            FILE *f;
            //deschiderea fisierului cu optiunea append
            f = fopen(numeFisierOut, "at");
            if (f == NULL)
                return;
            fprintf(f, "Niciun autor gasit.\n");
            fclose(f);
            return;
        }
        aux = aux->Map[index];
    }
    for (; auth_index < prefix_len; auth_index++) // Completarea array-ului cu prefixul numelui autorului
    {
        auth_name[auth_index] = prefix[auth_index];
    }
    int a = 0, found = 0;
    int *j = &a; // Counter pentru numarul de autori afisati
    show_author_prefix(aux, numeFisierOut, j, auth_name, auth_index, &found);
    if (!found)
    {
        FILE *f;
        //deschiderea fisierului cu optiunea append
        f = fopen(numeFisierOut, "at");
        if (f == NULL)
            return;
        fprintf(f, "Niciun autor gasit.\n");
        fclose(f);
        return;
    }
}

char* delete_word(T1 rootT1, char *title, char *numeFisierOut)
{
    int title_len = strlen(title);
    int depth;
    int index;
    T1 aux = rootT1;
    for (depth = 0; depth < title_len; depth++)
    {
        index = LetterIndex(title[depth]);
        if (!aux->Map[index]) // Daca o litera din denumirea cartii nu este prezenta in T1 cartea nu exista
        {
            FILE *f;
            //deschiderea fisierului cu optiunea append
            f = fopen(numeFisierOut, "at");
            if (f == NULL)
                return NULL;
            fprintf(f, "Cartea %s nu exista in recomandarile tale.\n", title);
            fclose(f);
            return NULL;
        }

        aux = aux->Map[index];
    }
    if (!aux->info) // Daca celula finala nu are o legatura catre o structura cu informatii, cartea nu exista
    {
        FILE *f;
        //deschiderea fisierului cu optiunea append
        f = fopen(numeFisierOut, "at");
        if (f == NULL)
            return NULL;
        fprintf(f, "Cartea %s nu exista in recomandarile tale.\n", title);
        fclose(f);
        return NULL;
    }
    else // Daca cartea exista, se salveaza numele ei si se elibereaza memoria din struct. de info. astfel nodul nu mai e terminal
    {
        char *name = malloc(strlen(aux->info->autor) + 1 * sizeof(char));
        strcpy(name, aux->info->autor);
        FreeInfo(aux->info);
        aux->info = NULL;
        return name;
    }
}

void free_empty_T1(T1 *rootT1)
{
    int i;
    if (!(*rootT1))
        return;

    for (i = 0; i < ALPH_LEN; i++)
    {
        free_empty_T1(&((*rootT1)->Map[i]));
    }

    free(*rootT1);
    *rootT1 = NULL;
}

void free_empty_T1V2(char *name, T2 rootT2)
{
    int name_len = strlen(name);
    int depth;
    int index;
    T2 aux = rootT2;

    for (depth = 0; depth < name_len; depth++) // Se verifica daca exista autorul 
    {
        index = LetterIndex(name[depth]);
        if (aux->Map[index])
        {
            aux = aux->Map[index];
        }
        else
            return;
    }

    free_empty_T1(&(aux->author_books)); // Eliberarea mem. ocupata de trie tip T1 aferent cuvantului din T2
}

int is_trie_empty(T1 rootT1)
{
    int i;
    if (!(rootT1))
        return 1;

    if (rootT1->info) // Daca este nod terminal se intoarce 0; 
    {
        return 0;
    }

    for (i = 0; i < ALPH_LEN; i++)
    {
        if (!is_trie_empty(rootT1->Map[i]))
            return 0;
    }
    return 1;
}

void free_T1(T1 *rootT1)
{
    int i;
    if (!(*rootT1))
        return;

    for (i = 0; i < ALPH_LEN; i++)
    {
        free_T1(&((*rootT1)->Map[i]));
    }

    if ((*rootT1)->info) //daca nodul este unul terminal, informatia despre carte se elibereaza 
    {
        FreeInfo((*rootT1)->info);
        (*rootT1)->info = NULL;
    }
    
    free(*rootT1);
    *rootT1 = NULL;
}

void free_T2(T2 *rootT2)
{
    int i;
    if (!(*rootT2))
        return;

    for (i = 0; i < ALPH_LEN; i++)
    {
        free_T2(&((*rootT2)->Map[i]));
    }
    
    if ((*rootT2)->author_books) // Daca nodul este terminal, se elibereaza trie tip T1 aferent acestuia
    {
        free_T1(&((*rootT2)->author_books));
        (*rootT2)->author_books = NULL;
    }

    free(*rootT2);
    *rootT2 = NULL;
}