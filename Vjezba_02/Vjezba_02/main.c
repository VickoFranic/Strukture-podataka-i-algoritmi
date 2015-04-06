#include <stdio.h>
#include <malloc.h>
#include "functions.h"


int main() {
	unsigned int num;
	FILE *fp;
//	fp = fopen("primjerbin.stl", "rb");
	fp = fopen("test.stl", "rb");

	Objekt3D* o = STL_read(fp); // vraæa pointer na strukturu Objekt3D
	Objekt3D_read(o);

	Objekt3D_write_txt(o);

	Objekt3D_write_bin(o); // zapisi u datoteku

	return 0;
}