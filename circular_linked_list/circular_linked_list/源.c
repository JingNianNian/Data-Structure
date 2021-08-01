#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define INANDOUTFORMAT "%d"
#define MAXDEL 100
#pragma warning (disable:4996)
#pragma warning (disable:6031)
#pragma warning (disable:6011)
#define true 1
#define false 0

typedef int Status;
typedef int ElemType;

typedef struct dList{
	ElemType val;
	struct dList* prior, * next;
}dList;

Status freeNode(dList* node) {
	// ToDo : 这里释放有点问题 啊 啊 啊 囸 ~
	return OK;
}

Status inputVal(ElemType* num) {
	printf("请输入值(初始化输入-1来停止）：");
	scanf(INANDOUTFORMAT, num);
	return *num != -1 ? OK : -1;
}

Status deleteNodeByLoc(dList** head, int loc) {
	dList* delLoc = *head;
	if (delLoc == NULL)
	{
		printf("此表为空，请先初始化！");
		return ERROR;
	}
	int cnt = 1;
	do
	{
		if (cnt == loc) break;
		delLoc = (*delLoc).next;
		cnt++;
	} while (delLoc != *head);

	if (cnt != loc) {
		printf("未找到此位置\n");
		return ERROR;
	}

	(*delLoc).prior->next = (*delLoc).next;
	(*delLoc).next->prior = (*delLoc).prior;
	if (loc == 1) {
		*head = (*delLoc).next;
	}

	freeNode(delLoc);

	return OK;
}

Status deleteNodeByVal_F(dList** head, int delVal) {
	dList* delLoc = *head;
	if (delLoc == NULL)
	{
		printf("此表为空，请先初始化！");
		return ERROR;
	}

	int cnt = 1;
	do
	{
		if ((*delLoc).val == delVal) break;
		delLoc = (*delLoc).next;
		cnt++;
	} while (delLoc != *head);

	if (delLoc == *head && cnt != 1) {
		printf("未找到此值\n");
		return ERROR;
	}

	(*delLoc).prior->next = (*delLoc).next;
	(*delLoc).next->prior = (*delLoc).prior;
	if (cnt == 1) {
		*head = (*delLoc).next;
	}
	freeNode(delLoc);

	

	return OK;
}

Status deleteNodeByVal_A(dList** head, int delVal) {
	dList* delLoc[MAXDEL];
	dList* temp = *head;
	if (temp == NULL)
	{
		printf("此表为空，请先初始化！");
		return ERROR;
	}
	
	int cnt = 0;
	do
	{
		if ((*temp).val == delVal) {
			delLoc[cnt++] = temp;
		}
		temp = (*temp).next;
	} while (temp != *head);

	if (cnt == 0) {
		printf("未找到此值\n");
		return ERROR;
	}

	for (int i = 0; i < cnt; i++)
	{
		(*delLoc[i]).prior->next = (*delLoc[i]).next;
		(*delLoc[i]).next->prior = (*delLoc[i]).prior;
		freeNode(delLoc[i]);
	}
	if (cnt != 0) {
		*head = (delLoc[cnt - 1])->next;
	}
	return OK;
}

Status initDlist(dList** head) {
	dList* loc = *head;
	while (true)
	{
		if (*head == NULL) {
			dList* temp = (dList*)calloc(1, sizeof(dList));
			inputVal(&(*temp).val);
			*head = temp;
			(*temp).prior = temp;
			(*temp).next = temp;
			loc = temp;
		}
		else {
			dList* temp = (dList*)calloc(1, sizeof(dList));
			if (inputVal(&(*temp).val) == -1) {
				break;
			}
			(**head).prior = temp;
			(*loc).next = temp;
			(*temp).next = *head;
			(*temp).prior = loc;
			loc = temp;
		}
	}
	return OK;
}

Status insertByLoc(dList** head, int loc) {
	dList* insertLoc = *head;
	if (insertLoc == NULL)
	{
		printf("此表为空，请先初始化！");
		return ERROR;
	}
	int cnt = 1;
	do
	{
		if (cnt == loc) break;
		insertLoc = (*insertLoc).next;
		cnt++;
	} while (insertLoc != *head);

	if (cnt != loc) {
		printf("未找到此位置\n");
		return ERROR;
	}

	dList* temp = (dList*)calloc(1, sizeof(dList));
	inputVal(&(*temp).val);
	(*temp).next = (*insertLoc).next;
	(*temp).prior = insertLoc;
	(*insertLoc).next->prior = temp;
	(*insertLoc).next = temp;
	return OK;
}

void printDlist(dList** head) {
	dList* print = *head;

	if (print == NULL)
	{
		printf("此表为空！");
		return;
	}
	int cnt = 0;
	do
	{
		cnt++;
		printf("\ncnt: %d\n", cnt);
		printf("val: ");
		printf(INANDOUTFORMAT, (*print).val);
		printf("\n");
		printf("prior: %p\n", (*print).prior);
		printf("next: %p\n", (*print).next);
		print = (*print).next;
	} while (print != *head);
	return;
}

int main() {
	dList* head = NULL;

	printf("initialize:\n");
	initDlist(&head);
	printDlist(&head);

	printf("insert:\n");
	insertByLoc(&head, 1);
	insertByLoc(&head, 3);
	printDlist(&head);

	printf("\ndel by loc:\n");
	deleteNodeByLoc(&head, 1);
	printDlist(&head);

	printf("\ndel by val f:\n");
	deleteNodeByVal_F(&head, 3);
	printDlist(&head);

	printf("\ndel by val f:\n");
	deleteNodeByVal_A(&head, 2);
	printDlist(&head);

	return 0;
}