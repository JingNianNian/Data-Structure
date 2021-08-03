#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996)
#pragma warning(disable:6031)
#pragma warning(disable:6011)
#define INANDOUTFORMAT "%c"
#define MAXN 1001
#define COMP(x,y) (x) == '*' || (x) == '/' && (y) == '+' || (y) == '-' ? 1 : 0

typedef char ElemType;

typedef struct {
	ElemType elem[MAXN];
	int top;
}Stack;

void push(Stack* s, ElemType e) {
	if ((*s).top > MAXN) {
		printf("栈满！\n");
		return;
	}

	(*s).elem[(*s).top] = e;
	(*s).top += 1;
}
ElemType getTopElem(Stack* s) {
	if ((*s).top == 0) {
		return -1;
	}
	return (*s).elem[(*s).top - 1];
}
void pop(Stack* s, ElemType* e) {
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

void print(Stack* s) {
	for (int i = 0; i < (*s).top; i++)
	{
		printf(INANDOUTFORMAT, (*s).elem[i]);
	}
}

void test() {
	Stack s = initStack();
	int input = 0;
	while (~scanf("%d", &input))
	{
		if (input == 1) {
			ElemType e;
			getchar();
			printf("请输入：");
			scanf(INANDOUTFORMAT, &e);
			push(&s, e);
			print(&s);
		}
		else {
			ElemType e;
			pop(&s, &e);
			printf(INANDOUTFORMAT, e);
		}
	}
}

void RPN() {
	Stack s = initStack();
	int input = 0;
	char inp[100] = { 0 };
	printf("请输入RPN表达式(数字用空格隔开):");
	gets(inp);
	double temp = 0;
	int cnt = 0;
	for (int i = 0; i < strlen(inp); i++)
	{
		if (inp[i] == '+' || inp[i] == '-' || inp[i] == '*' || inp[i] == '/') {
			ElemType a, b;
			pop(&s, &a);
			pop(&s, &b);
			push(&s, inp[i] == '+' ? a + b : inp[i] == '-' ? b - a : inp[i] == '*' ? a * b : b / a);
		}
		else if (inp[i] == ' ') {
			temp /= pow(10, 7 - cnt + 1);
			push(&s, temp);
			cnt = 0;
			temp = 0;
		}
		else if (inp[i] >= '0' && inp[i] <= '9') {
			temp += pow(10, 7 - cnt) * (inp[i] - '0');
			cnt++;
		}
		else {
			printf("有误");
			return -1;
		}
	}
	printf("%lf", s.elem[0]);
}

void mid2rpn() {
	//  1+(2-3)*4+10/5
	/*
	1. 数字直接加入后缀表达式
	2.如果是‘(’, 入栈
	3.如果是‘)’, 则依次把栈中的运算符加入后缀表达式，直到出现‘(’并从栈中删除它
	4.如果是运算符 + - / *
		a.栈空或者栈顶元素为‘(’, 入栈
		b.高于栈顶元素优先级，入栈
		c.否则依次弹出栈顶运算符，直到遇到一个优先级小于它的运算符或者是遇到‘(’为止
	5.遍历完成后，如果栈非空则依次弹出所有栈顶元素加入到表达式当中
	*/

	Stack s = initStack();
	char in[1001];
	int count = 0;
	gets(in);
	for (int  i = 0; i < strlen(in); i++)
	{
		if (in[i] == '(')
		{
			push(&s, in[i]);
			continue;
		}
		if (in[i] >= '0' && in[i] <= '9')
		{
			int temp = 0, cnt = 0;
			const int a = 1e7; 
			int j = 0;
			for (; in[j + i] <= '9' && in[j + i] >='0'; j++)
			{
				temp += pow(10, 7 - cnt) * (in[j + i] - '0');
				cnt++;
			}
			temp /= pow(10, 7 - cnt + 1);
			printf("%d ", temp);
			i += (j - 1);
			continue;
		}
		if (in[i] == ')')
		{
			char t = ' ';
			while (1) {
				pop(&s, &t);
				printf("%c ", t);
				if (getTopElem(&s) == '(') {
					pop(&s, &t);
					break;
				}
			}
			continue;
		}
		if (in[i] == '*' || in[i] == '+' || in[i] == '-' || in[i] == '/')
		{
			if (s.top == 0 || getTopElem(&s) == '(') {
				push(&s, in[i]);
				continue;
			}

			if (COMP(in[i], getTopElem(&s))) {
				push(&s, in[i]);
				continue;
			}
			else {
				char t = ' ';
				do
				{
					pop(&s, &t);
					printf("%c ", t);
					if (getTopElem(&s) == '('
						|| COMP(getTopElem(&s),in[i])
						|| s.top == 0) break;
				} while (1);
				push(&s, in[i]);
				continue;
			}
		}
	}
	if (s.top > 0) {
		char t = ' ';
		while (s.top != 0) {
			pop(&s, &t);
			printf("%c ", t);
		}
	}
}

int main() {
}