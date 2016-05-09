#include <iostream>

using namespace std;

typedef struct {
	char value;
	char lchild;
	char rchild;
	char parent;
} Node;

void fillParent(Node* tree, int num)
{
	for (int i = 0; i < num; i++)
	{
		tree[i].parent = '-';
	}
	for (int i = 0; i < num; i++)
	{
		if (tree[i].lchild != '-')
		{
			int indexL = tree[i].lchild - '0';
			tree[indexL].parent = tree[i].value;
		}
		if (tree[i].rchild != '-')
		{
			int indexR = tree[i].rchild - '0';
			tree[indexR].parent = tree[i].value;
		}
	}
}

bool compareTree(Node* t1, Node* t2, int num)
{
	bool flag = true;
	for (int i = 0; i < num; i++)
	{
		bool flag2 = false;
		Node& tmp1 = t1[i];
		char v1 = tmp1.value;
		char p1 = tmp1.parent;
		for (int j = 0; j < num; j++)
		{	

			Node& tmp2 = t2[j];
			char v2 = tmp2.value;
			char p2 = tmp2.parent;
			if (v2 == v1)
			{
				if (p2 == p1)
					flag2 = true;
			}
		}
		if (flag2 == false)
			return false;
	}
	return true;
}

int main()
{
	int n1, n2;
	cin >> n1;
	Node* tree1 = new Node[n1];
	for (int i = 0; i < n1; i++)
	{
		Node& tmp = tree1[i];
		cin >> tmp.value >> tmp.lchild >> tmp.rchild;
	}
	fillParent(tree1, n1);

	cin >> n2;
	Node* tree2 = new Node[n2];
	for (int i = 0; i < n2; i++)
	{
		Node& tmp = tree2[i];
		cin >> tmp.value >> tmp.lchild >> tmp.rchild;
	}
	fillParent(tree2, n2);

	if (n1 != n2)
		cout << "No";
	else
	{
		if (compareTree(tree1, tree2, n1) == true)
			cout << "Yes";
		else
			cout << "No";
	}

	delete[] tree1;
	delete[] tree2;
	return 0;
}
