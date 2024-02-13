#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>



typedef struct ListNode { //이중연결리스트
	int data;
	struct ListNode* llink;
	struct ListNode* rlink;
}listNode;

typedef struct LinkedList {
	listNode* head;
}linkedList;

linkedList* initList(){
	linkedList* L;
	L = (linkedList*)malloc(sizeof(linkedList));
	L->head = NULL;
	return L;
}

void insertFirst(linkedList* L, int x) {
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->data = x;

	if (L->head == NULL) {
		L->head = newNode;
		newNode->llink = NULL;
		newNode->rlink = NULL;
	}
	else {
		newNode->rlink = L->head;
		L->head->llink = newNode;
		L->head = newNode;
		newNode->llink = NULL;
	}
}

void insertLast(linkedList* L, int x) {
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->data = x;
	listNode* temp;

	if (L->head == NULL) {
		L->head = newNode;
		newNode->llink =NULL;
		newNode->rlink = NULL;
	}
	else {
		temp = L->head;
		while (temp != NULL) {
			temp = temp->rlink;
		}
		temp->rlink = newNode;
		newNode->llink = temp;
		newNode->rlink = NULL;
	}
}

void printlist(linkedList* L) {
	listNode* temp;
	temp = L->head;
	while (temp != NULL) {
		printf("%d <-> ", temp->data);
		temp = temp->rlink;
	}
	printf("\n");
}

void insert(linkedList* L, listNode* pre, int x) {
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->data = x;

	if (L->head == NULL) {
		newNode->rlink = NULL;
		newNode->llink = NULL;
		L->head = newNode;
	}
	else if (pre == NULL) {
		insertFirst(L, x);
	}
	else {
		newNode->rlink = pre->rlink;
		pre->rlink = newNode;
		newNode->llink = pre;
		if (newNode->rlink != NULL)
			newNode->rlink->llink = newNode;
	}
}

listNode* search(linkedList* L, int x) {
	listNode* temp;
	temp = L->head;
	while (temp != NULL) {
		if (temp->data == x)
			return temp;
		else
			temp = temp->rlink;
	}
	return temp;
}

bool deleteNode(linkedList* L, listNode* p) {
	if (L->head == NULL)
		return false;

	if (p == NULL)
		return false;

	if (p->llink == NULL) {
		L->head = p->rlink;
		p->rlink->llink = NULL;
	}
	else
		p->llink->rlink = p->rlink;

	if (p->rlink != NULL)
		p->rlink->llink = p->llink;
	else
		p->llink->rlink = NULL;
	free(p);
	return true;
}


int main()
{
	linkedList l, * L;
	L = &l;
	L = initList();
	insertLast(L, 10);
	insertLast(L, 20);
	insertLast(L, 30);
	insertLast(L, 40);
	insertLast(L, 50);
	printlist(L);

	insertFirst(L, 5);
	printlist(L);

	listNode* q;
	q = search(L, 30);
	//insert(L, search(L, 30), 35);
	insert(L, q, 35);
	printlist(L);

	return 0;
}