#include <C++AllHeaderFiles.h>
#define MAXN 100010
#pragma warning(disable:4996)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 10;

class TrieNode {
public:
	char parentChar;
	int pass;
	int end;
	map<char, TrieNode*>* nextmp;
	set<TrieNode*>* del;
	TrieNode()
	{
		parentChar = '\0';
		pass = 0;
		end = 0;
		nextmp = new map<char, TrieNode*>;
		del = new set<TrieNode*>;
	}
	TrieNode(char a):parentChar(a)
	{
		pass = 0;
		end = 0;
		nextmp = new map<char, TrieNode*>;
	}

	int insertStr(const char* insertStr) {
		try
		{
			if (strcmp(insertStr, "") == 0) {
				return 1;
			}
			auto curNode = this;
			for (int i = 0; i < strlen(insertStr); i++) {
				curNode->pass++;
				if (curNode->nextmp->find(insertStr[i]) == curNode->nextmp->end()) {
					auto newnode = new TrieNode(insertStr[i]);
					curNode->nextmp->insert(pair<char, TrieNode*>(insertStr[i], newnode));
					del->insert(newnode);
				}
				curNode = (*curNode->nextmp)[insertStr[i]];
			}
			curNode->pass++;
			curNode->end++;
			return 1;
		}
		catch (const std::exception& e)
		{
			cout << e.what() << endl;
			return 0;
		}
	}



	bool deleteStr(const char* deleteStr, int num) {
		stack<TrieNode*>* s = new stack<TrieNode*>;
		try
		{
			if (strcmp(deleteStr, "") == 0) {
				delete s;
				return 1;
			}
			auto curNode = this;
			for (int i = 0; i < strlen(deleteStr); i++)
			{
				s->push(curNode);
				if (curNode->nextmp->find(deleteStr[i]) == curNode->nextmp->end()) {
					throw new exception("Not Found This Str !");
				}
				curNode = (*curNode->nextmp)[deleteStr[i]];
			}
			s->push(curNode);
			if (s->top()->end < num) {
				throw new exception("Parameter 'num' is incorrect!");
			}
			s->top()->end -= num;
			while (s->top() != this)
			{
				auto now = s->top();
				s->pop();
				now->pass -= num;
				if (now->pass == 0) {
					s->top()->nextmp->erase(now->parentChar);
					this->del->erase(now);
					delete now;
				}
			}
			this->pass -= num;
			delete s;
			return 1;
		}
		catch (const std::exception& e)
		{
			cout << e.what() << endl;
			delete s;
			return 0;
		}
	}

	int prefixNumber(const char* preStr) {
		try
		{
			auto curNode = this;
			for (int i = 0; i < strlen(preStr); i++)
			{
				if (curNode->nextmp->find(preStr[i]) == curNode->nextmp->end()) {
					throw new exception("Not Found This Str !");
				}
				curNode = (*curNode->nextmp)[preStr[i]];
			}
			return curNode->pass;
		}
		catch (const std::exception& e)
		{
			cout << e.what() << endl;
			return 0;
		}
	}

	int searchStr(const char* searchStr) {
		try
		{
			auto curNode = this;
			for (int i = 0; i < strlen(searchStr); i++)
			{
				if (curNode->nextmp->find(searchStr[i]) == curNode->nextmp->end()) {
					throw new exception("Not Found This Str !");
				}
				curNode = (*curNode->nextmp)[searchStr[i]];
			}
			return curNode->end;
		}
		catch (const std::exception& e)
		{
			cout << e.what() << endl;
			return 0;
		}
	}
	~TrieNode()
	{
		/*auto q = new queue<TrieNode*>;
		auto s = new stack<TrieNode*>;
		q->push(this);
		while (!q->empty()) {
			s->push(q->front());
			q->pop();
			for (auto i = s->top()->nextmp->begin(); i != s->top()->nextmp->end(); i++)
			{
				q->push(i->second);
			}
		}
		while (s->top() != this)
		{
			delete s->top();
			s->pop();
		}
		s->pop();
		delete q;
		delete s;*/
		for (auto i = del->begin(); i != del->end(); i++)
		{
			delete* i;
		}
		delete this->nextmp;
	}
};

void test() {
	int num = 0x3f3f;
	while (num--)
	{
		auto trie = new TrieNode;
		trie->insertStr("abc");
		trie->insertStr("abd");
		trie->insertStr("abe");
		trie->insertStr("abe");
		cout << trie->searchStr("abe") << endl;
		trie->deleteStr("abe", 2);
		delete trie;
	}
}
int main() {
	test();
	return 0;
}
