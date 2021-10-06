#include <C++AllHeaderFiles.h>
#include <queue>
using namespace std;
#pragma warning(disable:6031)
#pragma warning(disable:4996)

#pragma warning(disable:6011)
#define INANDOUTFORMAT "%c"
typedef char ElemType;

int cnt = 0;
char input[100];
struct Node {
	ElemType val;
	struct Node* lNode, * rNode;
};
typedef struct Node Node;
struct ReturnType {
	bool isBalanced;
	int height;
};
typedef struct ReturnType ReturnType;
ReturnType* initReturnType(bool isB, int h) {
	ReturnType* ret = (ReturnType*)calloc(1, sizeof(ReturnType));
	ret->isBalanced = isB;
	ret->height = h;
	return ret;
}
bool isbalancedt(Node* h) {
	return isBalancedTree(h)->isBalanced;
}
ReturnType* isBalancedTree(Node* h) {
	if (h) {
		ReturnType* leftRet = isBalancedTree(h->lNode);
		ReturnType* rightRet = isBalancedTree(h->rNode);
		int height = max(leftRet->height, rightRet->height) + 1;
		bool isbalanced = leftRet->isBalanced && rightRet->isBalanced && (abs(leftRet->height - rightRet->height) < 2);
		return initReturnType(isbalanced, height);
	}
	else {
		return initReturnType(true, 0);
	}
}
bool checkBST(Node* H) {
	if (H == NULL) return true;
	stack<Node*> s;
	int lastNum = INT_MIN;
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
			if (H->val>lastNum)
			{
				lastNum = H->val;
			}
			else
			{
				return false;
			}
			H = H->rNode;
		}
	}
	return true;
}

//宽度优先遍历
void bfs(Node* h) {
	if (h == NULL) return;
	map<Node*, int> getlev;
	Node* cur = NULL;
	std::queue<Node*> q;
	q.push(h);
	getlev.insert(pair<Node*, int>(h, 1));
	int curlev = 1;
	int curlevsum = 0;
	int maxw = 0;
	while (!q.empty())
	{
		cur = q.front();
		int curnodelev = getlev.find(cur)->second;
		if (curnodelev == curlev) {// 还在当前层
			curlevsum++;//计数当前层
		}
		else
		{
			maxw = max(maxw, curlevsum);//不在当前层结算
			curlev++;//进入下一层
			curlevsum = 1;//记录此次节点
		}
		q.pop();
		cout << cur->val << endl;
		if (cur->lNode) {
			q.push(cur->lNode);
			getlev.insert(pair<Node*, int>(cur->lNode, curlev+1));
		}
		if (cur->rNode) {
			q.push(cur->rNode);
			getlev.insert(pair<Node*, int>(cur->rNode, curlev + 1));
		}
	}
	maxw = max(maxw, curlevsum);//树的宽度
	cout << endl << maxw << endl;
}

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
	auto a = checkBST(tree);
	cout << a << endl;
}