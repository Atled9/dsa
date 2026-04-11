#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;

typedef struct {
	Node *tail;
} List;

List *initList(void)
{
	List *list = (List *)malloc(sizeof(List));
	list->tail = NULL;

	return list;
}

void inserthead(List *list, int val)
{
	Node *newnode = (Node *)malloc(sizeof(Node));
	newnode->data = val;

	if (!list->tail) {
		list->tail = newnode;
		newnode->next = newnode;
		return;
	}
	newnode->next = list->tail->next;
	list->tail->next = newnode;
}
void inserttail(List *list, int val)
{
	Node *newnode = (Node *)malloc(sizeof(Node));
	newnode->data = val;

	if (!list->tail) {
		list->tail = newnode;
		newnode->next = newnode;
		return;
	}
	newnode->next = list->tail->next;
	list->tail->next = newnode;
	list->tail = newnode;
}

int removehead(List *list)
{
	if (!list->tail) {
		printf("empty list: returning -1\n");
		return -1;
	}
	Node *temp = list->tail->next;
	int val = list->tail->next->data;

	if (temp == list->tail)
	{
		list->tail = NULL;
		free(temp);
		return val;
	}
	list->tail->next = list->tail->next->next;
	free(temp);
	return val;
}
int removetail(List *list)
{
	if (!list->tail) {
		printf("empty list: returning -1\n");
		return -1;
	}
	Node *temp = list->tail;
	int val = list->tail->data;

	if (temp == list->tail->next) {
		list->tail = NULL;
		free(temp);
		return val;
	}
	Node *current = list->tail->next;

	while (current->next != list->tail)
		current = current->next;
	
	current->next = list->tail->next;
	list->tail = current;
	return val;
	free(temp);
}

void freeList(List *list)
{
	if (!list->tail) {
		free(list);
		return;
	}
	Node *current = list->tail;
	Node *temp = NULL;
	do {
		temp = current;
		current = current->next;
		free(temp);
	} while (current != list->tail);

	free(list);
}
