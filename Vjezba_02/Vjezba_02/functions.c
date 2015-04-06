#include <stdio.h>
#include <malloc.h>
#include "functions.h"


// Citanje STL binarne datoteke i spremanje u strukturu Objekt3D // RJESENO
Objekt3D* STL_read(FILE* fp) {
	unsigned int num;
	float tmp[3];
	int i = 0;
	int j = 0;

	fseek(fp, 80, SEEK_SET); // skoci preko 80 bytova
	fread(&num, 4, 1, fp); // citaj broj trokuta

	Objekt3D* obj = (Objekt3D*)malloc(sizeof(Objekt3D));

	obj->n = num;
	obj->niz = (Trokut*)malloc(obj->n*sizeof(Trokut));


	for (i; i < obj->n; i++) {

		// NORMALA
		fread(&tmp, 4, 3, fp);
		for (j; j < 3; j++) {
			obj->niz[i].normala[j] = tmp[j];  // objekt, trokut br. i, i od njega normala - 3 floata
		}
		j = 0;

		// PRVI VRH
		fread(&tmp, 4, 3, fp);
		for (j; j < 3; j++) {
			obj->niz[i].vrhovi[0].niz[j] = tmp[j];
		}
		j = 0;

		// DRUGI VRH
		fread(&tmp, 4, 3, fp);
		for (j; j < 3; j++) {
			obj->niz[i].vrhovi[1].niz[j] = tmp[j];
		}
		j = 0;

		// TREÆI VRH
		fread(&tmp, 4, 3, fp);
		for (j; j < 3; j++) {
			obj->niz[i].vrhovi[2].niz[j] = tmp[j];
		}
		j = 0;

		fseek(fp, 2, SEEK_CUR);
	}
	return obj;
}

// Èitanje ispunjenje strukture Objekt3D // RJESENO
void Objekt3D_read(Objekt3D* obj) {
	int i = 0;
	int j = 0;
	int z = 0;

	for (i; i < obj->n; i++) {
		printf("\nNormala:");
		for (j; j < 3; j++) {
			printf("%f ", obj->niz[i].normala[j]);
		}
		j = 0;

		printf("\n\nVrhovi:\n");
		for (z; z < 3; z++) {
			for (j; j < 3; j++) {
				printf("%f ", obj->niz[i].vrhovi[z].niz[j]);
			}
			printf("\n");
			j = 0;
		}
		z = 0;
	}
}

// Zapis strukture Objekt3D u binarnu STL datoteku // RJESENO
void Objekt3D_write_bin(Objekt3D* obj) {
	int i = 0;
	int j = 0;
	float nula[20];
	unsigned int brojTrokuta = obj->n;
	unsigned short u = 0;

	FILE *fp;
	fp = fopen("test.stl", "wb");

	for (i; i < 20; i++) {
		nula[i] = 0;
	}

	fwrite(&nula, 4, 20, fp);
	fwrite(&brojTrokuta, 4, 1, fp);
	
	for (j; j < brojTrokuta; j++) {
		fwrite(obj->niz[j].normala, 12, 1, fp); // zapisi normalu
		fwrite(obj->niz[j].vrhovi, 36, 1, fp); // zapisi vrhove
		fwrite(&u, 2, 1, fp);
	}
}

// Funkcija koja Objekt3D strukturu zapisuje u tekstualnu STL datoteku // RJESENO
void Objekt3D_write_txt(Objekt3D* obj) {

	int i = 0;

	FILE *fp;
	fp = fopen("STL_tekst.stl", "w");

	fprintf(fp, "solid STL\n");

	printf("%f", obj->niz[5].vrhovi[0].niz[2]);
	
	for (i; i < obj->n; i++) {
		fprintf(fp, "facet normal %f %f %f\n", obj->niz[i].normala[0], obj->niz[i].normala[1], obj->niz[i].normala[2]);

		fprintf(fp, "outer loop\nvertex %f %f %f\n", obj->niz[i].vrhovi->niz[0], obj->niz[i].vrhovi[0].niz[1], obj->niz[i].vrhovi[0].niz[2]);
		fprintf(fp, "vertex %f %f %f\n", obj->niz[i].vrhovi->niz[1], obj->niz[i].vrhovi[1].niz[1], obj->niz[i].vrhovi[1].niz[2]);
		fprintf(fp, "vertex %f %f %f\nendloop\nendfacet\n", obj->niz[i].vrhovi->niz[2], obj->niz[i].vrhovi[2].niz[1], obj->niz[i].vrhovi[2].niz[2]);
	}
	fprintf(fp, "endsolid STL");
}