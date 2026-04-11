#include <stdio.h>
#include "list.h"

#define TESTSIZE 16

int main ()
{
	List *list = initList();
	int i;

	for (i = 0; i < TESTSIZE; i++)
		inserthead(list, i);
	for (i = 0; i < TESTSIZE; i++)
		printf("%d%c", removehead(list), (i%10==9 || i==TESTSIZE-1) ? '\n' : ' ');

	for (i = 0; i < TESTSIZE; i++)
		inserttail(list, i);
	for (i = 0; i < TESTSIZE; i++)
		printf("%d%c", removetail(list), (i%10==9 || i==TESTSIZE-1) ? '\n' : ' ');
	
	printf("%d\n", removehead(list));
	printf("%d\n", removetail(list));

	freeList(list);
	return 0;
}

