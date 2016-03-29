#include <cstdio>

typedef int ET;
typedef struct Node{
    Node()
    {
        lchild = nullptr;
        rchild = nullptr;
    }
    Node(ET v)
    {
        value = v;
        lchild = nullptr;
        rchild = nullptr;
    }
    ET value;
    struct Node* lchild;
    struct Node* rchild;
} Node, *pNode, *biTree;

int whichNode(pNode node)
{
    if(node == nullptr)
        return -1;
    if(node->lchild == nullptr && node->rchild == nullptr)
        return 0;
    if(node->lchild == nullptr)
        return 1;
    if(node->rchild == nullptr)
        return 2;
    else
        return 3;
}

void insertNode(biTree tree, pNode node)
{
    pNode pre = nullptr;
    pNode temp = tree;
    while(temp != nullptr)
    {
        if(node->value < temp->value)
        {
            pre = temp;
            temp = temp->lchild;
        }
        else
        {
            pre = temp;
            temp = temp->rchild;
        }
    }
    if(node->value < pre->value)
        pre->lchild = node;
    else
        pre->rchild = node;
}

biTree buildTree(int N)
{
    ET tmp;
    scanf("%d", &tmp);
    biTree tree = new Node(tmp);
    for(int i = 1; i < N; i++)
    {
        scanf("%d", &tmp);
        pNode node = new Node(tmp);
        insertNode(tree, node);
    }
    return tree;
}

bool isSameTree(biTree a, biTree b)
{
    int ka = whichNode(a), kb = whichNode(b);
    if(ka != kb)
        return false;
    if(ka == -1)
        return true;
    if(a->value != b->value)
        return false;
    return (isSameTree(a->lchild, b->lchild)) && (isSameTree(a->rchild, b->rchild));
}

int main()
{
    int N, nTests;
    scanf("%d", &N);
    while(N > 0)
    {
        scanf("%d", &nTests);
        //get tree data
        biTree standard = buildTree(N);
        for(int i = 0; i < nTests; i++)
        {
            biTree testCase = buildTree(N);
            printf(isSameTree(standard, testCase) ? "Yes\n" : "No\n");
        }
        scanf("%d", &N);
    }
    return 0;
}
