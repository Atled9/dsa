#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int *a;
	size_t size;
	size_t capacity;
} Arr;

Arr *initArr(size_t initcap)
{
	Arr *buff = (Arr *)malloc(sizeof(Arr));

	if (initcap)
		buff->a = (int *)malloc(initcap * sizeof(int));
	else	/* MUST start with capacity >= 1 */
		buff->a = (int *)malloc(++initcap * sizeof(int));

	buff->size = 0;
	buff->capacity = initcap;

	return buff;
}

size_t randfill(Arr *buff)
{
	srand(time(NULL));

	int *pos = buff->a;
	while (pos < buff->a + buff->capacity)
		*pos++ = rand() % buff->capacity;
	
	return (buff->size = buff->capacity);
}

void nsrt(Arr *buff, size_t ind, int val)
{
	if (ind > buff->size)
		printf("index out of bounds: value will be placed at end of array\n");

	if (buff->size == buff->capacity)
		buff->a = (int *)realloc(buff->a, (buff->capacity *= 2) * sizeof(int));

	int *pos = buff->a + (buff->size)++;
	for (; pos > buff->a + ind; pos--)
		*pos = *(pos - 1);

	*pos = val;
}

void rmve(Arr *buff, size_t ind)
{
	if (ind >= buff->size)
		printf("index out of bounds: value at end of array will be removed\n");

	int *pos = buff->a + ind;
	for (; pos < buff->a + buff->size; pos++)
		*pos = *(pos + 1);

	if (buff->size)
		(buff->size)--;
}

void setval(Arr *buff, size_t ind, int val)
{
	if (buff->a + ind < buff->a + buff->size)
		*(buff->a + ind) = val;
}
int getval(Arr *buff, size_t ind)
{
	if (buff->a + ind < buff->a + buff->size)
		return *(buff->a + ind);
	else {
		printf("index out of bounds: returning 0\n");
		return 0;
	}
}

void printArr(Arr *buff)
{
	int *pos = buff->a;
	while(pos - buff->a < buff->size)
		printf("%3d%c", *pos++, ((pos-buff->a)%10==9 || (pos-buff->a)==buff->size-1) ? '\n' : ' ');

	printf("size: %zu, capacity: %zu\n", buff->size, buff->capacity);
}


void freeArr(Arr *buff)
{
	free(buff->a);
	free(buff);
}
