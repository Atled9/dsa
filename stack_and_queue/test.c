#include <stdio.h>
#include "collection.h"

#define TESTSIZE 16

int main()
{
	size_t i;
	int arr[TESTSIZE];
	for (i = 0; i < TESTSIZE; i++)
		*(arr + i) = i;

	Collection *stack = initStack();
	Collection *queue = initQueue();

	for (i = 0; i < TESTSIZE; i++)
		push(stack, arr + i);
	for (i = 0; i < TESTSIZE; i++)
		printf("%2d%c", *(int*)pop(stack), (i%10==9 || i==TESTSIZE-1) ? '\n' : ' ');
	
	for (i = 0; i < TESTSIZE; i++)
		enqueue(queue, arr + i);
	for (i = 0; i < TESTSIZE; i++)
		printf("%2d%c", *(int*)dequeue(queue), (i%10==9 || i==TESTSIZE-1) ? '\n' : ' ');

	freeCollection(stack);
	freeCollection(queue);
	return 0;
}
