#ifndef FILEHT_H
#define FILEHT_H
#include <stdio.h>

// svaki pretinac sadrži hash kljuc rijeci i offset unutar 
// neke tekstualne datoteke sa rijecima.
// offset < 0 znaci da pretinac nije ispunjen
// offset >= 0 znaci da se rijec nalazi u tekstualnoj datoteci na tom offsetu (do kraja linije)
typedef struct {
	unsigned int hcode;
	int offset;
} FileBin;

// tablica je sastavljena od dvije datoteke
// fd_bins - binarna datoteka koja sadrži zapise struktura FileBin
// fd_words - tekstualna datoteka koja sadrzi po jednu rijec u svakoj liniji
typedef struct {
	FILE *fd_bins;
	FILE *fd_words;
	int size, load;
} FileHT;

unsigned int hash_fd(char *word);

// otvara obje datoteke hash tablice
// ispunja binarnu datoteku sa pretinicima { hcode = 0, offset = -1 }
FileHT *NewFileHT(int size);

// dodaje rijec u pretinac
// ako je pretinac vec zauzet, linearno trazi iduci prazni pretinac
// ako je tablica puna, ispisati gresku i vratiti 0
int InsertFileHT(FileHT *ht, char *word);

// trazi rijec u tablici
// ako je pretinac zauzet, linearnom pretragom provjerava 
// sve pretince od njega pa nadalje (do praznog pretinca)
int GetFileHT(FileHT *ht, char *word);

#endif