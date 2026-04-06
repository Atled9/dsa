void go(int *x, int *y, void (*direction)(int *, int *))
{
	direction(x, y);
}

void north(int *x, int *y)
{
	(*y)++;
}
void south(int *x, int *y)
{
	(*y)--;
}
void east(int *x, int *y)
{
	(*x)++;
}
void west(int *x, int *y)
{
	(*x)--;
}
