#include <C++AllHeaderFiles.h>
#pragma warning(disable:4996)
#pragma warning(disable:6031)
#pragma warning(disable:6011)
#define INANDOUTFORMAT "%c"
#define MAXN 1001
#define COMP(x,y) (x) == '*' || (x) == '/' && (y) == '+' || (y) == '-' ? 1 : 0
using namespace std;
typedef int ElemType;

//typedef struct {
//	ElemType elem[MAXN];
//	int top;
//}Stack;
//
//void push(Stack* s, ElemType e) {
//	if ((*s).top > MAXN) {
//		printf("栈满！\n");
//		return;
//	}
//
//	(*s).elem[(*s).top] = e;
//	(*s).top += 1;
//}
//ElemType getTopElem(Stack* s) {
//	if ((*s).top == 0) {
//		return -1;
//	}
//	return (*s).elem[(*s).top - 1];
//}
//void pop(Stack* s, ElemType* e) {
//	if ((*s).top < 1) {
//		printf("栈空！\n");
//		return;
//	}
//
//	*e = (*s).elem[(*s).top - 1];
//	(*s).top -= 1;
//}
//
//int getStackSize(Stack* s) {
//	return (*s).top;
//}
//
//Stack initStack() {
//	Stack s;
//	s.top = 0;
//	return s;
//}
//
//void print(Stack* s) {
//	for (int i = 0; i < (*s).top; i++)
//	{
//		printf(INANDOUTFORMAT, (*s).elem[i]);
//	}
//}
//
//void test() {
//	Stack s = initStack();
//	int input = 0;
//	while (~scanf("%d", &input))
//	{
//		if (input == 1) {
//			ElemType e;
//			getchar();
//			printf("请输入：");
//			scanf(INANDOUTFORMAT, &e);
//			push(&s, e);
//			print(&s);
//		}
//		else {
//			ElemType e;
//			pop(&s, &e);
//			printf(INANDOUTFORMAT, e);
//		}
//	}
//}

vector<string> split(const string& str, const string& pattern)
{
	//const char* convert to char*
	char* strc = new char[strlen(str.c_str()) + 1];
	strcpy(strc, str.c_str());
	vector<string> resultVec;
	char* tmpStr = strtok(strc, pattern.c_str());
	while (tmpStr != NULL)
	{
		resultVec.push_back(string(tmpStr));
		tmpStr = strtok(NULL, pattern.c_str());
	}

	delete[] strc;

	return resultVec;
}


void RPN(const char* RPN_expression) {
	stack<double> s;
	auto allele = split(RPN_expression, " ");
	for (auto i = allele.begin(); i != allele.end(); i++)
	{
		if (*i == "+" || *i == "-" || *i == "*" || *i == "/")
		{
			auto a = s.top();s.pop();
			auto b = s.top();s.pop();
			s.push(*i == "+" ? a + b : *i == "-" ? b - a : *i == "*" ? a * b : b / a);
		}
		else if(i->empty()){
			continue;
		}
		else {
			s.push(atof((*i).c_str()));
		}
	}
	printf("%.2lf", s.top());
}

string* mid2rpn(const char* infix_expression) {
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
	string* ret = new string("");
	stack<char> s;
	int count = 0;
	for (int  i = 0; i < strlen(infix_expression); i++)
	{
		if (infix_expression[i] == '(')
		{
			s.push(infix_expression[i]);
			continue;
		}
		if (infix_expression[i] >= '0' && infix_expression[i] <= '9')
		{
			int temp = 0, cnt = 0;
			const int a = 1e7; 
			int j = 0;
			for (; infix_expression[j + i] <= '9' && infix_expression[j + i] >='0'; j++)
			{
				temp += pow(10, 7 - cnt) * (infix_expression[j + i] - '0');
				cnt++;
			}
			temp /= pow(10, 7 - cnt + 1);
			ret->append(to_string(temp));
			ret->append(" ");
			i += (j - 1);
			continue;
		}
		if (infix_expression[i] == ')')
		{
			while (1) {
				char t = s.top();
				s.pop();
				ret->append(&t, 1);
				ret->append(" ");
				if (s.top() == '(') {
					s.pop();
					break;
				}
			}
			continue;
		}
		if (infix_expression[i] == '*' || infix_expression[i] == '+' || infix_expression[i] == '-' || infix_expression[i] == '/')
		{
			if (s.size() == 0 || s.top() == '(') {
				s.push(infix_expression[i]);
				continue;
			}

			if (COMP(infix_expression[i], s.top())) {
				s.push(infix_expression[i]);
				continue;
			}
			else {
				do
				{
					char t = s.top();
					s.pop();
					ret->append(&t,1);
					ret->append(" ");
					if (s.size() == 0
						|| COMP(s.top(), infix_expression[i])
						|| s.top() == '(') break;
				} while (1);
				s.push(infix_expression[i]);
				continue;
			}
		}
	}
	if (s.size() > 0) {
		while (!s.empty()) {
			char t = s.top();
			s.pop();
			ret->append(&t, 1);
			if (s.empty()) break;
			ret->append(" ");
		}
	}
	return ret;
}

int main() {
	auto res = mid2rpn("1+2-3*4");
	RPN(res->c_str());
}