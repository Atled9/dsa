#include <stdio.h>
#include <stdlib.h>
#include "mat.h"

typedef struct Node {
	struct Node *l, *r, *p;
	char *str;
	int col;
	int key;
} Node;

typedef struct {
	Node *root;
} Tree;

static void freenodes(Node *node);

static void inorder(Node *node);
static int node_height(Node *node);
static void assign_to_mat(Node *node, Mat *mat, int height, int lo, int hi);

static void lrot(Node *node, Tree *tree);
static void rrot(Node *node, Tree *tree);
static void nsrt_repair(Tree *tree, Node *node);

static void removenode(Node *u, Tree *tree);
static Node *replacement(Node *u);
static void fixdoubleblack(Node *node, Tree *tree);

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

void inorder_traverse(Tree *tree)
{
	inorder(tree->root);
	printf("\n");
}
int height(Tree *tree);

void display_tree(Tree *tree)
{
	if (!tree->root)
		return;

	int h = height(tree);
	int nrow = h + 1;
	int ncol = 1;

	for (int i = 0; i < h; i++) {
		ncol = ncol * 2 + 1;
	}
	Mat *mat = initMat(nrow, ncol, 1, ' ');
	assign_to_mat(tree->root, mat, 0, 0, ncol - 1);
	display(mat);
}
int height(Tree *tree)
{
	return node_height(tree->root);
}

void backtrace_t(Tree *tree, int key)
{
	Node *curr = tree->root;

	while (curr->key != key) {
		if (key < curr->key)
			curr = curr->l;
		else
			curr = curr->r;
	}
	while (curr) {
		printf("%d ", curr->key);
		curr = curr->p;
	}
	printf("\n");
}

void rot_t(Tree *tree, int key, char dir)
{
	Node *curr = tree->root;

	while (curr->key != key) {
		if (key < curr->key)
			curr = curr->l;
		else
			curr = curr->r;
	}
	if (dir == 'l')
		lrot(curr, tree);
	if (dir == 'r')
		rrot(curr, tree);
}

void nsrt(Tree *tree, int key, char *str)
{
	Node *newnode = (Node *)malloc(sizeof(Node));
	newnode->col = 1;
	newnode->key = key;
	newnode->str = str;
	newnode->l = newnode->r = newnode->p = NULL;

	if (!tree->root) {
		tree->root = newnode;
		tree->root->col = 0;
		return;
	}
	Node *curr = tree->root;
	Node *next = tree->root;

	while (next) {
		curr = next;

		if (key < curr->key)
			next = curr->l;
		else
			next = curr->r;
	}
	if (key < curr->key) {
		curr->l = newnode;
		curr->l->p = curr;
	} else {
		curr->r = newnode;
		curr->r->p = curr;
	}
	nsrt_repair(tree, newnode);
	tree->root->col = 0;
}
void rmve(Tree *tree, int key)
{
	if (tree->root && tree->root->key == key) {
		removenode(tree->root, tree);
		return;
	}
	Node *curr = tree->root;
	Node *next = tree->root;

	while (next && next->key != key) {
		curr = next;

		if (key < curr->key)
			next = curr->l;
		else
			next = curr->r;
	}
	if (!next)
		return;
	
	if (key < curr->key) {
		removenode(curr->l, tree);
	} else {
		removenode(curr->r, tree);
	}
}

static void freenodes(Node *node)
{
	if (!node)
		return;
	
	freenodes(node->l);
	freenodes(node->r);

	free(node);
}

static void inorder(Node *node)
{
	if (!node)
		return;
	
	inorder(node->l);
	printf("%d\"%s\" ", node->key, node->str);
	inorder(node->r);
}
static int node_height(Node *node)
{
	if (!node)
		return -1;
	
	int lheight = node_height(node->l);
	int rheight = node_height(node->r);

	return (lheight > rheight ? lheight : rheight) + 1;
}

static void assign_to_mat(Node *node, Mat *mat, int height, int lo, int hi)
{
	if (!node)
		return;
	
	int mid = (lo + hi) / 2;

	assign_to_mat(node->l, mat, height + 1, lo, mid - 1);
	assign(mat, height, mid, node->str);
	assign_to_mat(node->r, mat, height + 1, mid + 1, hi);
}

