#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef struct{
    int Size;
    int parent;
} Data;

int findRoot(Data* arr, int index)
{
    int pos = index;
    while(arr[pos].parent != -1)
    {
        pos = arr[pos].parent;
    }
    return pos;
}

int findSeperatedNets(Data* arr, int num)
{

    int count = 0;
    for(int i = 1; i <= num; i++)
    {
        if(arr[i].parent == -1)
            count++;
    }
    return count;
}

int main()
{
    int N;
    scanf("%d", &N);
    getchar();
    Data* arr = (Data*)malloc((N + 1) * sizeof(Data));
    for(int i = 1; i <= N; i++)
    {
        arr[i].Size = 1;
        arr[i].parent = -1;
    }
    char op;
    scanf("%c", &op);
    while(op != 'S')
    {
        if(op == 'I')
        {
            int a, b;
            scanf("%d%d", &a, &b);
            getchar();
            int rootA = findRoot(arr, a);
            int rootB = findRoot(arr, b);
            if(arr[rootA].Size > arr[rootB].Size)
            {
                arr[rootB].parent = a;
                arr[rootA].Size++;
            }
            else
            {
                arr[rootA].parent = b;
                arr[rootB].Size++;
            }
        }
        else if(op == 'C')
        {
            int a, b;
            scanf("%d%d", &a, &b);
            getchar();
            if(findRoot(arr, a) == findRoot(arr, b))
                printf("yes\n");
            else
                printf("no\n");
        }
        scanf("%c", &op);
    }

    int nNets = findSeperatedNets(arr, N);
    if(nNets == 1)
        printf("The network is connected.");
    else
        printf("There are %d components.", nNets);

    free(arr);
    return 0;
}
