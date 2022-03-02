/*CODREANU DAN GRUPA 311CB*/
#include "tries.h"
// Functii de citire a informatiilor din fisier

#ifndef _READING_
#define _READING_


void read_add(T1* rootT1, T2* rootT2); // Pentru comanda add_book

void read_search(T1* rootT1, char* numeFisierOut); // Pentru comanda search_book

void read_list_author(T2* rootT2, char* numeFisierOut); // Pentru comanda list_author

void read_search_by_author(T2* rootT2, char* numeFisierOut); // Pentru comanda search_by_author

void read_delete_book(T1* rootT1, T2* rootT2, char* numeFisierOut); // Pentru comanda delete_book
#endif