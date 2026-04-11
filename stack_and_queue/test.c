#include <stdio.h>
#include "collection.h"

#define TESTSIZE 16

int main()
{
	Collection *stack = initStack();
	Collection *queue = initQueue();
	int i;

	for (i = 0; i < TESTSIZE; i++)
		push(stack, i);
	for (i = 0; i < TESTSIZE; i++)
		printf("%2d%c", pop(stack), (i%10==9 || i==TESTSIZE-1) ? '\n' : ' ');
	
	for (i = 0; i < TESTSIZE; i++)
		enqueue(queue, i);
	for (i = 0; i < TESTSIZE; i++)
		printf("%2d%c", dequeue(queue), (i%10==9 || i==TESTSIZE-1) ? '\n' : ' ');
	
	printf("%d\n", removal(stack));
	printf("%d\n", removal(queue));

	freeCollection(stack);
	freeCollection(queue);
	return 0;
}
