#ifndef TREE
#define TREE

typedef struct Node Node;
typedef struct Tree Tree;

Tree *initTree(void);
void freeTree(Tree *tree);

void *getdata(Tree *tree, int key);

size_t traverse(Tree *tree, void (*order)(Node *, int **), int *keyarr);
extern void (*inorder)(Node *, int **);
extern void (*preorder)(Node *, int **);
extern void (*postorder)(Node *, int **);

void setdata(Tree *tree, int key, void *data);

void nsrt(Tree *tree, int key, void *data);
void rmve(Tree *tree, int key);

#endif
