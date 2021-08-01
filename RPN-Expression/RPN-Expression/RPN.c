#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996)
#pragma warning(disable:6031)
#pragma warning(disable:6011)
#define INANDOUTFORMAT "%lf"
#define MAXN 100

typedef double ElemType;

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

int main() {
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
	/*while (~scanf("%d", &input))
	{
		if(input == 1){
			ElemType e;
			getchar();
			printf("请输入：");
			scanf(INANDOUTFORMAT, &e);
			push(&s, e);
			print(&s);
			printf("\n");
			}
		else{
			ElemType e;
			pop(&s, &e);
			printf(INANDOUTFORMAT, e);
			printf("\n");
		}
	}*/
}