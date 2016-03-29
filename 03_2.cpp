#include <cstdio>
#include <cstdlib>
#include <set>

using namespace std;

int count = 0;

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

int findRoot(char ch, char* arr, int len)
{
    int pos = -1;
    for(int i = 0; i < len; i++)
    {
        if(arr[i] == ch)
        {
            pos = i;
            break;
        }
    }
    return pos;
}

bool isEnd(set<pNode>& S, int total)
{
    if(S.size() == 0)
        return true;
    bool endFlag = true;
    for(set<pNode>::iterator itr = S.begin(); itr != S.end(); itr++)
    {
        if((*itr)->lchild != nullptr || (*itr)->rchild != nullptr)
            endFlag = false;
        else
        {
            count++;
            printf("%d", (*itr)->value);
            if(count < total)
                printf(" ");
        }
    }
    return endFlag;
}



int main()
{
    int N;
    scanf("%d", &N);
    char* left = (char*)malloc(N*sizeof(char));
    char* right = (char*)malloc(N*sizeof(char));
    pNode nodes = new Node[N];
    for(int i = 0; i < N; i++)
    {
        scanf("%c", left+i);
        scanf("%c", right+i);
        nodes[i].value = i;
    }

    //calculate number of leaf nodes
    int totalLeaves = 0;
    for(int i = 0; i < N; i++)
    {
        if(left[i] == right[i])
            totalLeaves++;
    }
    //find the root node
    int indexRoot;
    for(char i = '0'; i < '0'+ N; i++)
    {
        int lpos = findRoot(i, left, N);
        int rpos = findRoot(i, right, N);
        if(lpos == -1 && rpos == -1)
        {
            indexRoot = int(i - '0');
            break;
        }
    }
    biTree tree = nodes + indexRoot;
    //build tree
    for(int i = 0; i < N; i++)
    {
        if(left[i] != '-')
        {
            int l = int(left[i] - '0');
            nodes[i].lchild = nodes+l;
        }
        if(right[i] != '-')
        {
            int r = int(right[i] - '0');
            nodes[i].rchild = nodes+r;
        }
    }

    set<pNode> pre;
    set<pNode> temp;
    temp.insert(tree);
    while(!isEnd(temp, totalLeaves))
    {
        pre = temp;
        temp.clear();
        for(set<pNode>::iterator itr = pre.begin(); itr != pre.end(); itr++)
        {
            if((*itr)->lchild != nullptr)
                temp.insert((*itr)->lchild);
            if((*itr)->rchild != nullptr)
                temp.insert((*itr)->rchild);
        }
    }

    return 0;
}
