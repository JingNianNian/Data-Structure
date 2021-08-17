#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#pragma warning(disable:4996)
#pragma warning(disable:6011)
#pragma warning(disable:6031)
typedef char ElemType;
struct HufNode
{
	ElemType val;
	int weg;
	bool isWegNode;
	struct HufNode* lNode;
	struct HufNode* rNode;
};
typedef struct HufNode HufNode;
HufNode* treeNode = NULL;
HufNode Nodes[128];
char HuffmanCodeTable[128][8] = { '\0' };
int NodeCnt = 0;
char in[16000] = { 0 };
int cmp(const void* x, const void* y) {
	return ((HufNode*)x)->weg - ((HufNode*)y)->weg;
}

void inputAndPretreatment() {
	printf("请输入原字符串：");
	//scanf 不吃空格。。。
	gets(in);
	// scanf("%s",in);
	int len = strlen(in);
	for (int i = 0; i < len; i++) {
		if (!Nodes[in[i]].weg) NodeCnt++;
		Nodes[in[i]].weg++;
	}
	qsort(&Nodes[0], 128, sizeof(HufNode), cmp);
}

void initNodesArray() {
	for (int i = 0; i < 128; i++) {
		Nodes[i].isWegNode = false;
		Nodes[i].val = (ElemType)i;
		Nodes[i].weg = 0;
		Nodes[i].lNode = NULL;
		Nodes[i].rNode = NULL;
	}
}

void buildHufTree(HufNode** head) {
	while (NodeCnt) {
		HufNode* ltemp = (HufNode*)malloc(sizeof(HufNode));
		HufNode* rtemp = (HufNode*)malloc(sizeof(HufNode));
		ltemp->isWegNode = Nodes[128 - NodeCnt].isWegNode;
		ltemp->weg = Nodes[128 - NodeCnt].weg;
		ltemp->lNode = Nodes[128 - NodeCnt].lNode;
		ltemp->rNode = Nodes[128 - NodeCnt].rNode;
		ltemp->val = Nodes[128 - NodeCnt].val;
		Nodes[128 - NodeCnt].weg = 0;
		rtemp->isWegNode = Nodes[129 - NodeCnt].isWegNode;
		rtemp->weg = Nodes[129 - NodeCnt].weg;
		rtemp->lNode = Nodes[129 - NodeCnt].lNode;
		rtemp->rNode = Nodes[129 - NodeCnt].rNode;
		rtemp->val = Nodes[129 - NodeCnt].val;
		Nodes[129 - NodeCnt].weg = 0;
		HufNode* wegNode = (HufNode*)malloc(sizeof(HufNode));
		wegNode->isWegNode = true;
		wegNode->lNode = ltemp;
		wegNode->rNode = rtemp;
		wegNode->weg = ltemp->weg + rtemp->weg;
		wegNode->val = '\0';
		if (NodeCnt == 2) {
			*head = wegNode;
			return;
		}
		Nodes[0].isWegNode = wegNode->isWegNode;
		Nodes[0].lNode = wegNode->lNode;
		Nodes[0].rNode = wegNode->rNode;
		Nodes[0].weg = wegNode->weg;
		Nodes[0].val = wegNode->val;
		NodeCnt--;
		qsort(&Nodes[0], 128, sizeof(HufNode), cmp);
	}
}

void preorderTraversal(HufNode* t, int route) {
	if (t)
	{
		if (!t->isWegNode) {
			char r[9] = { '\0' };
			itoa(route, r, 10);
			strcat(HuffmanCodeTable[(int)t->val], &r[1]);
			printf("%c : %s\n", t->val, HuffmanCodeTable[(int)t->val]);
		}
		preorderTraversal(t->lNode, route * 10);
		preorderTraversal(t->rNode, route * 10 + 1);
	}
}

void printHuffmanCode() {
	printf("HuffmanCode：");
	int len = strlen(in);
	for (int i = 0; i < len; i++)
	{
		printf("%s", HuffmanCodeTable[in[i]]);
	}
}

int main() {
	initNodesArray();
	inputAndPretreatment();
	buildHufTree(&treeNode);
	printf("HuffmanCodeTable:\n");
	preorderTraversal(treeNode, 1);
	printHuffmanCode();
	return 0;
}