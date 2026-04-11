#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;

typedef struct {
	Node *head;
} List;

List *initList(void)
{
	List *list = (List *)malloc(sizeof(List));
	list->head = NULL;

	return list;
}

void inserthead(List *list, int val)
{
	Node *newnode = (Node *)malloc(sizeof(Node));
	newnode->data = val;

	if (!list->head) {
		list->head = newnode;
		return;
	}
	newnode->next = list->head;
	list->head = newnode;
}
void inserttail(List *list, int val)
{
	Node *newnode = (Node *)malloc(sizeof(Node));
	newnode->data = val;
	newnode->next = NULL;

	if (!list->head) {
		list->head = newnode;
		return;
	}
	Node *current = list->head;
	while (current->next)
		current = current->next;

	current->next = newnode;
}

int removehead(List *list)
{
	if (!list->head) {
		printf("empty list: returning -1\n");
		return -1;
	}
	Node *temp = list->head;
	int val = list->head->data;

	list->head = list->head->next;
	free(temp);
	return val;
}
int removetail(List *list)
{
	if (!list->head) {
		printf("empty list: returning -1\n");
		return -1;
	}
	Node *temp;
	int val;

	if (!list->head->next) {
		temp = list->head;
		val = list->head->data;

		list->head = NULL;
		free(temp);
		return val;
	}
	Node *current = list->head;
	while (current->next->next)
		current = current->next;
	
	temp = current->next;
	val = current->next->data;

	current->next = NULL;
	free(temp);
	return val;
}

void freeList(List *list)
{
	Node *current = list->head;
	Node *temp = NULL;

	while (current) {
		temp = current;
		current = current->next;
		free(temp);
	}
	free(list);
}
