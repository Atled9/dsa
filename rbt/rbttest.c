#include <stdio.h>
#include "rbt.h"

int main()
{
	Tree *tree = initTree();
	nsrt(tree, 0, "0");
	nsrt(tree, 1, "1");
	nsrt(tree, 2, "2");
	nsrt(tree, 3, "3");
	nsrt(tree, 4, "4");
	nsrt(tree, 5, "5");
	nsrt(tree, 6, "6");
	nsrt(tree, 7, "7");
	nsrt(tree, 8, "8");
	nsrt(tree, 9, "9");
	inorder_traverse(tree);

	/*
	backtrace_t(tree, 7);
	backtrace_t(tree, 2);
	backtrace_t(tree, 4);
	*/
	/*
	display_tree(tree);
	rot_t(tree, 1, 'r');
	*/
	display_tree(tree);
	rmve(tree, 1);
	display_tree(tree);

	freeTree(tree);

	return 0;
}
