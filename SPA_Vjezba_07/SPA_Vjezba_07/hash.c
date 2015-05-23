#include "hash.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

/*
Implementirati funkcije za rjeènik napravljen pomoæu hash tablice (opis funkcija u kôdu). Kolizije se rješavaju vezanom listom u svakom pretincu.
*/

#define HCONST 3567891

unsigned int hash(char *word)
{
	// od kljuca generira hash kod na 32 bita
	unsigned int key = 0;
	while (*word != '\0') {
		key = key*HCONST + *word;
		word++;
	}
	return key;
}

HashTable *NewTable(int size)
{
	// kreira novu hash tablicu (alocira samu strukturu i niz pokazivaèa)
	// postaviti sve pretince (pokazivaèe) na NULL
	int i = 0;
	HashTable* ht;

	ht = (HashTable*)malloc(sizeof(HashTable));
	ht->size = size;
	ht->load = 0;
	ht->table = malloc((sizeof(Bin)) * size);	// velicina jednog elementa * koliko ih ima u tablici

	for (i; i < ht->size; i++) {
		ht->table[i] = NULL;
	}
	return ht;
}

int Get(HashTable *ht, char *word)
{
	// vraca 0 ili 1 ovisno o tome da li rijec postoji u tablici
	unsigned int kljuc;
	int i = 0;
	Bin* it;

	kljuc = hash(word) % ht->size;
	it = ht->table[kljuc];

	if (it == NULL)
		return 0;	// nema nista u pretincu
	else if (it != NULL) {	// ima nesto
		while (it != NULL) {
			if (strcmp(word, it->word) == 0)	// rijec postoji u pretincu
				return 1;

			it = it->next;
		}
	}
	else
		return 0;
}

void Insert(HashTable *ht, char *word)
{
	// dodaje novu rijec u listu na odgovarajucem pretincu
	// povecava load tablice
	unsigned int kljuc;
	Bin* novi; 
	novi = malloc(sizeof(Bin));

	novi->word = word;
	novi->next = NULL;

	kljuc = hash(word) % ht->size;

	if (ht->table[kljuc] == NULL)
		ht->table[kljuc] = novi;
	else {
		novi->next = ht->table[kljuc];
		ht->table[kljuc] = novi;
	}
}

void PrintTable(HashTable* ht) {
	Bin* tmp;
	int i = 0;

	while (i < ht->size) {
		tmp = ht->table[i];
		printf("PRETINAC: %d\n", i);
		while (tmp != NULL) {
			printf("%s\n", tmp->word);
			tmp = tmp->next;
		}
		i++;
	}
}

void DeleteTable(HashTable *ht)
{
	// brise cijelu hash tablicu: liste na svim pretincima (rijec i element liste), pretince i samu hash tablicu
}