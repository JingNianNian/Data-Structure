#include <stdio.h>
#define MAXSIZE 1010 //The available space is MAXSIZE - 2
#define OK 1;
#define ERROR 0;
#pragma warning(disable:4996)
#pragma warning(disable:6031)
typedef int Elemtype;
typedef struct {
	int cur;
	Elemtype val;
}staticLink, c[MAXSIZE];

int lastNodeCur;
/// <summary>
/// 
/// </summary>
/// <param name="l"></param>
/// <returns></returns>
int initLink(c l) {
	for (int i = 0; i < MAXSIZE; i++)
	{
		l[i].cur = i + 1;
		l[i].val = (int)NULL;
	}
	l[MAXSIZE - 1].cur = 1;
	return OK;
}

/// <summary>
/// 
/// </summary>
/// <param name="l"></param>
/// <returns></returns>
int insert(c l) {
	if (l[0].cur >= MAXSIZE - 1)
	{
		printf("ERROR! The list is full.\n");
		return ERROR;
	}
	printf("please input value:");
	scanf("%d", &(l[l[0].cur].val));
	lastNodeCur = l[0].cur;
	l[0].cur = l[l[0].cur].cur;
	return OK;
}

/// <summary>
/// 
/// </summary>
/// <param name="l"></param>
/// <param name="loc"></param>
/// <returns></returns>
int insertByLoc(c l, int location) {
	// ToDo : ?
	if (l[0].cur >= MAXSIZE - 1)
	{
		printf("ERROR! The list is full.\n");
		return ERROR;
	}
	int cnt = 1;
	int loc = l[MAXSIZE - 1].cur;
	while (1)
	{
		if (cnt == location)
		{
			break;
		}
		loc = l[loc].cur;
		cnt++;
		if (loc == lastNodeCur && cnt != location) {
			printf("ERROR! The location is not exist.\n");
			return ERROR;
		}
	}

	int t_node_p = l[loc].cur;
	l[loc].cur = l[0].cur;
	printf("please input value:");
	scanf("%d", &l[l[loc].cur].val);
	l[0].cur = l[l[loc].cur].cur;
	if (l[loc].cur != t_node_p)
	{
		l[l[loc].cur].cur = t_node_p;
		l[lastNodeCur].cur = l[0].cur;
	}
	else
	{
		lastNodeCur = l[loc].cur;
	}
	return OK;
}


void printLink(staticLink* l) {
	int loc = l[MAXSIZE - 1].cur;
	while (1)
	{
		printf("%d\n", l[loc].val);
		loc = l[loc].cur;
		if (loc == lastNodeCur) {
			printf("%d\n", l[lastNodeCur].val);
			break; 
		}
	}
}


int main() {

	c stalink;
	initLink(stalink);
	for (int i = 0; i < 5; i++)
	{
		int status = insert(stalink);
		if (!status) break;
	}
	insertByLoc(stalink, 1);
	insertByLoc(stalink, 4);
	insertByLoc(stalink, 7);
	for (int i = 0; i < 2; i++)
	{
		int status = insert(stalink);
		if (!status) break;
	}
	printLink(stalink);
}