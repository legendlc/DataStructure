#include <iostream>
#include <cstring>
#include <stack>
#include <set>
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

void DFS(int n, Vertex* vertexs, int nVertexs, int* edges, stack<int>& s)
{
    int i;
    for(i = 0; i < nVertexs; i++)
    {
        if(edges[n * nVertexs + i] > 0) //exits an edge between n and i
        {
            if(vertexs[i].color == white) //have not been visited
            {
                vertexs[i].color = grey;
                s.push(i);
                cout << i << " ";
                DFS(i, vertexs, nVertexs, edges, s);
            }
        }
    }
    if(i == nVertexs) //all vertexs connected have been visited
    {
        vertexs[i].color = black;
        //cout << n << " ";
        s.pop();
    }
}

void BFS(Vertex* vertexs, int nVertexs, int* edges, set<int>& s)
{
    while(!s.empty())
    {
        for(set<int>::iterator itr = s.begin(); itr != s.end(); itr++)
        {
            int n = *itr;
            for(int i = 0; i < nVertexs; i++)
            {
                if(edges[n * nVertexs + i] > 0 && vertexs[i].color == white)
                {
                    vertexs[i].color = grey;
                    cout << i << " ";
                    s.insert(i);
                }
            }
            vertexs[n].color = black;
            s.erase(n);
            //cout << endl << s.size() << endl;
        }
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

    //begin dfs
    for(int i = 0; i < nVertexs; i++)
    {
        stack<int> todo;
        if(vertexs[i].color == white)
        {
            cout << "{ ";
            vertexs[i].color = grey;
            todo.push(i);
            cout << i << " ";
            DFS(i, vertexs, nVertexs, edges, todo);
            cout << "}\n";
        }
    }

    //back to original state
    for(int i = 0; i < nVertexs; i++)
    {
        vertexs[i].color = white;
    }
    //begin bfs
    for(int i = 0; i < nVertexs; i++)
    {
        set<int> todo;
        if(vertexs[i].color == white)
        {
            cout << "{ ";
            vertexs[i].color = grey;
            todo.insert(i);
            cout << i << " ";
            BFS(vertexs, nVertexs, edges, todo);
            cout << "}\n";
        }
    }
    return 0;
}
