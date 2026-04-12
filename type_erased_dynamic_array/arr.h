#ifndef ARR
#define ARR

typedef struct Arr Arr;

Arr *initArr(size_t initcap);
void freeArr(Arr *arr);

void *getdata(Arr *arr, size_t ind);
size_t getsize(Arr *arr);
size_t getcapacity(Arr *arr);

void setdata(Arr *arr, size_t ind, void *data);
void nsrt(Arr *arr, size_t ind, void *data);
void rmve(Arr *arr, size_t ind);

#endif
