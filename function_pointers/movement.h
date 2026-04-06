#ifndef MOVEMENT
#define MOVEMENT

void go(int *x, int *y, void (*direction)(int *, int *));

void north(int *x, int *y);
void south(int *x, int *y);
void east(int *x, int *y);
void west(int *x, int *y);

#endif
