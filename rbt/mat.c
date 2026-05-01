#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char **orig;
	size_t nrow;
	size_t ncol;
	size_t field;
} Mat;

Mat *initMat(size_t nrow, size_t ncol, size_t field, char fill)
{
	Mat *mat = (Mat *)malloc(sizeof(Mat));
	mat->nrow = nrow;
	mat->ncol = ncol;
	mat->field = field;
	mat->orig = (char **)malloc(nrow * sizeof(char *));

	for (int i = 0; i < nrow; i++) {
		*(mat->orig + i) = (char *)malloc(ncol * sizeof(char) + 1);

		for (int j = 0; j < ncol * field; j++) {
			*(*(mat->orig + i) + j) = fill;
		}
		*(*(mat->orig + i) + ncol * field) = '\0';
	}
	return mat;
}

void freeMat(Mat *mat)
{
	for (int i = 0; i < mat->nrow; i++) {
		free(*(mat->orig + i));
	}
	free(mat->orig);
	free(mat);
}

void display(Mat *mat)
{
	for (int i = 0; i < mat->nrow; i++) {
		printf("%s\n", *(mat->orig + i));
	}
}

void assign(Mat *mat, int row, int col, char *str)
{
	if (strlen(str) > mat->field) {
		printf("\"%s\" is larger than the field size\n", str);
		return;
	}
	if (strlen(str) == 1) {
		*(*(mat->orig + row) + col * mat->field + (mat->field - 1) / 2) = *str;
		return;
	}
	strncpy(*(mat->orig + row) + col * mat->field, str, strlen(str));
}
