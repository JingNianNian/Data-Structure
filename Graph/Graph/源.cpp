#include <C++AllHeaderFiles.h>
#define MAXN 100010
#pragma warning(disable:4996)
#define foreach(item, collection) for(auto (item) = (collection).begin(); (item) != (collection).end(); (item)++)
#define foreach_array_from0(_item,_array,_size) for(int i = 0, (_item) = (_array)[i]; i < (_size); i++)
#define foreach_array_from_index(_item,_array,_index,_size) for(int i = (_index), (_item) = (_array)[i]; i < (_size); i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = (int)1e5 + 10;
typedef int ElemType;
class Edge;

class Node {
public:
	ElemType val;
	int in;
	int out;
	vector<Edge*>* edges;
	vector<Node*>* nexts;
	Node(ElemType v) {
		val = v;
		in = 0;
		out = 0;
		edges = new vector<Edge*>;
		nexts = new vector<Node*>;
	};
	~Node() {
		delete edges;
		delete nexts;
	}
};
class Edge {
public:
	int weight;
	Node* from;
	Node* to;
	Edge(int _wei, Node* _from, Node* _to) {
		weight = _wei;
		from = _from;
		to = _to;
	};
};
class Graph {
public:
	map<int, Node*>* nodes;
	set<Edge*>* edges;
	vector<Node*>* nodesToVector() {
		auto v = new vector<Node*>;
		foreach(itr, *nodes) {
			(*v).push_back((*itr).second);
		}
		return v;
	}
	Graph()
	{
		edges = new set<Edge*>;
		nodes = new map<int, Node*>;
	};
	~Graph() {
		delete nodes;
		delete edges;
	}
};
class MySet {
public:
	map<Node*, vector<Node*>*>* mp;
	bool isSameSet(Node* from, Node* to) {
		return (*mp)[from] == (*mp)[to];
	};
	void combine(Node* from, Node* to) {
		auto fromSet = (*mp)[from];
		auto toSet = (*mp)[to];
		foreach(toNode, (*toSet)) {
			(*fromSet).push_back(*toNode);
			(*mp)[*toNode] = fromSet;
		}
	};
	MySet(vector<Node*>* nodeList) {
		mp = new map<Node*, vector<Node*>*>;
		foreach(i, *nodeList) {
			auto t = new vector<Node*>;
			(*t).push_back(*i);
			(*mp)[*i] = t;
		}
	}
	~MySet() {
		delete mp;
	}
};
struct MyCmp {
	bool operator()(const void* x, const void* y) {
		return (*((Edge*)x)).weight > (*((Edge*)y)).weight;
	}
};

Graph* test() {
	auto a = new Node(1);
	auto b = new Node(2);
	auto obj = new Graph();
	obj->edges->insert(new Edge(1, a, b));
	obj->nodes->insert(pair<int, Node*>(1, a));
	obj->nodes->insert(pair<int, Node*>(2, b));
	return obj;
}





map<Node*, int>* dijkstral(Node node) {
	return NULL;
}

set<Edge*>* kruskalMST(Graph graph) {
	auto res = new set<Edge*>;// ���صĽ��
	auto myset = new MySet(graph.nodesToVector()); // ģ�Ⲣ�鼯һЩ����
	auto p = new priority_queue<Edge*, vector<Edge*>, MyCmp>;// С����

	foreach(itr, *graph.edges) {
		p->push(*itr);// �����б߷���С���ѣ���������
	}
	
	while (!p->empty())
	{
		auto curEdge = p->top();
		p->pop();//ÿ��ȡ����̱ߣ��������㲻��һ�������ڣ��ϲ����ϲ���д���Ӧ�ļ��ϣ�����һ���������������л�
		if (!myset->isSameSet((*curEdge).from, (*curEdge).to)) {
			res->insert(curEdge);
			myset->combine((*curEdge).from, (*curEdge).to);
		}
	}
	delete myset;
	delete p;
	return res;
}

