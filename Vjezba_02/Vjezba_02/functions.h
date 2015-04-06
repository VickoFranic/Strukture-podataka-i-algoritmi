#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <malloc.h>

typedef struct {
	float niz[3];
} Vrh;

typedef struct {
	float normala[3];
	Vrh vrhovi[3];
	unsigned short nula;
} Trokut;

typedef struct {
	unsigned int n;
	Trokut* niz;
}Objekt3D;


// Citanje STL binarne datoteke i spremanje u strukturu Objekt3D
Objekt3D* STL_read(FILE* fp);

// Èitanje ispunjenje strukture Objekt3D
void Objekt3D_read(Objekt3D* obj);

// Zapis strukture Objekt3D u binarnu STL datoteku
void Objekt3D_write_bin(Objekt3D* obj);

// Funkcija koja Objekt3D strukturu zapisuje u tekstualnu STL datoteku
void Objekt3D_write_txt(Objekt3D* obj);

#endif