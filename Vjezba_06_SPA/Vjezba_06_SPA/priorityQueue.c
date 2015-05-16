#include "prior_queue.h"
#include <memory.h>

#define N 10000

prior_queue* newPQ() {
	prior_queue* pq = malloc(sizeof(prior_queue));
	pq->capacity = N;
	pq->size = 0;
	pq->elements = (element*)malloc(sizeof(element)*N);	// alociramo memoriju za 10000 elemenata

	return pq;
}

element newEl(int p) {
	element novi;
	novi.priority = p;
	return novi;
}

void insert(prior_queue *pq, element* novi) {
	int i;
	element* tmp = (element*)malloc(sizeof(element));
	tmp = novi;

	if (pq->size == N)
		return;
	
	i = (++pq->size);
	pq->elements[i] = *tmp;	// dodali smo novi element na kraj niza

	max_heapify(pq, i);
}

void max_heapify(prior_queue* pq, int c) {
	element tmp;
	int p = c / 2;

	if (p < 1)
		return;
	else if (pq->elements[c].priority < pq->elements[p].priority)
		return;
	else if (pq->elements[c].priority > pq->elements[p].priority) {	// ako je prioritet djeteta veci od prioriteta roditelja, swap
		tmp = pq->elements[p];
		pq->elements[p] = pq->elements[c];
		pq->elements[c] = tmp;

		max_heapify(pq, p);
	}
}

printPQ(prior_queue* pq) {
	int i = 1;

	while (i <= pq->size) {
		printf("Prioritet %d\n", pq->elements[i].priority);
		i++;
	}
}