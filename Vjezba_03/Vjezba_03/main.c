#include <stdio.h>
#include <ctype.h>
#include "dictionary.h"

int readWord(FILE *fd, char *buffer)
{
	int c;

	do {
		c = fgetc(fd);
		if (c == EOF)
			return 0;
	} while (!isalpha(c));

	do {
		*buffer = tolower(c);
		buffer++;
		c = fgetc(fd);
		if (c == 146)
			c = '\'';
	} while (isalpha(c) || c == '\'');

	*buffer = '\0';
}

void main()
{
	FILE *fd;
	char buffer[1024];
	Dictionary dict;

	fd = fopen("liar.txt", "rt");
	if (fd == NULL)
	{
		printf("Error opening file.\n");
		return;
	}

	dict = create(); // kreiraj novi Dictionary
	while (readWord(fd, buffer))
	{
		add(dict, buffer); // dodaj rijec u Dictionary
	}

	fclose(fd);

	filterDictionary(dict, filter);

	print(dict);

	destroy(dict);
}