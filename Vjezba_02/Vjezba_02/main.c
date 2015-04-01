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

// Èitanje ispunjenje strukture Objekt3D
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

// Zapis strukture Objekt3D u binarnu STL datoteku
void Objekt3D_write_bin(Objekt3D* obj) {
	int i = 0;
	int j = 0;
	float nula[20];
	unsigned int brojTrokuta = obj->n;
	unsigned short u = 0;

	FILE *fp;
	fp = fopen("test.stl", "a");

	for (i; i < 20; i++) {
		nula[i] = 0;
	}

	fwrite(&nula, 4, 20, fp);
	fwrite(&brojTrokuta, 4, 1, fp);

	for (j; j < brojTrokuta; j++) {
		fwrite(obj->niz, 50, 1, fp); // zapisi trokut
		fseek(fp, 2, SEEK_CUR);
	}
}

int main() {
	unsigned int num;
	FILE *fp;
	fp = fopen("primjerbin.stl", "rb");
	//	fp = fopen("test.stl", "rb");

	Objekt3D* o = STL_read(fp); // vraæa pointer na strukturu Objekt3D
	Objekt3D_read(o);

	//	Objekt3D_write_bin(o); // zapisi u datoteku

	return 0;
}