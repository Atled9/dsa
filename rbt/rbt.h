#ifndef TREE
#define TREE

typedef struct Tree Tree;

Tree *initTree(void);
void freeTree(Tree *tree);

void inorder_traverse(Tree *tree);
void display_tree(Tree *tree);
int height(Tree *tree);

void backtrace_t(Tree *tree, int key);
void rot_t(Tree *tree, int key, char dir);

void nsrt(Tree *tree, int key, char *str);
void rmve(Tree *tree, int key);

#endif
