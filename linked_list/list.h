#ifndef LIST
#define LIST

typedef struct List List;

List *initList(void);

void inserthead(List *list, int val);
void inserttail(List *list, int val);

int removehead(List *list);
int removetail(List *list);

void freeList(List *list);

#endif
