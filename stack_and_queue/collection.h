#ifndef COLLECTION
#define COLLECTION

typedef struct Collection Collection;

Collection *initStack(void);
Collection *initQueue(void);

void insertion(Collection *, int val);
extern void (*push)(Collection *, int);
extern void (*enqueue)(Collection *, int);

int removal(Collection *);
extern int (*pop)(Collection *);
extern int (*dequeue)(Collection *);

void freeCollection(Collection *collection);

#endif
