/*CODREANU DAN GRUPA 311CB*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>


#ifndef _TRIE_
#define _TRIE_

#define ALPH_LEN 68


typedef struct carteInfo
{
    char* titlu;
    char* autor;
    int rating;
    int pagini;
}infoCarte, *CInfo;


typedef struct trie1
{
    struct trie1* Map[ALPH_LEN];
    CInfo info;
}Trie1, *T1;

typedef struct trie2
{
    struct trie2* Map[ALPH_LEN];
    T1 author_books;
}Trie2, *T2;

int LetterIndex(const char letter); // Functie care determina indexul pe care ar trebui sa se afle un caracter

int isPoints(char* string);

T1 AllocT1(); // Functia aloca o celula de tip T1

T2 AllocT2(); // Functia aloca o celula de tip T2

int addT1(T1 rootT1, CInfo info_book); // Functia adauga o carte in T1

int addT2(T2 rootT2, CInfo info_book); // Functia adauga o carte in T2

void add_book(CInfo info_book1, CInfo info_book2, T1 rootT1, T2 rootT2); // Functia adauga o carte in ambele structuri

void search(const char* title, T1 rootT1, char* numeFisierOut); // Functie de cautare a unei carti dupa titlu

T1 findAuthorCollection(T2 rootT2, char* authorName, char* numeFisierOut); // Functia care intoarce colectia de carti a unui autor

void showAuthorCollection(T1 authorCollection, char* numeFisierOut); // Functia primeste colectia de carti a unui autor si le afiseaza in ordine lexicografica

void search_by_author(char* numeFisierOut, T2 rootT2, char* name, char* title); // Functia cauta cartea cu titlul dat al unui autor

void showSearch_prefix(T1 prefixedT1, char *numeFisierOut, int* booksShown, int* found);

void search_prefix(char *numeFisierOut, char *prefix, T1 rootT1); // Functia primeste un prefix de titlu si afiseaza cartile care incep cu acel prefix(maxim 3)

void show_author_prefix(T2 prefixedT2, char *numeFisierOut, int* authorsShown, char auth_name[50], int auth_index, int*found);

void list_author_prefix(char *numeFisierOut, char *prefix, T2 rootT2); // Functia primeste un prefix din nume si afiseaza autorii cu acel inceput de nume(maxim 3)

char* delete_word(T1 rootT1, char* title, char* numeFisierOut); // Functie ce elimina o carte dintr-o trie

void free_empty_T1(T1* rootT1); // Functie de eliberare trie T1 daca acesta nu contine noduri terminale

void free_empty_T1V2(char* name, T2 rootT2); // Functie de eliberare a unui trie tip T1 aferent unui cavant din T2
                                            // daca acesta nu contine noduri terminale

int is_trie_empty(T1 rootT1); // Functia verifica daca un trie nu are noduri terminale
                            // Intoarce: 1 - nu are noduri terminale/ 0 - are noduri terminale

void free_T1(T1 *rootT1); // Functie de eliberare a unui trie tip T1

void free_T2(T2 *rootT2); // Functie de eliberare a unui trie tip T2
#endif