static void removenode(Node *u, Tree *tree)
{
	Node *v = replacement(u);

	Node *parent = u->p;
	Node *sibling;
	if (!parent)
		sibling = NULL;
	else if (u == parent->l)
		sibling = parent->r;
	else
		sibling = parent->l;

	int uvblack = (!v || !v->col) && !u->col;

	if (!v) {
		if (u == tree->root)
			tree->root = NULL;
		else {
			if (uvblack)
				fixdoubleblack(u, tree);
			else if (sibling)
				sibling->col = 1;

			if (u == parent->l)
				parent->l = NULL;
			else
				parent->r = NULL;
		}
		free(u);
		return;
	}
	if (!u->l || !u->r) {
		if (u == tree->root) {
			u->key = v->key;
			u->str = v->str;
			free(v);
		} else {
			if (u == parent->l)
				parent->l = v;
			else
				parent->r = v;

			free(u);
			v->p = parent;

			if (uvblack)
				fixdoubleblack(v, tree);
			else
				v->col = 0;
		}
		return;
	}
	int keytemp;
	char *strtemp;
	keytemp = u->key;
	strtemp = u->str;

	u->key = v->key;
	u->str = v->str;
	v->key = keytemp;
	v->str = strtemp;

	removenode(v, tree);
}
static Node *replacement(Node *u)
{
	if (!u->l && !u->r)
		return NULL;

	if (u->l && !u->r)
		return u->l;

	if (!u->l && u->r)
		return u->r;
	
	Node *temp = u->r;
	while (temp->l)
		temp = temp->l;
	
	return temp;
}
static void fixdoubleblack(Node *node, Tree *tree)
{
	if (node == tree->root)
		return;
	
	Node *parent = node->p;
	Node *sibling;
	if (!parent)
		sibling = NULL;
	else if (node == parent->l)
		sibling = parent->r;
	else
		sibling = parent->l;
	
	if (!sibling)
		fixdoubleblack(parent, tree);
	else {
		if (sibling->col) {
			parent->col = 1;
			sibling->col = 0;

			if (sibling == parent->l)
				rrot(parent, tree);
			else
				lrot(parent, tree);

			fixdoubleblack(node, tree);
		} else {
			if (sibling->l && sibling->l->col || sibling->r && sibling->r->col) {
				if (sibling->l && sibling->l->col) {
					if (sibling == parent->l) {
						sibling->l->col = sibling->col;
						sibling->col = parent->col;
						rrot(parent, tree);
					} else {
						sibling->l->col = parent->col;
						rrot(sibling, tree);
						lrot(parent, tree);
					}
				} else {
					if (sibling == parent->l) {
						sibling->r->col = parent->col;
						lrot(sibling, tree);
						rrot(parent, tree);
					} else {
						sibling->r->col = sibling->col;
						sibling->col = parent->col;
						lrot(parent, tree);
					}
				}
				parent->col = 0;
			} else {
				sibling->col = 1;

				if (!parent->col)
					fixdoubleblack(parent, tree);
				else
					parent->col = 0;
			}
		}
	}
}

static void nsrt_repair(Tree *tree, Node *node)
{
	Node *parent = NULL;
	Node *grandparent = NULL;
	Node *uncle = NULL;
	int tempcol;

	while (node != tree->root && node->col != 0 && 
	       node->p->col == 1) {

		parent = node->p;
		grandparent = node->p->p;

		if (parent == grandparent->l) {
			uncle = grandparent->r;

			if (uncle && uncle->col) {
				grandparent->col = 1;
				parent->col = 0;
				uncle->col = 0;
				node = grandparent;
			} else {
				if (node == parent->r) {
					lrot(parent, tree);
					node = parent;
					parent = node->p;
				}
				rrot(grandparent, tree);
				tempcol = parent->col;
				parent->col = grandparent->col;
				grandparent->col = tempcol;
				node = parent;
			}
		} else {
			uncle = grandparent->l;

			if (uncle && uncle->col) {
				grandparent->col = 1;
				parent->col = 0;
				uncle->col = 0;
				node = grandparent;
			} else {
				if (node == parent->l) {
					rrot(parent, tree);
					node = parent;
					parent = node->p;
				}
				lrot(grandparent, tree);
				tempcol = parent->col;
				parent->col = grandparent->col;
				grandparent->col = tempcol;
				node = parent;
			}
		}
	}
}

static void lrot(Node *node, Tree *tree)
{
	Node *temp = node->r;
	node->r = temp->l;

	if (node->r) {
		node->r->p = node;
	}
	temp->p = node->p;
	if (!node->p) {
		tree->root = temp;
	
	} else if (node == node->p->l) {
		node->p->l = temp;

	} else {
		node->p->r = temp;
	}
	temp->l = node;
	node->p = temp;
}
static void rrot(Node *node, Tree *tree)
{
	Node *temp = node->l;
	node->l = temp->r;

	if (node->l) {
		node->l->p = node;
	}
	temp->p = node->p;
	if (!node->p) {
		tree->root = temp;

	} else if (node == node->p->l) {
		node->p->l = temp;

	} else {
		node->p->r = temp;
	}
	temp->r = node;
	node->p = temp;
}
