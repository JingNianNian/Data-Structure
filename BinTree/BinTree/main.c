#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#pragma warning(disable:6031)
#pragma warning(disable:6011)
#define INANDOUTFORMAT "%c"
typedef char ElemType;

int cnt = 0;
char input[100];
struct Node{
	ElemType val;
	struct Node* lNode, * rNode;
};
typedef struct Node Node;
/*
typedef struct {
	Node elem[10010];
	int top;
}Stack;

void push(Stack* s, Node e) {
	if ((*s).top > 10010) {
		printf("ջ����\n");
		return;
	}

	(*s).elem[(*s).top] = e;
	(*s).top += 1;
}

void pop(Stack* s, Node* e) {
	if ((*s).top < 1) {
		printf("ջ�գ�\n");
		return;
	}

	*e = (*s).elem[(*s).top - 1];
	(*s).top -= 1;
}

int getStackSize(Stack* s) {
	return (*s).top;
}

Stack initStack() {
	Stack s;
	s.top = 0;
	return s;
}

int IsEmpty(Stack s) {
	return s.top == 0 ? 1 : 0;
}
*/


//ǰ���������������
void CreatedBiTree(Node** T) {
	char c = input[cnt++];
	if (c == '#')
	{
		*T = NULL;
	}
	else
	{
		*T = (Node*)malloc(sizeof(Node));
		(*T)->val = c;
		CreatedBiTree(&(*T)->lNode);
		CreatedBiTree(&(*T)->rNode);
	}
}
// ǰ�����������ݹ飩
void preorderTraverse(Node* T, int level) {
	if (T) {
		// ���ֵ
		printf(INANDOUTFORMAT, T->val);
		printf(" level: %d\n", level);
		// �������
		preorderTraverse(T->lNode, level + 1);
		preorderTraverse(T->rNode, level + 1);
	}
}
/*
// ǰ�����������ݹ飩
void PreOrderTraverse(Node* T)
{
	Stack S = initStack();   //��������ʼ����ջS
	while (T || !IsEmpty(S))
	{
		while (T)        //һֱ���󲢽���;�ڵ���ʣ���ӡ����ѹ���ջ 
		{
			printf("%c\n", T->val);
			push(&S, *T);
			T = T->lNode;
		}
		if (!IsEmpty(S))
		{
			pop(&S,T);    //�ڵ㵯����ջ
			T = T->rNode;  //ת��������
		}
	}
}*/

int main() {
	Node* tree = NULL;
	scanf("%s", input);
	CreatedBiTree(&tree);
	preorderTraverse(tree,1);
}