#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <windows.h>
#include <time.h>
#include <math.h>

static int c;

// generiranje i ispis niza
int* generate(int n) {
	int i;
	int *niz = (int*)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++)
		niz[i] = rand() % 1000;
	return niz;
}

int print(int *niz, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%d ", niz[i]);
	}
	printf("\n");
}

// selection sort
// Ti(n) = 1 + n * ( 5 + (n/2)*2 ) 
// Ti(n) = 1 + n*(5 + n)
// Ti(n) = 1 + 5n + n^2
void selectionsort(int *niz, int n) {
	int i, j;
	for (i = 0; i < n - 1; i++) {   // 1 + n
		int tmp, maxi = i; // 2
		for (j = i + 1; j < n; j++) { // n/2  
			if (niz[j] < niz[maxi]) // 1
				maxi = j; // 1
		}
		// 3
		tmp = niz[maxi];
		niz[maxi] = niz[i];
		niz[i] = tmp;
	}
}

// insertion sort
void insertionsort(int *niz, int n) {
	int i, j;
	for (i = 1; i < n; i++) {
		j = i;
		while (j > 0 && niz[j - 1] > niz[j]) {
			int tmp;
			tmp = niz[j - 1];
			niz[j - 1] = niz[j];
			niz[j] = tmp;
			j--;
		}
	}
}

// quick sort partition bez odabira pivota
int partition(int *niz, int n) {
	int l, r;
	l = 1;
	r = n - 1;
	while (l < r) {
		if (niz[r] >= niz[0]) {
			r--;
		}
		else if (niz[l] < niz[0]) {
			l++;
		}
		else {
			int tmp = niz[l];
			niz[l] = niz[r];
			niz[r] = tmp;
		}
	}
	if (niz[0] < niz[r]) {
		return 0;
	}
	else {
		int tmp = niz[r];
		niz[r] = niz[0];
		niz[0] = tmp;
		return r;
	}
}

// quick sort bez odabira pivota
void quicksort(int *niz, int n) {
	int pi;
	if (n < 2)
		return;
	pi = partition(niz, n); // 4 + 3*n
	quicksort(niz, pi);
	quicksort(niz + pi + 1, n - pi - 1);
}




// quick sort partition s odabirom pivota kao srednje vrijednosti izmedju prvog, srednjeg i zadnjeg elementa
int partition_new(int *niz, int n) {
	int l, r;
	int tmp;

	if (((niz[n / 2] > niz[0]) && (niz[n / 2] < niz[n - 1])) || ((niz[n - 1] < niz[n / 2]) && (niz[0] > niz[n / 2]))) {
		tmp = niz[0];
		niz[0] = niz[n / 2];
		niz[n / 2] = tmp;
	}
	else if (((niz[n - 1] > niz[0]) && (niz[n - 1] < niz[n / 2])) || ((niz[n / 2] < niz[n - 1]) && (niz[0] > niz[n - 1]))) {
		tmp = niz[0];
		niz[0] = niz[n - 1];
		niz[n - 1] = tmp;
	}

	l = 1;
	r = n - 1;
	while (l < r) {
		if (niz[r] >= niz[0]) {
			r--;
		}
		else if (niz[l] < niz[0]) {
			l++;
		}
		else {
			int tmp = niz[l];
			niz[l] = niz[r];
			niz[r] = tmp;
		}
	}
	if (niz[0] < niz[r]) {
		return 0;
	}
	else {
		int tmp = niz[r];
		niz[r] = niz[0];
		niz[0] = tmp;
		return r;
	}
}


// quick sort s odabirom sortiranja
void quicksort_test(int *niz, int n) {
	int pi;
	if (n < c) {
		selectionsort(niz, n);
	}
	else {
		pi = partition(niz, n); // 4 + 3*n
		quicksort_test(niz, pi);
		quicksort_test(niz + pi + 1, n - pi - 1);
	}
}


// quick sort new
void quicksort_new(int *niz, int n) {
	int pi;
	if (n < 2)
		return;
	pi = partition_new(niz, n);
	quicksort_new(niz, pi);
	quicksort_new(niz + pi + 1, n - pi - 1);
}

// merge sort
void merge(int *niz, int *niza, int na, int *nizb, int nb) {
	int a, b;
	a = 0;
	b = 0;
	while (a < na || b < nb) {
		if (a == na) {
			niz[a + b] = nizb[b];
			b++;
		}
		else if (b == nb) {
			niz[a + b] = niza[a];
			a++;
		}
		else if (niza[a] < nizb[b]) {
			niz[a + b] = niza[a];
			a++;
		}
		else {
			niz[a + b] = nizb[b];
			b++;
		}
	}
}

// alocira i vraca kopiju niza
int* duplicate(int *niz, int n) {
	int i;
	int *novi = (int*)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++) {
		novi[i] = niz[i];
	}
	return novi;
}

void mergesort(int *niz, int n) {
	// implementirati
}

// mjerenje vremena izvocenja funkcije sortiranja
double measure(void(*sort)(int *niz, int n), int *niz, int n) {
	LARGE_INTEGER frequency;
	LARGE_INTEGER start;
	LARGE_INTEGER end;
	double interval;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

	sort(niz, n);

	QueryPerformanceCounter(&end);
	interval = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	return interval;
}



void main() {
	int *niz;
	double n;
	float k;
	int *niz1, *niz2;
	double seltime, instime, quicktime, quicktime_new, quick_sorted, quick_sorted_pivot, mergetime;

	srand((unsigned int)time(0));

	/*
	// Ti(n) = 1 + 5*n + n^2
	// Tq(n) = (2*n-1) + 4 * (2^(k+1)-1) +  3 * n * k + n { sa k = log(n) }
	for(n=2; n < 64; n=n*2) {
		k = (log10(n)/log(2.0));

		printf("n: %.f\t",n);
		printf("Insertion: %f\t", (1 + 5*n + pow(n,2))); // Slozenost Insertionsort-a
		printf("Quicksort: %f\n", ((2*n-1) + 4 * (pow(2,(k + 1))-1) +  3 * n * k + n)); // Slozenost Quicksort-a
	}
	
	
	for (c = 2; c < 10000; c = c * 2) {
		niz1 = generate(30000);
		niz2 = generate(30000);
		printf("c: %d\t", c);
		printf("Quicksort: %f\t", measure(quicksort, niz1, 30000));
		printf("Quicksort_test: %f\n", measure(quicksort_test, niz2, 30000));
	}
	*/

	seltime = instime = quicktime = quicktime_new = quick_sorted = quick_sorted_pivot = mergetime = 0;
	for (n = 1000; n < 20000; n += 1000) {
		/* 
		niz = generate(n);
		seltime = measure(selectionsort,niz, n);
		free(niz);

		niz = generate(n);
		instime = measure(insertionsort, niz, n);
		free(niz);

		niz = generate(n);
		mergetime = measure(mergesort, niz, n);
		free(niz);
		*/

		/*
		niz = generate(n);
		insertionsort(niz, n);
		
		niz1 = duplicate(niz, n);
		niz2 = duplicate(niz, n);
		

		quick_sorted = measure(quicksort, niz1, n);
		quick_sorted_pivot = measure(quicksort_new, niz2, n);
		free(niz);

		free(niz1);
		free(niz2);
		*/
		
		niz = generate(n);
		quicktime = measure(quicksort, niz, n);
		free(niz);

		niz = generate(n);
		quicktime_new = measure(quicksort_new, niz, n);
		free(niz);
		

		printf("%lf %lf %f %f\n", quicktime, quicktime_new, quick_sorted, quick_sorted_pivot);
		
	}
}