// Need Optimization
#include<cstdio>
//#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<map>
using namespace std;

char buffer[200];

typedef struct Node{
    Node(int f)
    {
        isLeaf = false;
        ch = '-';
        freq = f;
        lchild = nullptr;
        rchild = nullptr;
    }
    Node()
    {
        isLeaf = true;
        ch = '-';
        freq = 0;
        lchild = nullptr;
        rchild = nullptr;
    }
    bool isLeaf;
    char ch;
    int freq;
    string code;
    Node* lchild;
    Node* rchild;
}Node;

typedef struct Code{
    Code(char c, string s)
    {
        ch = c;
        code = s;
    }
    char ch;
    string code;
} Code;

bool cmpNode(Node* a, Node* b)
{
    return a->freq > b->freq;
}

bool cmpVector(const Code& a, const Code& b)
{
    return a.code.length() < b.code.length();
}

bool isPrefix(string& a, string& b)
{
    if(a.length() > b.length())
        return false;
    //len(a) <= len(b)
    for(unsigned int i = 0; i < a.length(); i++)
    {
        if(a[i] != b[i])
            return false;
    }
    return true;
}

bool isValidCoding(vector<Code>& vec)
{
    for(vector<Code>::iterator ia = vec.begin(); ia != vec.end(); ia++)
    {
        for(vector<Code>::iterator ib = ia; ib != vec.end(); ib++)
        {
            string a = (*ia).code, b = (*ib).code;
            if(ia != ib)
            {
                if(isPrefix(a, b))
                    return false;
            }
        }
    }
    return true;
}

void encode(Node* node, string code)
{
    if(node == nullptr)
        return;
    else
    {
        node->code = code;
        encode(node->lchild, code + "0");
        encode(node->rchild, code + "1");
    }
}

int calTotalBits(Node* node, map<char, int>& Map)
{
    if(node == nullptr)
        return 0;
    else
    {
        if(node->isLeaf == true)
        {
            return node->code.length() * Map[node->ch];
        }
        else
            return calTotalBits(node->lchild, Map) + calTotalBits(node->rchild, Map);
    }
}

int main()
{
    //get data
    int N;
    scanf("%d", &N);
    printf("N:%d\n", N);
    getchar();
    map<char, int> dict;
    Node** arr = new Node*[N];
    for(int i = 0; i < N; i++)
    {
        arr[i] = new Node();
        scanf("%c", &(arr[i]->ch));
        getchar();
        scanf("%d", &(arr[i]->freq));
        getchar();
        printf("char:%c\n", arr[i]->ch);
        printf("freq:%d\n", arr[i]->freq);
        dict[arr[i]->ch] = arr[i]->freq;
    }

    int totalBits;
    //build huffman tree, calculate the number of total bits
    Node* head = nullptr;
    for(int i = 0; i < N - 1; i++)
    {
        sort(arr, arr + N - i, cmpNode);
        Node* node = new Node(arr[N - i - 1]->freq + arr[N - i - 2]->freq);
        head = node;
        head->lchild = arr[N - i - 1];
        head->rchild = arr[N - i - 2];
        arr[N - i - 2] = head;
    }
    // encode
    encode(head, string(""));
    totalBits = calTotalBits(head, dict);

    //get test cases
    int nCases;
    scanf("%d", &nCases);
    getchar();
    printf("nCases:%d\n", nCases);
    for(int i = 0; i < nCases; i++)
    {
        vector<Code> vec;
        char c;
        string s;
        for(int j = 0; j < N; j++)
        {
            scanf("%c", &c);
            getchar();
            scanf("%s", buffer);
            getchar();
            s = string(buffer);
            Code tmp(c, s);
            vec.push_back(tmp);
        }

        //verify whether less or equal than the huffman number above and whether it's valid
        sort(vec.begin(), vec.end(), cmpVector);
        int nBits = 0;
        bool isValid = isValidCoding(vec);
        for(vector<Code>::iterator itr = vec.begin(); itr != vec.end(); itr++)
        {
            nBits += (*itr).code.length() * dict[(*itr).ch];
        }

        if(nBits <= totalBits && isValid)
            printf("Yes\n");
        else
            printf("No\n");
    }

    //delete
    delete[] arr;// fake
    return 0;
}
