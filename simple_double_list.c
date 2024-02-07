#include<stdio.h>
#include<stdlib.h>


typedef struct ListNode { //원형 연결리스트 헤드는 마지막 노드
	int data;
	struct ListNode* link;
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
		newNode->link = newNode;
	}
	else {
		newNode->link = L->head->link;
		L->head->link = newNode;
	}
}

void insertLast(linkedList* L, int x) {
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->data = x;

	if (L->head == NULL) {
		L->head = newNode;
		newNode->link = newNode;
	}
	else {
		newNode->link = L->head->link;
		L->head->link = newNode;
		L->head = newNode;
	}
}

void printlist(linkedList* L) {
	listNode* temp;
	temp = L->head->link;
	while (temp != L->head) {
		printf("%d <-> ", temp->data);
		temp = temp->link;
	}
	printf("%d\n", temp->data);
}

void insert(linkedList* L, listNode* pre, int x) {
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->data = x;

	if (L->head == NULL) {
		L->head = newNode;
		newNode->link = newNode;
	}
	/*else if (pre == NULL) {
		newNode->link = L->head->link;
		L->head->link = newNode;
	}*/
	else {
		newNode->link = pre->link;
		pre->link = newNode;
	}
}

listNode* search(linkedList* L, int x) {
	listNode* temp;
	temp = L->head->link;
	while (temp != L->head) {
		if (temp->data == x)
			return temp;
		else
			temp = temp->link;
	}
	return temp;
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