#ifndef TREE_H
#define TREE_H
#include <string.h>

// Èvor stabla sa pokazivaèom na rijeè i na djecu èvora
typedef struct Node {
	char *word;
	struct Node *left, *right;
} Node;

// Stablo odnosno pokazivaè na korijen stabla
typedef Node* BSTree;

BSTree NewBSTree();

void AddNode(BSTree *bst, char *word);

int BSTHeight(BSTree bst);

void PrintBSTree(BSTree bst);

void SaveBSTree(BSTree bst, FILE *fd);

void DeleteBSTree(BSTree bst);

BSTree LoadBSTree(FILE *fd);

#endif