#include <C++AllHeaderFiles.h>
using namespace std;
#pragma warning(disable:6031)
#pragma warning(disable:4996)

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

//前序遍历二叉树（非递归）
void preorderTraverseN(Node* H) {
	stack<Node*> s;
	Node* cur = NULL;
	s.push(H);
	while (!s.empty())
	{
		cur = s.top();
		s.pop();
		cout << cur->val << endl;
		if (cur->rNode != NULL) {
			s.push(cur->rNode);
		}
		if (cur->lNode != NULL) {
			s.push(cur->lNode);
		}
	}
}

//中序遍历二叉树（非递归）
void inorderTraverseN(Node* H) {
	stack<Node*> s;
	while (!s.empty() || H != NULL)
	{
		if (H != NULL) {
			s.push(H);
			H = H->lNode;
		}
		else
		{
			H = s.top();
			s.pop();
			cout << H->val << endl;
			H = H->rNode;
		}
	}
}

//后序遍历二叉树（非递归）
void posorderTraverseN(Node* H) {
	stack<Node*> s;
	stack<Node*> collection;
	Node* cur = NULL;
	s.push(H);
	while (!s.empty())
	{
		cur = s.top();
		s.pop();
		collection.push(cur);
		if (cur->lNode != NULL) {
			s.push(cur->lNode);
		}
		if (cur->rNode != NULL) {
			s.push(cur->rNode);
		}
	}
	while (!collection.empty())
	{
		cout << collection.top()->val << endl;
		collection.pop();
	}
}

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
// 中序遍历输出（递归）
void midorderTraverse(Node* T, int level) {
	if (T) {
		preorderTraverse(T->lNode, level + 1);
		// 输出值
		printf(INANDOUTFORMAT, T->val);
		printf(" level: %d\n", level);
		// 左根右
		preorderTraverse(T->rNode, level + 1);
	}
}
// 后序遍历输出（递归）
void postorderTraverse(Node* T, int level) {
	if (T) {
		// 左右根
		preorderTraverse(T->lNode, level + 1);
		preorderTraverse(T->rNode, level + 1);
		// 输出值
		printf(INANDOUTFORMAT, T->val);
		printf(" level: %d\n", level);
	}
}

int main() {
	Node* tree = NULL;
	scanf("%s", input);
	CreatedBiTree(&tree);
	inorderTraverseN(tree);
}