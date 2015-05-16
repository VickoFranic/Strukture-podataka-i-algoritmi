#include "prior_queue.h"
#include <memory.h>

#define N 10000

prior_queue* newPQ() {
	prior_queue* pq = (prior_queue*)malloc(sizeof(prior_queue));
	pq->capacity = N;
	pq->size = 0;
	pq->elements = (element*)malloc(sizeof(element)*N);	// alociramo memoriju za 10000 elemenata

	return pq;
}


void insert(prior_queue *pq, element* novi) {
	int i;
	element* tmp = (element*)malloc(sizeof(element));
	tmp = novi;

	if (pq->size == N)
		return;

	i = (++pq->size);
	pq->elements[i] = *tmp;	// dodali smo novi element na kraj niza

	fix_up(pq, i);
}

void fix_up(prior_queue* pq, int c) {
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

		fix_up(pq, p);
	}
}

void removeMax(prior_queue* pq) {
	element tmp;

	tmp = pq->elements[1];
	pq->elements[1] = pq->elements[pq->size];
	pq->size--;

	fix_down(pq, 1);
}

void fix_down(prior_queue* pq, int p) {
	int l, r;
	element tmp;

	l = 2 * p;
	r = 2 * p + 1;

	if (p >= pq->size)
		return;
	else if (pq->elements[l].priority > pq->elements[r].priority) {
		if (pq->elements[l].priority > pq->elements[p].priority) {
			tmp = pq->elements[p];
			pq->elements[p] = pq->elements[l];
			pq->elements[l] = tmp;
			fix_down(pq, l);
		}
	}

	else if (pq->elements[l].priority < pq->elements[r].priority) {
		if (pq->elements[r].priority > pq->elements[p].priority) {
			tmp = pq->elements[p];
			pq->elements[p] = pq->elements[r];
			pq->elements[r] = tmp;
			fix_down(pq, r);
		}
	}
	else
		return;
}

void printPQ(prior_queue* pq) {
	int i = 1;

	while (i <= pq->size) {
		printf("Prioritet %d\n", pq->elements[i].priority);
		i++;
	}
}