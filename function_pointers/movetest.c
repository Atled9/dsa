#include <stdio.h>
#include "movement.h"

int x_pos = 0;
int y_pos = 0;

int main()
{
	void (*n)(int *, int *) = north;
	void (*s)(int *, int *) = south;
	void (*e)(int *, int *) = east;
	void (*w)(int *, int *) = west;

	n(&x_pos, &y_pos);
	go(&x_pos, &y_pos, east);

	printf("x_position: %d, y_position: %d\n", x_pos, y_pos);

	
}
