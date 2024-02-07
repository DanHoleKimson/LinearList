#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Listdata {
	char name[30];
	int id;
} listData;

typedef struct Listnode {
	listData data;
	struct Listnode* link;
}listNode;

typedef struct LinkedList {
	listNode* head;
	int length;
}linkedList;

linkedList* initList() {
	linkedList* L;
	L = (linkedList*)malloc(sizeof(linkedList));
	L->head = NULL;
	L->length = 0;
	return L;
}

void insertLast(linkedList* L, listData item) {
	listNode* newNode, * temp;
	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->data = item;
	newNode->link = NULL;

	if (L->head == NULL)
		L->head = newNode;
	else {
		temp = L->head;
		while (temp->link != NULL) {
			temp = temp->link;
		}
		temp->link = newNode;
	}
	L->length++;
}

void printList(linkedList* L) {
	listNode* p;
	p = L->head;
	printf("�л����:\n");
	while (p != NULL) {
		printf("%s %d\n", p->data.name, p->data.id);
		p = p->link;
	}
	printf("\n");
}

listNode* search(linkedList* L, int id) {
	listNode* temp = L->head;
	while (temp != NULL) {
		if (temp->data.id == id) {
			return temp;
		}
		else {
			temp = temp->link;
		}
	}
	if (temp == NULL) {
		printf("ã���ô� �й��� �����ϴ�\n");
		return NULL;
	}
}

void insert(linkedList* L, listNode* pre, listData d) {
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->data = d;

	if (pre == NULL) {
		newNode->link = L->head;
		L->head = newNode;
	}
	else {
		newNode->link = pre->link;
		pre->link = newNode;
	}
	L->length++;

}

int delete(linkedList* L, listNode* p) {
	if (L->head == NULL)
		return 0;
	if (p == NULL)
		return 0;
	listNode* pre;
	pre = L->head;

	if (pre == p) {
		L->head = p->link;
		free(p);
		L->length--;
		return 1;
	}
	else {
		while (pre->link != p) {
			pre = pre->link;
			if (pre == NULL)
				return 0;
		}
		pre->link = p->link;
		free(p);
		L->length--;
		return 1;

	}

	
}

void reverse(linkedList* L) {
	listNode* p, * q, * r;

	p = L->head;
	q = NULL;
	while (p != NULL) {
		r = q;

		q = p;
		p = p->link;
		q->link = r;
	}
	L->head = q;
}

int getLength(linkedList* L) {
	return L->length;
}


int main(void)
{
	char temp[80];
	char* date[2] = { NULL,NULL };
	int i = 0;
	char command[50];

	FILE* fp;
	listData data;
	linkedList L, * q;
	q = &L;

	q = initList();



	fp = fopen("student.txt", "r");
	if (fp == NULL) {
		printf("Cannot open\n");
		return 1;
	}

	while (fgets(temp, 80, fp))
	{
		char* ptr = strtok(temp, " ");
		i = 0;
		while (ptr != NULL) {
			date[i] = ptr;
			i++;

			ptr = strtok(NULL, " ");
		}

		for (int j = 0; j < 2; j++) {
			if (date[j] != NULL) {
				if (j == 0) {
					strcpy(data.name, date[j]);
				}
				else {
					data.id = atoi(date[j]);
				}
			}
		}
		insertLast(q, data);
	}
	fclose(fp);
	printList(q);

	
	
	while (1) {
		printf("����� �Է��ϼ���: ");
		gets_s(command, sizeof(command));

		char* com[4] = { NULL,NULL,NULL,NULL };
		int p = 0;
		char* qtr = strtok(command, " ");
		int id_d;
		listNode* temp_1;
		listData temp_2;

		while (qtr != NULL) {
			com[p] = qtr;
			p++;

			qtr = strtok(NULL, " ");
		}

		if (strcmp(com[0], "print") == 0) {
			printList(q);
		}
		else if (strcmp(com[0], "search") == 0) {
			id_d = atoi(com[1]);
			temp_1 = search(q, id_d);
			if (temp_1 != NULL) {
				printf("ã���ô� �л��� �̸���: %s\n", temp_1->data.name);
			}
		}
		else if (strcmp(com[0], "exit") == 0) {
			break;
		}
		else if (strcmp(com[0], "insert") == 0) {
			char* rtr;
			char* str;
			int id_d_2;
			if (com[1] != NULL && com[2] != NULL && com[3] != NULL) {
				rtr = strtok(com[1], ",");
				id_d = atoi(rtr);
				str = strtok(com[2], ",");
				id_d_2 = atoi(str);

				temp_2.id = id_d_2;
				strcpy(temp_2.name, com[3]);

				if (!search(q, id_d)) {
					printf("Ȥ�� ù ��° ���� �߰��Ϸ��� �̴ϱ�?\n�׷ķ��� 'y'�� �ƴϸ� 'n'�� �����ּ���");
					char c = getch();
					if (c == 'y') {
						insert(q, NULL, temp_2);
					}
					else if (c == 'n') {
						printf("ù ��° ���� �߰��ϴ°� �ƴѰ����� �����մϴ�\ninsert ��ɾ �����մϴ�");
					}
					else {
						printf("��ȿ���� ���� ����Դϴ�\n");
					}
				}
				else {
					insert(q, search(q, id_d), temp_2);
				}
				printList(q);
			}
			else {
				printf("��ȿ���� ���� ����Դϴ�\n");
			}
			
			
		}
		else if (strcmp(com[0], "delete") == 0) {
			id_d = atoi(com[1]);
			temp_1 = search(q, id_d);

			if (temp_1 != NULL) {
				strcpy(temp_2.name, temp_1->data.name);
				temp_2.id = id_d;
				delete(q, temp_1);
				printf("�̸�: %s �й�: %d��/�� �����Ǿ����ϴ�\n", temp_2.name, temp_2.id);
			}
			else {
				printf("������ �����߽��ϴ�.\n");
			}

			printList(q);
		}
		else if (strcmp(com[0], "reverse") == 0) {
			reverse(q);
			printf("����Ʈ�� �������� �ٲ� �� ����մϴ�\n");
			printList(q);
		}
		else if (strcmp(com[0], "getLength") == 0) {
			int len;
			len = getLength(q);
			printf("���� ����Ʈ�� %d�� �Դϴ�\n", len);
		}
		else {
			printf("��ȿ���� ���� ����Դϴ�.\n");
		}
	}
	printf("���α׷��� �����մϴ�.");
	free(q);
	return 0;

}