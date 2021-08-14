#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
#pragma warning(disable:6031)
#pragma warning(disable:6011)
#define INANDOUTFORMAT "%c"

typedef char ElemType;

struct BinThNode
{
	ElemType val;
	struct BinThNode* lNode, * rNode;
	bool lTag, rTag;
};
typedef struct BinThNode BinThNode;

//前序遍历建树
void CreateBinThTree(BinThNode** T) {
	char c;
	scanf(INANDOUTFORMAT, &c);
	if (c == ' ') {
		*T = NULL;
	}
	else
	{
		*T = (BinThNode*)malloc(sizeof(BinThNode));
		(*T)->val = c;
		(*T)->lTag = false;
		(*T)->rTag = false;
		CreateBinThTree(&(*T)->lNode);
		CreateBinThTree(&(*T)->rNode);
	}
}

//中序遍历线索化
void inThreading(BinThNode** T,BinThNode** pre) {
	if (*T) {
		inThreading(&(*T)->lNode, &(*pre));
		if (!(*T)->lNode) {
			(*T)->lTag = true;
			(*T)->lNode = *pre;
		}
		if ((*pre) && !(*pre)->rNode) {
			(*pre)->rTag = true;
			(*pre)->rNode = *T;
		}
		*pre = *T;
		inThreading(&(*T)->rNode, &(*pre));
	}
}

// 有点问题，第一个访问到的节点右结点无法设置后继节点
//void inThreading(BinThNode* T, BinThNode* pre) {
//	if (T) {
//		inThreading(T->lNode, pre);
//		if (!T->lNode) {
//			T->lTag = true;
//			T->lNode = pre;
//		}
//		if (pre && !pre->rNode) {
//			pre->rTag = true;
//			pre->rNode = T;
//		}
//		pre = T;
//		inThreading(T->rNode, pre);
//	}
//}

int main() {
	BinThNode* tree = NULL;
	BinThNode* pre = NULL;
	CreateBinThTree(&tree);
	inThreading(&tree, &pre);
}