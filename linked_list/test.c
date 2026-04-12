#include <stdio.h>
#include "list.h"

#define TESTSIZE 16

int main ()
{
	size_t i;
	int arr[TESTSIZE];
	for (i = 0; i < TESTSIZE; i++)
		*(arr + i) = i;

	List *list = initList();

	for (i = 0; i < TESTSIZE; i++)
		inserthead(list, arr + i);
	for (i = 0; i < TESTSIZE; i++)
		printf("%d%c", *(int*)removehead(list), (i%10==9 || i==TESTSIZE-1) ? '\n' : ' ');

	for (i = 0; i < TESTSIZE; i++)
		inserttail(list, arr + i);
	for (i = 0; i < TESTSIZE; i++)
		printf("%d%c", *(int*)removetail(list), (i%10==9 || i==TESTSIZE-1) ? '\n' : ' ');

	freeList(list);
	return 0;
}

