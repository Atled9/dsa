#ifndef COOR
#define COOR

typedef struct Coor Coor;

Coor *assign(int x_val, int y_val);
double getnorm(Coor *c);

void freecoor(Coor *c);

#endif
