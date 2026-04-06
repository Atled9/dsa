#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arr.h"

#define VALRANGE 10

size_t size = 0;

int main()
{
	srand(time(NULL));

	printf("initialization with non-zero argument:\n");
	Arr* buffer = initArr(16);
	printArr(buffer);
	freeArr(buffer);
	printf("\n");

	printf("initialization with zero argument:\n");
	buffer = initArr(size = 0);
	printArr(buffer);
	printf("\n");

	printf("insertion at beginning of empty array:\n");
	nsrt(buffer, size++, rand() % VALRANGE);
	printArr(buffer);
	printf("\n");

	printf("insertion at beginning of non-empty array:\n");
	nsrt(buffer, size++ - 1, rand() % VALRANGE);
	printArr(buffer);
	printf("\n");

	printf("insertion at middle of array:\n");
	nsrt(buffer, size++ / 2, rand() % VALRANGE);
	printArr(buffer);
	printf("\n");

	printf("insertion at end of array:\n");
	nsrt(buffer, size++, rand() % VALRANGE);
	printArr(buffer);
	printf("\n");

	printf("insertion out of bounds:\n");
	nsrt(buffer, size++ + 1, rand() % VALRANGE);
	printArr(buffer);
	printf("\n");

	/* out of bounds removal does not copy the junk value above the former
	 * last index into the former last index, however, the size is still
	 * decremented */
	printf("removal out of bounds:\n");
	rmve(buffer, size--);
	printArr(buffer);
	printf("\n");

	printf("removal at end of array:\n");
	rmve(buffer, --size);
	printArr(buffer);
	printf("\n");

	printf("removal at middle of array:\n");
	rmve(buffer, --size / 2);
	printArr(buffer);
	printf("\n");

	printf("removal at beginning of array:\n");
	rmve(buffer, --size - 1);
	printArr(buffer);
	printf("\n");

	printf("removal at beginning of single-element array:\n");
	rmve(buffer, --size);
	printArr(buffer);
	printf("\n");

	printf("removal at beginning of empty array:\n");
	rmve(buffer, size);
	printArr(buffer);
	printf("\n");

	printf("randfill() function:\n");
	size = randfill(buffer);
	printArr(buffer);
	printf("\n");

	printf("new size: %d\n", size);
	unsigned int pos;
	setval(buffer, pos = rand() % size, -1 * (rand() % VALRANGE + 1));
	printArr(buffer);
	printf("%d assigned to index %d\n", getval(buffer, pos), pos);
	printf("\n");

	freeArr(buffer);

	return 0;
}