set<Edge*>* primMST(Graph* g) {// ��������ͼ�����ܳ���ĳ����Ȩֵ֮��Ϊ����
	auto minEdges = new priority_queue<Edge*, vector<Edge*>, MyCmp>;// ��С��
	auto res = new set<Edge*>;// ���صĽ��
	auto selectedNodes = new set<Node*>;// �Ѿ�������ĵ�
	foreach(itr, *(g->nodes)) {// ��ֹ����ͨͼ
		if (selectedNodes->find((*itr).second) == selectedNodes->end()) {// ��δ����
			auto curNode = (*itr).second;
			selectedNodes->insert(curNode);// ���봦����ĵ�

			foreach(edg, *(*curNode).edges) {
				minEdges->push(*edg);//�����õ�����б�
			}

			while (!minEdges->empty())
			{
				auto selectedEdge = minEdges->top();// ѡ����С��
				minEdges->pop();
				auto nextNode = (*selectedEdge).to;// ��С��ָ��ĵ�
				if (selectedNodes->find(nextNode) == selectedNodes->end())// ���õ�δ������
				{
					selectedNodes->insert(nextNode);// ���봦����ĵ�
					res->insert(selectedEdge);// ���߼����
					foreach(nextEdge, *(*nextNode).edges) {
						minEdges->push(*nextEdge);//�����õ�����б�
					}
				}
			}
		}
	}
	delete minEdges;
	delete selectedNodes;
	return res;
}

vector<Node*>* topologicalSort(Graph* g) {
	vector<Node*>* ret = new vector<Node*>;
	queue<Node*>* q = new queue<Node*>;
	map<Node*, int>* mp = new map<Node*, int>;
	foreach(i, *(g->nodes))
	{
		mp->insert(pair<Node*, int>((*i).second, (*i).second->in));
		if (!(*i).second->in) {
			q->push((*i).second);
		}
	}
	while (!q->empty())
	{
		auto cur = q->front();
		q->pop();
		ret->push_back(cur);
		for (auto i = (*cur).nexts->begin(); i != (*cur).nexts->end(); i++)
		{
			(*mp)[*i]--;
			if (!(*mp)[*i]) {
				q->push(*i);
			}
		}
	}
	return ret;
}

Graph* createGraph(int** gra, int edgesnum) {
	Graph* graph = new Graph();
	for (int i = 0; i < edgesnum; i++)
	{
		int wei = gra[i][0];
		int from = gra[i][1];
		int to = gra[i][2];
		if (graph->nodes->find(from) == graph->nodes->end())
		{
			graph->nodes->insert(pair<int, Node*>(from, new Node(from)));
		}
		if (graph->nodes->find(to) == graph->nodes->end())
		{
			graph->nodes->insert(pair<int, Node*>(to, new Node(to)));
		}
		Node* fromNode = graph->nodes->find(from)->second;
		Node* toNode = graph->nodes->find(to)->second;
		Edge* newEdge = new Edge(wei, fromNode, toNode);
		fromNode->nexts->push_back(toNode);
		fromNode->out++;
		toNode->in++;
		fromNode->edges->push_back(newEdge);
		graph->edges->insert(newEdge);
	}
	return graph;
}

int main() {
	int** a = (int**)calloc(3, sizeof(int*));
	for (int i = 0; i < 3; i++)
	{
		a[i] = (int*)calloc(3, sizeof(int));
	}
	a[0][0] = 5;
	a[0][1] = 0;
	a[0][2] = 1;
	a[1][0] = 3;
	a[1][1] = 0;
	a[1][2] = 2;
	a[2][0] = 7;
	a[2][1] = 1;
	a[2][2] = 2;
	Graph* gra = createGraph(a, 3);
	auto res = primMST(gra);
	/*int q = 10;
	int** a = (int**)calloc(3, sizeof(int*));
	for (int i = 0; i < 3; i++)
	{
		a[i] = (int*)calloc(3, sizeof(int));
	}
	a[0][0] = 5;
	a[0][1] = 0;
	a[0][2] = 1;
	a[1][0] = 3;
	a[1][1] = 0;
	a[1][2] = 2;
	a[2][0] = 7;
	a[2][1] = 1;
	a[2][2] = 2;
	Graph gra = createGraph(a, 3);
	auto b = topologicalSort(gra);
	auto c = kruskalMST(gra);
	return 0;*/
}