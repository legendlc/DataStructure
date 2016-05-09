#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

enum COLOR{
    white = -1,
    grey,
    black
};

typedef int Value;

typedef struct{
    COLOR color;
    Value value;
} Vertex;

int BFS(Vertex* vertexs, int nVertexs, int* edges, vector<int>& vec, int depth)
{
    int count = 1;
    for(int i1 = 0; i1 < depth; i1++)
    {
        //add all connected node which haven't been visited before into vector
        vector<int> backup(vec);
        for(vector<int>::iterator itr = backup.begin(); itr != backup.end(); itr++)
        {
            int n = *itr;
            for(int i = 0; i < nVertexs; i++)
            {
                if(edges[n * nVertexs + i] > 0 && vertexs[i].color == white)
                {
                    vertexs[i].color = grey;
                    vec.push_back(i);
                }
            }
            vec.erase(find(vec.begin(), vec.end(), n));
            vertexs[n].color = black;
        }
        count += vec.size();
    }
    return count;
}

int main()
{
    int nVertexs, nEdges;
    scanf("%d%d", &nVertexs, &nEdges);
    Vertex* vertexs = new Vertex[nVertexs];

    //initialize n vertexs
    for(int i = 0; i < nVertexs; i++)
    {
        vertexs[i].color = white;
        vertexs[i].value = i+1;
    }

    //use adjacency matrix to store edges
    int* edges = new int[nVertexs * nVertexs];
    memset(edges, 0, nVertexs * nVertexs * sizeof(int));
    for(int i = 0; i < nEdges; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        edges[(a - 1) * nVertexs + b - 1] = 1;
        edges[(b - 1) * nVertexs + a - 1] = 1;
    }
/*
    for(int i = 0; i < nVertexs; i++)
    {
        for(int j = 0; j < nVertexs; j++)
        {
            printf("%d ", edges[i * (nVertexs) + j]);
        }
        printf("\n");
    }
*/

    for(int i = 0; i < nVertexs; i++)
    {
        vector<int> todo;
        vertexs[i].color = grey;
        todo.push_back(i);
        printf("%d: %.2f%\n", vertexs[i].value, BFS(vertexs, nVertexs, edges, todo, 6) * 100.0 / nVertexs);
        for(int j = 0; j < nVertexs; j++)
        {
            vertexs[j].color = white;
        }
    }

    delete[] vertexs;
    delete[] edges;
    return 0;
}
