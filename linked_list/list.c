#include <stdlib.h>

typedef struct Node {
	void *data;
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

void inserthead(List *list, void *data)
{
	Node *newnode = (Node *)malloc(sizeof(Node));
	newnode->data = data;

	if (!list->head) {
		list->head = newnode;
		return;
	}
	newnode->next = list->head;
	list->head = newnode;
}
void inserttail(List *list, void *data)
{
	Node *newnode = (Node *)malloc(sizeof(Node));
	newnode->data = data;
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

void *removehead(List *list)
{
	if (!list->head) {
		return NULL;
	}
	Node *temp = list->head;
	void *data = list->head->data;

	list->head = list->head->next;
	free(temp);
	return data;
}
void *removetail(List *list)
{
	if (!list->head) {
		return NULL;
	}
	Node *temp;
	void *data;

	if (!list->head->next) {
		temp = list->head;
		data = list->head->data;

		list->head = NULL;
		free(temp);
		return data;
	}
	Node *current = list->head;
	while (current->next->next)
		current = current->next;
	
	temp = current->next;
	data = current->next->data;

	current->next = NULL;
	free(temp);
	return data;
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
