#include <stdio.h>
#include "arr.h"

void printArr(Arr *arr);

int main()
{
	Arr *arr = initArr(1);

	printf("insertion at beginning of array:\n");
	char *a = "the quick brown fox\n";
	nsrt(arr, 0, a);
	printArr(arr);
	printf("\n");

	printf("insertion at end of array:\n");
	char *c = "lazy dog\n";
	nsrt(arr, getsize(arr), c);
	printArr(arr);
	printf("\n");

	printf("insertion at middle of array:\n");
	char *b = "jumps over the\n";
	nsrt(arr, getsize(arr) / 2, b);
	printArr(arr);
	printf("\n");
	
	printf("replacement of data:\n");
	char *d = "sphinx of\n";
	char *e = "black quartz,\n";
	char *f = "judge my vow\n";
	setdata(arr, 0, d);
	setdata(arr, (getsize(arr)-1) / 2, e);
	setdata(arr, (getsize(arr)-1), f);
	printArr(arr);
	printf("\n");
	
	printf("removal at middle of array:\n");
	rmve(arr, (getsize(arr)-1) / 2);
	printArr(arr);
	printf("\n");

	printf("removal at end of array:\n");
	rmve(arr, (getsize(arr)-1));
	printArr(arr);
	printf("\n");

	printf("removal at beginning of array:\n");
	rmve(arr, 0);
	printArr(arr);
	printf("\n");

	freeArr(arr);
	return 0;
}

void printArr(Arr *arr)
{
	size_t i = 0;
	size_t size = getsize(arr);

	for (; i < size; i++)
		printf("%s", (char *)getdata(arr, i));
	
	printf("size: %zu, capacity: %zu\n", getsize(arr), getcapacity(arr));
}
