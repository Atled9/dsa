#include <stdio.h>
#include <stdlib.h>

int main()
{
	int num0 = 16;
	double num1 = 1.25;
	char letter = 'a';

	void *ptr = &num0;
	printf("Value at ptr: %d\n", *(int *)ptr);
	ptr = &num1;
	printf("Value at ptr: %lf\n", *(double *)ptr);

	void **pos;
	void *arr[3];

	pos = arr;
	*pos = &num0;
	*(pos + 1) = &num1;
	*(pos + 2) = &letter;

	printf("values in array: %d %lf %c\n", (*(int *)*pos)++, (*(double *)*(pos + 1))++, (*(char *)*(pos + 2))++);

	pos = (void **)malloc(3 * sizeof(void *));
	*pos = *arr;
	*(pos + 1) = *(arr + 1);
	*(pos + 2) = *(arr + 2);
	
	printf("values in array: %d %lf %c\n", *(int *)*pos, *(double *)*(pos + 1), *(char *)*(pos + 2));

	free(pos);
	return 0;
}
