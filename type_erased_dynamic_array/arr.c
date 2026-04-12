#include <stdlib.h>

typedef struct {
	void **a;
	size_t size;
	size_t capacity;
} Arr;

Arr *initArr(size_t initcap)
{
	Arr *arr = (Arr *)malloc(sizeof(Arr));

	if (initcap)
		arr->a = (void **)malloc(initcap * sizeof(void *));
	else
		arr->a = (void **)malloc(++initcap * sizeof(void *));
	
	arr->size = 0;
	arr->capacity = initcap;

	return arr;
}
void freeArr(Arr *arr)
{
	free(arr->a);
	free(arr);
}

void *getdata(Arr *arr, size_t ind)
{
	if (ind < arr->size)
		return *(arr->a + ind);

	return NULL;
}
size_t getsize(Arr *arr)
{
	return arr->size;
}
size_t getcapacity(Arr *arr)
{
	return arr->capacity;
}

void setdata(Arr *arr, size_t ind, void *data)
{
	if (ind < arr->size)
		*(arr->a + ind) = data;
}
void nsrt(Arr *arr, size_t ind, void *data)
{
	if (arr->size == arr->capacity)
		arr->a = (void **)realloc(arr->a, (arr->capacity *= 2) * sizeof(void *));
	
	void **pos = arr->a + (arr->size)++;
	for (; pos > arr->a + ind; pos--)
		*pos = *(pos - 1);
	
	*pos = data;
}
void rmve(Arr *arr, size_t ind)
{
	void **pos = arr->a + ind;
	for (; pos < arr->a + arr->size; pos++)
		*pos = *(pos + 1);
	
	if (arr->size)
		(arr->size)--;
}
