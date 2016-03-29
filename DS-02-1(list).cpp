#include <cstdio>

typedef int elemType;

typedef struct Node{
    Node(){
        last = nullptr;
        next = nullptr;
    }
    Node(const Node& n)
    {
        this->value = n.value;
        this->power = n.power;
        last = nullptr;
        next = nullptr;
    }
    Node(int v, int p)
    {
        value = v;
        power = p;
        last = nullptr;
        next = nullptr;
    }
    int power;
    elemType value;
    Node* last;
    Node* next;
} node, *pNode, *List;

void deleteNode(List L, pNode node)
{
    pNode tmp = L;
    while(tmp != nullptr)
    {
        if(tmp == node)
        {
            (tmp->last)->next = tmp->next;
            (tmp->next)->last = tmp->last;
            delete tmp;
            return;
        }
        tmp = tmp->next;
    }
}

List insertList(List l, pNode p)
{
    if(p == nullptr)
        return l;
    if(l == nullptr)
    {
        return p;
    }
    // l != nullptr and p != nullptr
    pNode tmp = l;
    pNode pre = nullptr;
    while(tmp != nullptr && p->power < tmp->power)
    {
        pre = tmp;
        tmp = tmp->next;
    }
    // tmp == nullptr or p->power >= tmp->power
    if(pre == nullptr)  //p->power is the largest
    {
        if(p->power == tmp->power)
        {
            tmp->value += p->value;
            delete p;
        }
        else
        {
            p->next = l;
            l->last = p;
            return p;
        }
    }
    else    //pre != nullptr
    {
        if(tmp == nullptr)  //p->value is the smallest
        {
            pre->next = p;
            p->last = pre;
        }
        else    //tmp != nullptr
        {
            if(p->power == tmp->power)
            {
                tmp->value += p->value;
                delete p;
            }
            else // pre->power > p->power > tmp->power
            {
                pre->next = p;
                p->next = tmp;
                p->last = pre;
                tmp->last = p;
            }
        }
    }
    return l;
}

void displayList(List L)
{
    if(L == nullptr)
    {
        printf("0 0\n");
        return;
    }
    pNode tmp = L;
    while(tmp != nullptr)
    {
        printf("%d %d", tmp->value, tmp->power);
        if(tmp->next != nullptr)
            printf(" ");
        tmp = tmp->next;
    }
    printf("\n");
}

List deleteZero(List L)
{
    pNode tmp = L;
    List head = L;
    while(head != nullptr && head->value == 0)
    {
        tmp = head;
        head = head->next;
        if(head != nullptr)
            head->last = nullptr;
        delete tmp;
    }
    tmp = head;
    while(tmp != nullptr)
    {
        if(tmp->value == 0)
        {
            if(tmp->next == nullptr)
            {
                tmp->last->next = tmp->next;
                pNode _tmp = tmp;
                tmp = tmp->next;
                delete _tmp;
            }
            else
            {
                tmp->last->next = tmp->next;
                tmp->next->last = tmp->last;
                pNode _tmp = tmp;
                tmp = tmp->next;
                delete _tmp;
            }
        }
        else
        {
            tmp = tmp->next;
        }
        //displayList(tmp);
    }
    return head;
}

void deleteList(List L)
{
    if(L == nullptr)
        return;
    deleteList(L->next);
    delete L;
}

List addLists(List a, List b)
{
    List result = nullptr;
    pNode tmp = a;
    while(tmp != nullptr)
    {
        pNode newNode = new Node(*tmp);
        result = insertList(result, newNode);
        tmp = tmp->next;
    }
    tmp = b;
    while(tmp != nullptr)
    {
        pNode newNode = new Node(*tmp);
        result = insertList(result, newNode);
        tmp = tmp->next;
    }
    return result;
}

List multiplyLists(List a, List b)
{
    List result = nullptr;
    for(pNode node1 = a; node1 != nullptr; node1 = node1->next)
    {
        for(pNode node2 = b; node2 != nullptr; node2 = node2->next)
        {
            pNode newNode = new Node(node1->value * node2->value, node1->power + node2->power);
            result = insertList(result, newNode);
        }
    }
    return result;
}

int main()
{
    int m, n;
    List a = nullptr, b = nullptr;
    //get list a and b
    scanf("%d", &m);
    if(m == 0)
        scanf("%d", &m);
    for(int i = 0; i < m; i++)
    {
        pNode newNode = new node;
        scanf("%d%d", &(newNode->value), &(newNode->power));
        a = insertList(a, newNode);
    }
    scanf("%d", &n);
    if(n == 0)
        scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        pNode newNode = new node;
        scanf("%d%d", &(newNode->value), &(newNode->power));
        b = insertList(b, newNode);
    }

    List sum, product;
    sum = addLists(a, b);
    sum = deleteZero(sum);
    product = multiplyLists(a, b);
    product = deleteZero(product);

    //displayList(a);
    //displayList(b);
    displayList(product);
    displayList(sum);

    deleteList(a);
    deleteList(b);
    deleteList(sum);
    deleteList(product);
    return 0;
}
