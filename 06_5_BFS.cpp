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
    int x;
    int y;
} Value;

typedef struct{
    COLOR color;
    Value value;
    bool isEnd;
    int nSteps;
} Vertex;

bool BFS(Vertex* vertexs, int nVertexs, int* edges, queue<int>& s)
{
    while(!s.empty())
    {
        int n = s.front();
        for(int i = 0; i < nVertexs; i++)
        {
            if(edges[n * nVertexs + i] > 0 && vertexs[i].color == white)
            {
                vertexs[i].color = grey;
                vertexs[i].nSteps = vertexs[n].nSteps + 1;
                if(vertexs[i].isEnd)
                    return true;
                else
                    s.push(i);
            }
        }
        vertexs[n].color = black;
        s.pop();
    }
    return false;
}

int existEdge(Vertex& a, Vertex& b, int D)
{
    if((a.value.x - b.value.x) * (a.value.x - b.value.x) + (a.value.y - b.value.y) * (a.value.y - b.value.y)
        <= D * D)
        return 1;
    else
        return 0;
}

int main()
{
    int nVertexs, D;
    cin >> nVertexs >> D;
    Vertex* vertexs = new Vertex[nVertexs+2]; //start(0, 0) + nVertexs + end

    //initialize start point
    vertexs[0].color = white;
    vertexs[0].nSteps = 0;
    vertexs[0].isEnd = false;
    vertexs[0].value.x = 0;
    vertexs[0].value.y = 0;
    //initialize n vertexs
    for(int i = 1; i <= nVertexs; i++)
    {
        vertexs[i].color = white;
        vertexs[i].isEnd = false;
        vertexs[i].nSteps = 0;
        cin >> vertexs[i].value.x >> vertexs[i].value.y;
    }
    //initialize end point
    vertexs[nVertexs+1].color = white;
    vertexs[nVertexs+1].isEnd = true;
    vertexs[nVertexs+1].nSteps = 0;

    //use adjacency matrix to store edges
    int* edges = new int[(nVertexs + 2) * (nVertexs + 2)];
    memset(edges, 0, (nVertexs + 2) * (nVertexs + 2) * sizeof(int));
    for(int i = 0; i < nVertexs + 1; i++)
    {
        for(int j = i + 1; j < nVertexs + 2; j++)
        {
            /*if(i == 0)
            {
                if(j < nVertexs + 1)
                {
                    int hasEdge;
                    int x = vertexs[j].value.x;
                    int y = vertexs[j].value.y;
                    if(x * x + y * y <= (15 + D) * (15 + D))
                        hasEdge = 1;
                    else
                        hasEdge = 0;
                    edges[i * (nVertexs + 2) + j] = hasEdge;
                    edges[j * (nVertexs + 2) + i] = hasEdge;
                }
            }
            else*/
            {
                if(j < nVertexs + 1)
                {
                    int hasEdge = existEdge(vertexs[i], vertexs[j], D);
                    edges[i * (nVertexs + 2) + j] = hasEdge;
                    edges[j * (nVertexs + 2) + i] = hasEdge;
                }
                else
                {
                    int hasEdge;
                    int x = vertexs[i].value.x;
                    int y = vertexs[i].value.y;
                    if(50 - x <= D || x + 50 <= D || 50 - y <= D || y + 50 <= D)
                        hasEdge = 1;
                    else
                        hasEdge = 0;
                    edges[i * (nVertexs + 2) + j] = hasEdge;
                    edges[j * (nVertexs + 2) + i] = hasEdge;
                }
            }
        }
    }

/*
    for(int i = 0; i < nVertexs + 2; i++)
    {
        for(int j = 0; j < nVertexs + 2; j++)
        {
            cout << edges[i * (nVertexs + 2) + j] << ' ';
        }
        cout << endl;
    }
*/

    //begin bfs
    queue<int> todo;
    vertexs[0].color = grey;
    todo.push(0);
    bool canLive = BFS(vertexs, nVertexs + 2, edges, todo);
    if(canLive)
    {
        cout << vertexs[nVertexs+1].nSteps << endl;
        int tmp = nVertexs+1;
        stack<Value> posStack;
        while(vertexs[tmp].nSteps > 0)
        {
            for(int i = 0; i < nVertexs + 2; i++)
            {
                if(edges[tmp * (nVertexs + 2) + i] && vertexs[i].nSteps == vertexs[tmp].nSteps - 1)
                {
                    tmp = i;
                    Value v;
                    v.x = vertexs[i].value.x;
                    v.y = vertexs[i].value.y;
                    posStack.push(v);
                    break;
                }
            }
        }
        posStack.pop();
        while(!posStack.empty())
        {
            Value v = posStack.top();
            cout << v.x << " " << v.y << endl;
            posStack.pop();
        }
    }
    else
        cout << 0;




    delete[] vertexs;
    delete[] edges;
    return 0;
}
