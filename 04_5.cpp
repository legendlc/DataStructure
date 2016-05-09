#include <iostream>
#define maxInt(a, b) ((a) > (b) ? (a) : (b))
using namespace std;

typedef struct Node{
	Node()
	{
		lchild = nullptr;
		rchild = nullptr;
		parent = nullptr;
		bFactor = 0;
	}
	Node* parent;
	Node* lchild;
	Node* rchild;
	int value;
	int bFactor; // left:+    right:-
} Node, *Tree;

void middleTraverse(Tree tree)
{
	if (tree == nullptr)
		return;
	else
	{
		middleTraverse(tree->lchild);
		cout << tree->value << " " << tree->bFactor << endl;
		middleTraverse(tree->rchild);
	}
}

inline bool compare(Node* a, Node* b)
{
	return a->value < b->value;
}

Tree insert(Tree tree, Node* node)
{
	Node* head = tree;
	// tree is null
	if (tree == nullptr)
		return node;
	// tree isn't null
	Node* last = nullptr;
	Node* tmp = tree;
	while (tmp != nullptr)
	{
		last = tmp;
		if (compare(node, tmp)) // node < tmp
		{
			(tmp->bFactor)++;
			tmp = tmp->lchild;
		}
		else
		{
			(tmp->bFactor)--;
			tmp = tmp->rchild;
		}
	}
	if (compare(node, last))
	{
		last->lchild = node;
		node->parent = last;
	}
	else
	{
		last->rchild = node;
		node->parent = last;
	}
	cout << "before\n"; middleTraverse(tree); cout << endl;
	//find first unbalanced tree
	tmp = node;
	Node* p = tmp->parent;
	Node* pp = p->parent;
	while (pp != nullptr)
	{
		if (pp->bFactor > 1 || pp->bFactor < -1)
		{
			//reconstruct
			if (tmp == p->lchild && p == pp->lchild)
			{
				// Right rotation
				if (pp->parent == nullptr)
				{	//head will change
					pp->parent = p;
					pp->lchild = p->rchild;
					p->rchild = pp;
					p->parent = nullptr;
					head = p;
					//change bFactor
					int x = tmp->bFactor;
					int y = p->bFactor;
					pp->bFactor = 0;
					p->bFactor = 0;
				}
				else
				{
					p->parent = pp->parent;
					if (pp == pp->parent->lchild)
						pp->parent->lchild = p;
					else
						pp->parent->rchild = p;
					pp->parent = p;
					pp->lchild = p->rchild;
					p->rchild = pp;
					//change bFactor
					pp->bFactor = 0;
					p->bFactor = 0;
					tmp = p;
					p = tmp->parent;
					while (p != nullptr)
					{
						if (tmp == p->lchild)
							p->bFactor--;
						else
							p->bFactor++;
						tmp = p;
						p = p->parent;
					}
				}
			}
			else if (tmp == p->rchild && p == pp->rchild)
			{
				// Left rotation
				if (pp->parent == nullptr)
				{	//head will change
					pp->parent = p;
					pp->rchild = p->lchild;
					p->lchild = pp;
					p->parent = nullptr;
					head = p;
					//change bFactor
					int x = tmp->bFactor;
					int y = p->bFactor;
					pp->bFactor = 0;
					p->bFactor = 0;
				}
				else
				{
					p->parent = pp->parent;
					if (pp == pp->parent->lchild)
						pp->parent->lchild = p;
					else
						pp->parent->rchild = p;
					pp->parent = p;
					pp->rchild = p->lchild;
					p->lchild = pp;
					//change bFactor
					int x = tmp->bFactor;
					pp->bFactor = 0;
					p->bFactor = 0;
					tmp = p;
					p = tmp->parent;
					while (p != nullptr)
					{
						if (tmp == p->lchild)
							p->bFactor--;
						else
							p->bFactor++;
						tmp = p;
						p = p->parent;
					}
				}
			}
			else if (tmp == p->lchild && p == pp->rchild)
			{
				//Right then left rotation
				if (pp->parent == nullptr)
				{	//change head
					head = tmp;
					Node* B = tmp->lchild;
					Node* C = tmp->rchild;
					int x = tmp->bFactor;
					tmp->parent = nullptr;
					tmp->lchild = pp;
					tmp->rchild = p;
					p->parent = tmp;
					p->lchild = C;
					pp->parent = tmp;
					pp->rchild = B;
					if (x >= 0)
					{
						p->bFactor = -1 * x;
						pp->bFactor = 0;
						tmp->bFactor = 0;
					}
					else
					{
						p->bFactor = 0;
						pp->bFactor = -1 * x;
						tmp->bFactor = 0;
					}
				}
				else
				{
					Node* B = tmp->lchild;
					Node* C = tmp->rchild;
					int x = tmp->bFactor;
					tmp->parent = pp->parent;
					if (pp == pp->parent->lchild)
						pp->parent->lchild = tmp;
					else
						pp->parent->rchild = tmp;
					tmp->rchild = p;
					tmp->lchild = pp;
					p->parent = tmp;
					p->lchild = C;
					pp->parent = tmp;
					pp->rchild = B;
					if (x >= 0)
					{
						p->bFactor = -1 * x;
						pp->bFactor = 0;
						tmp->bFactor = 0;
					}
					else
					{
						p->bFactor = 0;
						pp->bFactor = -1 * x;
						tmp->bFactor = 0;
					}
					p = tmp->parent;
					while (p != nullptr)
					{
						if (tmp == p->lchild)
							p->bFactor--;
						else
							p->bFactor++;
						tmp = p;
						p = p->parent;
					}
				}
			}
			else if (tmp == p->rchild && p == pp->lchild)
			{
				//Left then right rotation
				if (pp->parent == nullptr)
				{	//change head
					head = tmp;
					Node* B = tmp->lchild;
					Node* C = tmp->rchild;
					int x = tmp->bFactor;
					tmp->parent = nullptr;
					tmp->lchild = p;
					tmp->rchild = pp;
					p->parent = tmp;
					p->rchild = B;
					pp->parent = tmp;
					pp->lchild = C;
					if (x >= 0)
					{
						p->bFactor = 0;
						pp->bFactor = -1 * x;
						tmp->bFactor = 0;
					}
					else
					{
						pp->bFactor = 0;
						p->bFactor = -1 * x;
						tmp->bFactor = 0;
					}
				}
				else
				{
					Node* B = tmp->lchild;
					Node* C = tmp->rchild;
					int x = tmp->bFactor;
					tmp->parent = pp->parent;
					if (pp == pp->parent->lchild)
						pp->parent->lchild = tmp;
					else
						pp->parent->rchild = tmp;
					tmp->lchild = p;
					tmp->rchild = pp;
					p->parent = tmp;
					p->rchild = B;
					pp->parent = tmp;
					pp->lchild = C;
					if (x >= 0)
					{
						p->bFactor = 0;
						pp->bFactor = -1 * x;
						tmp->bFactor = 0;
					}
					else
					{
						pp->bFactor = 0;
						p->bFactor = -1 * x;
						tmp->bFactor = 0;
					}
					p = tmp->parent;
					while (p != nullptr)
					{
						if (tmp == p->lchild)
							p->bFactor--;
						else
							p->bFactor++;
						tmp = p;
						p = p->parent;
					}
				}
			}
			break;
		}
		else
		{
			tmp = p;
			p = pp;
			pp = pp->parent;
		}
	}
	return head;
}

int main()
{
	int N;
	cin >> N;
	Tree tree = nullptr;
	for (int i = 0; i < N; i++)
	{
		int v;
		cin >> v;
		Node* node = new Node;
		node->value = v;
		tree = insert(tree, node);
		middleTraverse(tree); cout << endl;
	}
	cout << tree->value;

	return 0;
}
