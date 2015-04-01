#ifndef DICTIONARY_H
#define DICTIONARY_H

typedef struct Word {
	char *word; // rijec
	int count; // broj pojavljivanja rijeci
	struct Word *next;
} Word;

typedef Word* Dictionary;

// kreira novi prazni rjecnik
Dictionary create();

// dodaje rijec ili uvecava broj pojavljivanja rijeci u rjecniku
// rijeci se dodaju u abecednom redu
void add(Dictionary dict, char *str);

//filtriranje Dictionarya
int filter(Word *w);

// ispisuje sve rijeci i broj pojavljivanja svake rijeci
void print(Dictionary dict);

// briše cijeli rjeènik
void destroy(Dictionary dict);

#endif