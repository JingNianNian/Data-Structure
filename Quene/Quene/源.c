#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996)
#pragma warning(disable:6031)
#pragma warning(disable:6011)
#define INANDOUTFORMAT "%d"
#define MAXN 1001
/*
   队列：先进先出
*/
typedef int ElemType;

typedef struct {
	ElemType val;
	struct QNode* next;
}QNode;

typedef struct {
	QNode* head;
	QNode* rear;
	int length;
}LinkQuene;

void input(ElemType* e) {
	printf("请输入值：");
	scanf(INANDOUTFORMAT, e);
}

QNode* newqNode(ElemType val) {
	QNode* q = (QNode*)malloc(sizeof(QNode));
	q->next = NULL;
	q->val = val;
	return q;
}

LinkQuene* initLinkQuene() {
	LinkQuene* l = (LinkQuene*)malloc(sizeof(LinkQuene));
	l->length = 0;
	ElemType in;
	printf("input : ");
	while (~scanf(INANDOUTFORMAT, &in))
	{
		if (in == -1) break;

		if (l->length == 0)
		{
			QNode* q = newqNode(in);
			printf("loc:%p\n", q);
			l->head = q;
			l->rear = q;
			l->length++;
		}
		else
		{
			QNode* q = newqNode(in);
			printf("loc:%p\n", q);
			l->rear->next = q;
			l->rear = q;
			l->length;
		}
		printf("input : ");
	}
	return l;
}

ElemType outQuene(LinkQuene* l) {
	QNode* t = (*l).head;
	(*l).head = (*l).head->next;
	ElemType ret = (*t).val;
	free(t);
	return ret;
}

void inQuene(LinkQuene* l,ElemType val) {
	QNode* q = newqNode(val);
	(*l).rear->next = q;
	(*l).rear = q;
	(*l).length++;
}

void printQuene(LinkQuene* l) {
	QNode* st = (*l).head;
	do
	{
		printf("%d->", (*st).val);
		st = (*st).next;
	} while (st != NULL);
	printf("\n");
}

int main() {
	LinkQuene* l = initLinkQuene();
	printQuene(l);
	inQuene(l, 9);
	printQuene(l);
	ElemType temp = outQuene(l);
	printf("out_elem : %d\n", temp);
	printQuene(l);
}