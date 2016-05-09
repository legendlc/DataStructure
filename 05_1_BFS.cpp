#include <iostream>
#include <cstring>
#include <stack>
#include <queue>
using namespace std;

enum COLOR{
    white = -1,
    grey,
    black
};

typedef struct{
    COLOR color;
    int value;
} Vertex;

void BFS(Vertex* vertexs, int nVertexs, int* edges, queue<int>& s)
{
    while(!s.empty())
    {
        int n = s.front();
        for(int i = 0; i < nVertexs; i++)
        {
            if(edges[n * nVertexs + i] > 0 && vertexs[i].color == white)
            {
                vertexs[i].color = grey;
                cout << i << " ";
                s.push(i);
            }
        }
        s.pop();
        vertexs[n].color = black;
        //cout << endl << s.size() << endl;
    }
}

int main()
{
    int nVertexs;
    cin >> nVertexs;
    Vertex* vertexs = new Vertex[nVertexs];
    int* edges = new int[nVertexs * nVertexs];
    memset(edges, 0, nVertexs * nVertexs * sizeof(int));
    //initialize vertexs
    for(int i = 0; i < nVertexs; i++)
    {
        vertexs[i].color = white;
        vertexs[i].value = i;
    }
    //use adjacency matrix to store edges
    int nEdges;
    cin >> nEdges;
    for(int i = 0; i < nEdges; i++)
    {
        int a, b;
        cin >> a >> b;
        edges[a * nVertexs + b] = 1;
        edges[b * nVertexs + a] = 1;
    }

    //begin bfs
    for(int i = 0; i < nVertexs; i++)
    {
        queue<int> todo;
        if(vertexs[i].color == white)
        {
            cout << "{ ";
            vertexs[i].color = grey;
            todo.push(i);
            cout << i << " ";
            BFS(vertexs, nVertexs, edges, todo);
            cout << "}\n";
        }
    }
    return 0;
}
