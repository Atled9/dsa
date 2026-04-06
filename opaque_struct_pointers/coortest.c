#include <stdio.h>
#include "coor.h"

int main()
{
	Coor *c0 = assign(3, 4);
	Coor *c1 = assign(5, 12);

	printf("%lf\n", getnorm(c0));
	printf("%lf\n", getnorm(c1));

	freecoor(c0);
	freecoor(c1);
	return 0;
}
