#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "hash.h"

int readWord(FILE *fd, char *buffer)
{
	int c;
	
	do {
		c = fgetc(fd);				
		if(c == EOF)
			return 0;
	} while(!isalpha(c));

	do {
		*buffer = c;
		buffer++;
		c = fgetc(fd);
		if(c == 146)
			c = '\'';
	} while(isalpha(c) || c == '\'');

	*buffer = '\0';
}

// ubacuje sve rijeci u tablicu
void fillTable(HashTable *dict)
{
	FILE *fd;
	char buffer[1024];
				
	fd = fopen("big.txt", "rt");
	if(fd == NULL)
	{
		printf("Error opening file.\n");
		return;
	}
	
	while(readWord(fd, buffer))
	{
		//printf("%s\n", buffer);
		if(!Get(dict, buffer))	// vraca 0 ili jedan, ovisno da li rijec postoji u tablici
			Insert(dict, strdup(buffer));
	}

	fclose(fd);
}

void main()
{
	int i, size;
	HashTable *dict;

	// ispunja hash tablice razlicitih velicina svim rijecima iz datoteke
	for(size = 256; size < (1<<18); size *= 2)
	{
		float st, et;
		dict = NewTable(size);
		st = clock();
		fillTable(dict);
		
//		PrintTable(dict);

		
		et = clock();
		printf("Size = %d, load factor = %f, time = %f\n", dict->size, (float)dict->load / dict->size, (et-st)/CLOCKS_PER_SEC);
		DeleteTable(dict);
		
	}
}