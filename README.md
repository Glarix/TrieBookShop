CODREANU DAN GRUPA 311CB
TEMA 3 - Biblioteca Online

Punctaj obtinut la teste pe calculator propriu:
TOTAL: 135/135
BONUS: 20/20

Tema se ruleaza cu comanda ./tema3 in_file out_file
in_file -- fisierul cu datele de intrare
out_file -- fisierul cu datele obtinute in urma rularii programului

Implementarea temei:

Functia citesteInput este folosita pentru citirea rand cu rand a fisierului de intrare si obtinerea si
gestionarea fiecarei operatii.


Fisierul reading.c contine implementarile functiilor de citire a informatiilor din input.


Operatia add_book este efectuata de functiile:

-- read_add -- care obtine informatiile despre carte si le stocheaza in structura de informatii.

-- addT1 -- care stocheaza in trie tip T1 cartea cu informatiile primite.

-- addT2 -- care stocheaza in trie tip T2 autorul cartii si formeaza trie tip T1 aferenta autorului cu
cartile acestuia.


Operatia de search_book este efectuata de functiile:

-- read_search -- care obtine criteriul de cautare al cartii din input

-- search -- care cauta cartea in trie de tip T1 dupa numele acesteia

-- search_prefix -- care cauta in T1 cel mult 3 carti ale caror titlu incepe cu prefixul primit 


Operatia de list_author este efectuata de functiile:

-- read_list_author -- care obtine informatiile necesare despre un autor

-- findAuthorCollection -- care gaseste trie T1 aferenta numelui unui autor daca acesta exista

-- showAuthorCollection -- care printeaza denumirile tuturor cartilor care apartin acelui autor

-- list_author_prefix si search_prefix -- care determina daca in trie exista autori al caror nume contin prefixul dat
si printeaza numele a primilor maxim 3 astfel de autori


Operatia de search_by_author este efectuata de functiile:

-- read_search_by_author -- care obtine din input informatiile necesare efectuarii operatiilor

-- findAuthorCollection si search_prefix -- 

-- search_by_author -- care cauta cartea cu numele dat scrisa de autorul cu numele dat

-- list_author_prefix --


Operatia de delete_book este efectuata de functiile:

-- read_delete_book -- care obtine denumirea cartii ce trebuie stearsa

-- delete_word -- care elimina nodul terminal al unui cuvant din trie daca acesta exista

-- free_empty_T1 si free_empty_T1V2 -- care elibereaza memoria pentru un trie T1 respectiv, trie T1 aferent cuvant din trie T2
care nu contin noduri terminale

-- is_trie_empty -- care determina daca un trie are noduri terminale

Eliberarea memoriei prin functiile:

-- free_T1 si free_T2 -- care elibereaza trie tip T1/T2
