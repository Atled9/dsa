#include <stdlib.h>

typedef struct Node {
	void *data;
	int key;

	struct Node *l, *r;
} Node;

typedef struct {
	Node *root;
} Tree;

static void freenodes(Node *node);

static void in_order(Node *node, int **pos);
static void pre_order(Node *node, int **pos);
static void post_order(Node *node, int **pos);

static Node *removenode(Node *node);

Tree *initTree(void)
{
	Tree *tree = (Tree *)malloc(sizeof(Tree));
	tree->root = NULL;

	return tree;
}

void freeTree(Tree *tree)
{
	freenodes(tree->root);
	free(tree);
}

void *getdata(Tree *tree, int key)
{
	if (tree->root == NULL)
		return NULL;
	
	Node *curr = tree->root;

	while (curr != NULL) {

		if (key < curr->key)
			curr = curr->l;
		else if (key > curr->key)
			curr = curr->r;
		else
			return curr->data;
	}
	return NULL;
}

size_t traverse(Tree *tree, void (*order)(Node *, int **), int *keyarr)
{
	int *pos = keyarr;
	order(tree->root, &pos);
	return pos - keyarr;
}

void setdata(Tree *tree, int key, void *data)
{
	if (tree->root == NULL)
		return;
	
	Node *curr = tree->root;

	while (curr != NULL) {

		if (key < curr->key)
			curr = curr->l;
		else if (key > curr->key)
			curr = curr->r;
		else {
			curr->data = data;
			return;
		}
	}
}

void nsrt(Tree *tree, int key, void *data)
{
	Node *newnode = (Node *)malloc(sizeof(Node));
	newnode->key = key;
	newnode->data = data;
	newnode->l = newnode->r = NULL;

	if (tree->root == NULL) {
		tree->root = newnode;
		return;
	}
	Node *curr = tree->root;
	Node *next = tree->root;

	while (next != NULL) {
		curr = next;

		if (key < curr->key)
			next = curr->l;
		else
			next = curr->r;
	}
	if (key < curr->key)
		curr->l = newnode;
	else
		curr->r = newnode;
}
void rmve (Tree *tree, int key)
{
	if (tree->root != NULL && tree->root->key == key) {
		tree->root = removenode(tree->root);
		return;
	}
	Node *curr = tree->root;
	Node *next = tree->root;

	while (next != NULL && next->key != key) {
		curr = next;

		if (key < curr->key)
			next = curr->l;
		else
			next = curr->r;
	}
	if (next == NULL)
		return;	
	
	if (key < curr->key)
		curr->l = removenode(curr->l);
	else
		curr->r = removenode(curr->r);
}

static void freenodes(Node *node)
{
	if (node == NULL)
		return;
	
	freenodes(node->l);
	freenodes(node->r);

	free(node);
}

static void in_order(Node *node, int **pos)
{
	if (node == NULL)
		return;
	in_order(node->l, pos);
	*(*pos)++ = node->key;
	in_order(node->r, pos);
}
void (*inorder)(Node *, int **) = in_order;

static void pre_order(Node *node, int **pos)
{
	if (node == NULL)
		return;
	*(*pos)++ = node->key;
	pre_order(node->l, pos);
	pre_order(node->r, pos);
}
void (*preorder)(Node *, int **) = pre_order;

static void post_order(Node *node, int **pos)
{
	if (node == NULL)
		return;
	post_order(node->l, pos);
	post_order(node->r, pos);
	*(*pos)++ = node->key;
}
void (*postorder)(Node *, int **) = post_order;

static Node *removenode(Node *node)
{
	if (node->l == NULL && node->r == NULL) {
		free(node);
		return NULL;
	}	
	Node *temp;

	if (node->l != NULL && node->r == NULL) {
		temp = node->l;
		free(node);
		return temp;
	}
	if (node->l == NULL && node->r != NULL) {
		temp = node->r;
		free(node);
		return temp;
	}

	if (node->l->r == NULL) {
		temp = node->l;
		temp->r = node->r;
		free(node);
		return temp;
	}
	Node *succ = node->l;

	while (succ->r->r != NULL) {
		succ = succ->r;
	}

	temp = succ->r;
	succ->r = succ->r->l;

	temp->l = node->l;
	temp->r = node->r;

	free(node);
	return temp;
}
