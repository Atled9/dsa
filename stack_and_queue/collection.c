#include <stdlib.h>
#include "circular_list.h"

typedef struct {
	List *list;
	void (*nsrt)(List *, int);
	int (*rmve)(List *);
} Collection;

Collection *initStack(void)
{
	Collection *stack = (Collection *)malloc(sizeof(Collection));
	stack->list = initList();

	stack->nsrt = inserthead;
	stack->rmve = removehead;

	return stack;
}
Collection *initQueue(void)
{
	Collection *queue = (Collection *)malloc(sizeof(Collection));
	queue->list = initList();

	queue->nsrt = inserttail;
	queue->rmve = removehead;

	return queue;
}

void insertion(Collection *collection, int val)
{
	collection->nsrt(collection->list, val);
}
void (*push)(Collection *, int) = insertion;
void (*enqueue)(Collection *, int) = insertion;

int removal(Collection *collection)
{
	collection->rmve(collection->list);
}
int (*pop)(Collection *) = removal;
int (*dequeue)(Collection *) = removal;

void freeCollection(Collection *collection)
{
	freeList(collection->list);
	free(collection);
}
