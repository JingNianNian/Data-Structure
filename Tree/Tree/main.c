#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#pragma warning(disable:6031)
#pragma warning(disable:6011)
#define MAXSIZE 1000
#define ERROR 0
#define OK 1
#define INANDOUTFORMAT "%d"

typedef int ElemType;
typedef int Status;

typedef struct {
	ElemType val;
	struct Node* firstChild;
	struct Node* next;
	int parent;
	int level;
}Node;

typedef struct {
	Node nodes[MAXSIZE];
	int size;
	int rear;
}Tree;

Tree initTree(int val) {
	Tree tree;
	tree.nodes[0].parent = -1;
	tree.nodes[0].val = val;
	tree.nodes[0].level = 1;
	tree.nodes[0].firstChild = NULL;
	tree.size = 1;
	tree.rear = 1;
	return tree;
}

Status insertNode(Tree* tree,int level, int t_val, int insert_val) {
	if (level == 1)
	{
		if (tree->nodes[0].firstChild == NULL)
		{
			tree->nodes[0].firstChild = &(tree->nodes[tree->rear]);
		}
		else
		{
			Node* find = tree->nodes[0].firstChild;
			while (1)
			{
				if (find->next == NULL) break;
				find = find->next;
			}
			find->next = &(tree->nodes[tree->rear]);
		}
		tree->nodes[tree->rear].parent = 0;
		tree->nodes[tree->rear].level = level + 1;
		tree->nodes[tree->rear].firstChild = NULL;
		tree->nodes[tree->rear].next = NULL;
		tree->nodes[tree->rear].val = insert_val;
		tree->rear++;
		tree->size++;
		return OK;
	}
	else
	{
		// ≤ªª·¡À
	}
}

int main() {
	Tree tree = initTree(9);
	insertNode(&tree, 1, 9, 3);
	insertNode(&tree, 1, 9, 5);
	insertNode(&tree, 1, 9, 7);
}