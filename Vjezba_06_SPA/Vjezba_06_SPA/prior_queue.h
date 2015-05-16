#ifndef PQ_H
#define PQ_H
#include <malloc.h>
#include <stdio.h>

/***** ELEMENT *****/
typedef struct element {
	void* data;
	int priority;
} element;

typedef struct prior_queue {
	int size;
	int capacity;
	element* elements;
} prior_queue;

prior_queue* newPQ();

void insert(prior_queue *pq, element* novi);

void fix_up(prior_queue* pq, int child);

void removeMax(prior_queue* pq);

void fix_down(prior_queue* pq, int parent);

void printPQ(prior_queue* pq);

#endif