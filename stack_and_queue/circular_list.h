#ifndef LIST
#define LIST

typedef struct List List;

List *initList(void);

void inserthead(List *list, void *data);
void inserttail(List *list, void *data);

void *removehead(List *list);
void *removetail(List *list);

void freeList(List *list);

#endif
