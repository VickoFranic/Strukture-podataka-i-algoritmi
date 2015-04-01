#include "dictionary.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

// kreira novi prazni rjecnik
Dictionary create() {
	Dictionary rjecnik = (Word*)malloc(sizeof(Word));
	rjecnik->word = "Novi rjecnik";
	rjecnik->next = NULL;
	return rjecnik;
}

// dodaje rijec ili uvecava broj pojavljivanja rijeci u rjecniku
// rijeci se dodaju u abecednom redu
void add(Dictionary dict, char *str) {
	Word *novi, *tmp, *eq;
	int c;
	int d;

	char* tmp_str = strdup(str);

	novi = (Word*)malloc(sizeof(Word));
	novi->word = tmp_str;
	novi->count = 1;
	novi->next = NULL;

	tmp = dict;
	if (dict->next != NULL) {
		if (strcmp(tmp->next->word, novi->word) == 0) {
			tmp->next->count++;
		}
		if (strcmp(tmp->next->word, novi->word) < 0) {
			novi->next = tmp->next;
			tmp->next = novi;
		}
		if (strcmp(tmp->next->word, novi->word) > 0) {
			eq = NULL;
			while (tmp->next != NULL) {

				if (strcmp(tmp->next->word, novi->word) > 0) {
					eq = tmp;
					tmp = tmp->next;
				}
				else if (strcmp(tmp->next->word, novi->word) < 0) {
					novi->next = tmp->next;
					tmp->next = novi;
					break;
				}
				else if (strcmp(tmp->next->word, novi->word) == 0) {
					tmp->next->count++;
					novi = tmp->next;
					break;
				}
				else {
					tmp = tmp->next;
				}
			}
			tmp->next = novi;
		}
	}
	if (dict->next == NULL) {
		dict->next = novi;
	}
}


int filter(Word *w) {
	char* tmp;
	int cnt;

	tmp = strdup(w->word);
	cnt = strlen(tmp);

	if ((((w->count) > 5) && (w->count < 11)) && cnt > 3)
		return 1;

	return 0;
}

Dictionary filterDictionary(Dictionary indict, int(*filter)(Word *w)) {
	Dictionary tmp, novi;

	novi = (Word*)malloc(sizeof(Word));
	novi->word = "Izmjenjeni rjecnik";
	novi->next = NULL;

	tmp = indict;
	while (tmp->next != NULL) {
		if (filter(tmp->next))
			tmp = tmp->next;
		else {
			novi = tmp->next;
			tmp->next = novi->next;
			free(novi);
		}
	}
}

void print(Dictionary dict) {
	Word* tmp;

	tmp = dict->next;

	while (tmp != NULL) {
		printf("%s\t %d\n", tmp->word, tmp->count);
		tmp = tmp->next;
	}
}

void destroy(Dictionary dict) {
	Word* tmp;
	char* str_head;
	str_head = strdup(dict->word);
	dict->word = str_head;


	while (dict != NULL) {
		tmp = dict;
		dict = dict->next;
		free(tmp->word);
		free(tmp);
	}
}