#include <math.h>
#include <stdlib.h>

typedef struct {
	int x;
	int y;
} Coor;

Coor *assign(int x_val, int y_val)
{
	/* memory must be heap allocated, otherwise the
	 * memory for the struct will be freed at the end 
	 * of this function */
	Coor *c = (Coor *)malloc(sizeof(Coor));

	c->x = x_val;
	c->y = y_val;

	return c;
}

double getnorm(Coor *c)
{
	return sqrt(c->x * c->x + c->y * c->y);
}

void freecoor(Coor *c)
{
	free(c);
}

