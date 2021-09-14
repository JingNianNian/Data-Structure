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

//ǰ��������������ǵݹ飩
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

//����������������ǵݹ飩
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

//����������������ǵݹ飩
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
// �������������ݹ飩
void midorderTraverse(Node* T, int level) {
	if (T) {
		preorderTraverse(T->lNode, level + 1);
		// ���ֵ
		printf(INANDOUTFORMAT, T->val);
		printf(" level: %d\n", level);
		// �����
		preorderTraverse(T->rNode, level + 1);
	}
}
// �������������ݹ飩
void postorderTraverse(Node* T, int level) {
	if (T) {
		// ���Ҹ�
		preorderTraverse(T->lNode, level + 1);
		preorderTraverse(T->rNode, level + 1);
		// ���ֵ
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