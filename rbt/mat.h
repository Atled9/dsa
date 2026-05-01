#ifndef MATRIX
#define MATRIX

#include <stddef.h>

typedef struct Mat Mat;

Mat *initMat(size_t nrow, size_t ncol, size_t field, char fill);
void freeMat(Mat *mat);

void display(Mat *mat);

void assign(Mat *mat, int row, int col, char *str);

#endif
