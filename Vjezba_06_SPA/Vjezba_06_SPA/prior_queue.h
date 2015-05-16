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

void max_heapify(prior_queue* pq, int child);

printPQ(prior_queue* pq);

#endif