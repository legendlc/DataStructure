#include <iostream>
#include <stack>
#include <cstring>
using namespace std;

int countAll = 0;

typedef struct Node{
	Node()
	{
		lchild = nullptr;
		rchild = nullptr;
		inStack = true;
	}
	Node* lchild;
	Node* rchild;
	int value;
	bool inStack;
} Node, *Tree;

Tree addToTree(Tree t, Node* node)
{
	if (t->inStack)
		t->lchild = node;
	else
		t->rchild = node;
	return t;
}

void postTraverse(Tree tree, int N)
{
	if (tree == nullptr)
		return;
	else
	{
		postTraverse(tree->lchild, N);
		postTraverse(tree->rchild, N);
		cout << tree->value;
		if ((++countAll) < N)
			cout << " ";
	}
}

int main()
{
	int N, count = 0;
	char buf[10];
	int v;
	cin >> N;
	stack<Node*> stackNode;
	//build tree
	Tree tree = nullptr;
	cin >> buf;
	cin >> v;
	Node* node = new Node;
	node->value = v;
	tree = node;
	stackNode.push(tree); //push head
	Node* isVisiting = stackNode.top();
	while (count < N)
	{
		cin >> buf;
		if (strcmp(buf, "Push") == 0)
		{
			cin >> v;
			node = new Node;
			node->value = v;
			addToTree(isVisiting, node);
			isVisiting = node;
			stackNode.push(node);
		}
		else if (strcmp(buf, "Pop") == 0)
		{
			isVisiting = stackNode.top();
			isVisiting->inStack = false;
			count++;
			stackNode.pop();
		}
	}

	postTraverse(tree, N);
	return 0;
}
