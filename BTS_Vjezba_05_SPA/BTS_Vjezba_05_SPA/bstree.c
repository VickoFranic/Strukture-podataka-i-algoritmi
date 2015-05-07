#include <stdio.h>
#include <malloc.h>
#include "bstree.h"

BSTree NewBSTree()
{
	// Novo prazno stablo
	return NULL;
}

void AddNode(BSTree *bst, char *word)
{
	// Rekurzivno se traži mjesto za novi èvor u stablu. Ako rijeè postoji u stablu, ne dodaje se.
	// bst parametar je dvostruki pokazivaè.

	if (*bst == NULL) {							// znaci da smo dosli do kraja (leaf), dodaj rijec
		*bst = (Node*)malloc(sizeof(Node));
		(*bst)->word = strdup(word);
		(*bst)->left = (*bst)->right = NULL;
	}
	else if (strcmp(word, (*bst)->word) == 0) {	// ako rijec postoji u stablu, return
		return;
	}
	else if (strcmp(word, (*bst)->word) < 0) {	// ako je nova rijec MANJA od trenutne, rekurzivni poziv na left, esle poziv na right
		AddNode(&(*bst)->left, word);
	}
	else if (strcmp(word, (*bst)->word) > 0) {
		AddNode(&(*bst)->right, word);
	}
}

int BSTHeight(BSTree bst)
{
	// Rekurzivno se prolazi cijelo stablo da bi se pronašla najduža grana (visina stabla).
	if (bst == NULL)
		return 0;
	else {
		int lh = BSTHeight(bst->left);
		int rh = BSTHeight(bst->right);

		if (lh > rh)
			return lh + 1; // dodajemo jedan zbog root node
		else
			return rh + 1;
	}
}

void PrintBSTree(BSTree bst)
{
	// Ispisuje rijeèi u stablu na ekran po abecednom redu.
	// In-order šetnja po stablu (lijevo dijete, èvor, desno dijete)

	if (bst == NULL)
		return;

	PrintBSTree(bst->left);

	printf("%s\n", bst->word);

	PrintBSTree(bst->right);
}

void SaveBSTree(BSTree bst, FILE *fd)
{
	// Snima rijeè po rijeè iz stabla u tekstualnu datoteku. Rijeèi su odvojene razmakom.
	// Pre-order šetnja po stablu
	if (bst == NULL)
		return;

	fprintf(fd, "%s,", bst->word);	// prvo ispisemo rijec u cvoru

	SaveBSTree(bst->left, fd);	// rekurzivni poziv za ispis svih rijeci na lijevu stranu stabla

	SaveBSTree(bst->right, fd);	// ispis na desnu stranu 
}

void DeleteBSTree(BSTree bst)
{
	// Briše stablo (string word i sam èvor) iz memorije.
	// Post-order šetnja po stablu

	if (bst == NULL)
		return;

	DeleteBSTree(bst->left);	// brisemo prvo lijevo, rekurzija

	DeleteBSTree(bst->right);	// brisemo desno

	printf("Brisem %s\n", bst->word);
	free(bst->word);
	free(bst);
}

BSTree LoadBSTree(FILE *fd)
{
	// Uèitava rijeè po rijeè iz tekstualne datoteke i dodaje ih u stablo preko AddNode() funkcije.
	// Rijeè duplicirati sa strdup().
	char* tmp[128];
	BSTree novi = NewBSTree();
	

	while (readWord(fd, tmp)) {
		AddNode(&novi, strdup(tmp));
		printf("Novi: %s\n", tmp);
	}
	return novi;
}
