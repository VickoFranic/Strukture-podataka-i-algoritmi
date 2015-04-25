#include <stdio.h>
#include <malloc.h>

static int N = 7;

int podijeli(int niz[]) {
	int i = 0, j = 0;
	int cnt1 = 0, cnt2 = 0;

	for (i; i < N; i++) {
		cnt1 = cnt1 + niz[i]; // uzmi element iz niza svaki krug petlje i pribroji ih

		cnt2 = 0;
		j = i + 1;
		for (j; j < N; j++) { // kreni od sljedeceg elementa u nizu
			cnt2 = cnt2 + niz[j];
		}

		if (cnt1 == cnt2) {
			return i;
		}
	}
	return -1;
}

int zbrojiPrije(int niz[], int index) {
	int i = 0, cnt = 0;

	for (i; i < index; i++)
		cnt = cnt + niz[i];

	return cnt;
}

int zbrojiIza(int niz[], int index) {
	int cnt = 0;
	index++;

	for (index; index < N; index++)
		cnt = cnt + niz[index];

	return cnt;
}

void noviNiz(int niz[], int a, int b) {
	int l = b - a;
	int *pn;
	int i = 0;

	pn = (int*)malloc(l * sizeof(int));

	printf("Novi niz: ");
	for (i; i <= l ; i++) {
		pn[i] = niz[a];
		printf("%d ", pn[i]);
		a++;
	}
	printf("\n");
}

int main() {
	int niz[] = { 6, 2, 1, 1, 2, 6, 6 };

	printf("Index zbroja: %d\n", podijeli(niz));
	printf("Zbroj prije indexa: %d\n", zbrojiPrije(niz, 2));
	printf("Zbroj iza indexa: %d\n", zbrojiIza(niz, 4));

	noviNiz(niz, 2, 4);
}