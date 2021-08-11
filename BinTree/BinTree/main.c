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
		printf("栈满！\n");
		return;
	}

	(*s).elem[(*s).top] = e;
	(*s).top += 1;
}

void pop(Stack* s, Node* e) {
	if ((*s).top < 1) {
		printf("栈空！\n");
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


//前序遍历创建二叉树
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
// 前序遍历输出（递归）
void preorderTraverse(Node* T, int level) {
	if (T) {
		// 输出值
		printf(INANDOUTFORMAT, T->val);
		printf(" level: %d\n", level);
		// 先左后右
		preorderTraverse(T->lNode, level + 1);
		preorderTraverse(T->rNode, level + 1);
	}
}
/*
// 前序遍历输出（递归）
void PreOrderTraverse(Node* T)
{
	Stack S = initStack();   //创建并初始化堆栈S
	while (T || !IsEmpty(S))
	{
		while (T)        //一直向左并将沿途节点访问（打印）后压入堆栈 
		{
			printf("%c\n", T->val);
			push(&S, *T);
			T = T->lNode;
		}
		if (!IsEmpty(S))
		{
			pop(&S,T);    //节点弹出堆栈
			T = T->rNode;  //转向右子树
		}
	}
}*/

int main() {
	Node* tree = NULL;
	scanf("%s", input);
	CreatedBiTree(&tree);
	preorderTraverse(tree,1);
}