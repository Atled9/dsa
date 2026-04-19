#include <stdio.h>
#include "bst.h"

int main()
{
	Tree *tree = initTree();

	nsrt(tree, 7, NULL);
	nsrt(tree, 3, NULL);
	nsrt(tree, 11, NULL);
	nsrt(tree, 1, NULL);
	nsrt(tree, 5, NULL);
	nsrt(tree, 9, NULL);
	nsrt(tree, 13, NULL);
	nsrt(tree, 0, NULL);
	nsrt(tree, 2, NULL);
	nsrt(tree, 4, NULL);
	nsrt(tree, 6, NULL);
	nsrt(tree, 8, NULL);
	nsrt(tree, 10, NULL);
	nsrt(tree, 12, NULL);
	nsrt(tree, 14, NULL);

	int keyarr[15];
	size_t size;

	size = traverse(tree, inorder, keyarr);
	for (size_t i = 0; i < size; i++)
		printf("%d ", *(keyarr + i));
	printf("\n");

	size = traverse(tree, preorder, keyarr);
	for (size_t i = 0; i < size; i++)
		printf("%d ", *(keyarr + i));
	printf("\n");

	size = traverse(tree, postorder, keyarr);
	for (size_t i = 0; i < size; i++)
		printf("%d ", *(keyarr + i));
	printf("\n");

	char *data;

	data = "OwO";
	setdata(tree, 3, data);
	printf("%s\n", (char *)getdata(tree, 3));

	data = "UwU";
	setdata(tree, 9, data);
	printf("%s\n", (char *)getdata(tree, 9));

	rmve(tree, 7);
	size = traverse(tree, inorder, keyarr);
	for (size_t i = 0; i < size; i++)
		printf("%d ", *(keyarr + i));
	printf("\n");

	freeTree(tree);
	return 0;
}
