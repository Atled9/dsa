#ifndef ARR
#define ARR

typedef struct Arr Arr;

Arr *initArr(size_t initcap);
void freeArr(Arr *buff);

void nsrt(Arr *buff, unsigned int ind, int val);
void rmve(Arr *buff, unsigned int ind);

void setval(Arr *buff, unsigned int ind, int val);
int getval(Arr *buff, unsigned int ind);

size_t randfill(Arr *buff);
void printArr(Arr *buff);

#endif
