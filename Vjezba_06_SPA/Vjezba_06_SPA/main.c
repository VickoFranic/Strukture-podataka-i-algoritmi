#include "prior_queue.h"

void main() {

	prior_queue* pq = newPQ();

	element el1 = { "", 6 };
	element el2 = { "", 4 };
	element el3 = { "", 15 };
	element el4 = { "", 20 };
	element el5 = { "", 12 };
	element el6 = { "", 9 };

	insert(pq, &el1);
	insert(pq, &el2);
	insert(pq, &el3);
	insert(pq, &el4);
	insert(pq, &el5);
	insert(pq, &el6);

	printPQ(pq);

	removeMax(pq);
	printf("\n");

	printPQ(pq);
}