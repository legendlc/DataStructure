#include <cstdio>
#include <cstdlib>
#include <set>

using namespace std;

int leafCount = 0;

typedef int ET;
typedef struct Node {
	Node()
	{
		level = -1;
		parent = nullptr;
		lchild = nullptr;
		rchild = nullptr;
	}
	Node(ET v)
	{
		value = v;
		level = -1;
		parent = nullptr;
		lchild = nullptr;
		rchild = nullptr;
	}
	ET value;
	int level;
	struct Node* parent;
	struct Node* lchild;
	struct Node* rchild;
} Node, *pNode, *biTree;

int findRoot(char ch, char* arr, int len)
{
	int pos = -1;
	for (int i = 0; i < len; i++)
	{
		if (arr[i] == ch)
		{
			pos = i;
			break;
		}
	}
	return pos;
}

void setLevel(pNode node, int lv)
{
	node->level = lv;
	if (node->lchild != nullptr)
		setLevel(node->lchild, lv + 1);
	if (node->rchild != nullptr)
		setLevel(node->rchild, lv + 1);
}

void printLevel(biTree tree, int lv, int total)
{
	if (tree == nullptr)
		return;
	if (tree->level < lv)
	{
		printLevel(tree->lchild, lv, total);
		printLevel(tree->rchild, lv, total);
	}
	else if (tree->lchild == nullptr && tree->rchild == nullptr)
	{
		printf("%d", tree->value);
		leafCount++;
		if (leafCount < total)
			printf(" ");
	}
}

int main()
{
	int N;
	scanf("%d", &N);
	getchar();
	char* left = (char*)malloc(N*sizeof(char));
	char* right = (char*)malloc(N*sizeof(char));
	pNode nodes = new Node[N];
	for (int i = 0; i < N; i++)
	{
		scanf("%c", left + i);
		getchar();
		scanf("%c", right + i);
		getchar();
		nodes[i].value = i;
	}

	//calculate number of leaf nodes
	int totalLeaves = 0;
	for (int i = 0; i < N; i++)
	{
		if (left[i] == right[i])
			totalLeaves++;
	}
	//find the root node
	int indexRoot;
	for (char i = '0'; i < '0' + N; i++)
	{
		int lpos = findRoot(i, left, N);
		int rpos = findRoot(i, right, N);
		if (lpos == -1 && rpos == -1)
		{
			indexRoot = int(i - '0');
			break;
		}
	}
	biTree tree = nodes + indexRoot;

	//build tree
	for (int i = 0; i < N; i++)
	{
		if (left[i] != '-')
		{
			int l = int(left[i] - '0');
			nodes[i].lchild = nodes + l;
			nodes[l].parent = nodes + i;
		}
		if (right[i] != '-')
		{
			int r = int(right[i] - '0');
			nodes[i].rchild = nodes + r;
			nodes[r].parent = nodes + i;
		}
	}
	//get node level
	setLevel(tree, 0);

	//
	for (int i = 0; i < 11; i++)
	{
		printLevel(tree, i, totalLeaves);
	}

	return 0;
}
