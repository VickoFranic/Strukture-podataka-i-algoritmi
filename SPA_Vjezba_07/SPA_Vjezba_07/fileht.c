#include "fileht.h"

#define HCONST 3567891

unsigned int hash_fd(char *word)
{
	// od kljuca generira hash kod na 32 bita
	unsigned int key = 0;
	while (*word != '\0') {
		key = key*HCONST + *word;
		word++;
	}
	return key;
}

