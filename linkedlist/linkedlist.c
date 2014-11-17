/* linkedlist.c */
#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int insert(struct Node *headList,int payload)
{
	struct Node*newNode;
	
	newNode = malloc(sizepof(struct Node));
	assert(newNode !=NULL);
	newNode->payload = payload;
	newNode->next = headList;
	headList = newNode;
	return 0;
}

struct Node
{
	int payload;
	struct Node* next;
};

int insert(struct Node *headList,int payload);
int delete(struct Node *headList,int payload);
struct Node *find(struct Node *headList, int payload);
void printAll(struct Node*headList);
void deleteAll(struct Node *headList);
