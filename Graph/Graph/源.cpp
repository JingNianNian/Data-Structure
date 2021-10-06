#include <C++AllHeaderFiles.h>
#define MAXN 100010
#pragma warning(disable:4996)

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
	vector<Edge*> edges;
	vector<Node*> nexts;
	Node(ElemType v) {
		val = v;
		in = 0;
		out = 0;
		edges = {};
		nexts = {};
	};
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
	map<int, Node*> nodes;
	set<Edge*> edges;
	Graph()
	{
		edges = {};
		nodes = {};
	};
};

vector<Node*> topologicalSort(Graph g) {
	vector<Node*> ret;
	queue<Node*> q;
	map<Node*, int> mp;
	for (auto i = g.nodes.begin(); i != g.nodes.end(); i++)
	{
		mp[(*i).second] = (*i).second->in;
		if (!(*i).second->in) {
			q.push((*i).second);
		}
	}
	while (!q.empty())
	{
		auto cur = q.front();
		q.pop();
		ret.push_back(cur);
		for (auto i = (*cur).nexts.begin(); i != (*cur).nexts.end(); i++)
		{
			mp[*i]--;
			if (!mp[*i]) {
				q.push(*i);
			}
		}
	}
	return ret;
}

Graph createGraph(int** gra, int edgesnum) {
	auto graph = Graph();
	for (int i = 0; i < edgesnum; i++)
	{
		int wei = gra[i][0];
		int from = gra[i][1];
		int to = gra[i][2];
		if (graph.nodes.find(from) == graph.nodes.end())
		{
			graph.nodes.insert(pair<int, Node*>(from, new Node(from)));
		}
		if (graph.nodes.find(to) == graph.nodes.end())
		{
			graph.nodes.insert(pair<int, Node*>(to, new Node(from)));
		}
		Node* fromNode = graph.nodes[from];
		Node* toNode = graph.nodes[to];
		Edge newEdge = Edge(wei, fromNode, toNode);
		fromNode->nexts.push_back(toNode);
		fromNode->out++;
		toNode->in++;
		fromNode->edges.push_back(&newEdge);
		graph.edges.insert(&newEdge);
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
	Graph gra = createGraph(a, 3);
	auto b = topologicalSort(gra);
	return 0;
}
