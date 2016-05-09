#include <iostream>
#include <cstring>
#include <stack>
#include <queue>
#include <climits>
using namespace std;

const int POS_INF = INT_MAX;

typedef struct{
    int dst;
    int edge;
}Edge;

typedef struct{
    bool isVisited;
    int value;
} Vertex;

struct cmp{
    bool operator()(Edge& a, Edge& b)
    {
        return a.edge < b.edge;
    }
};

int findLeast(int* dist, int nVertexs, Vertex* vertexs)
{
    int index = 0;
    while(vertexs[index].isVisited)
        index++;
    for(int i = index + 1; i < nVertexs; i++)
    {
        if(vertexs[i].isVisited == false)
        {
            if(dist[i] < dist[index])
                index = i;
        }
    }
    if(dist[index] == POS_INF)
        return -1;
    return index;
}

int Dijkstra(int source, Vertex* vertexs, int nVertexs, int* edges)
{
    int* dist = new int[nVertexs];
    queue<int> visited;
    //priority_queue<Edge, vector<Edge>, cmp> pq_not_visited;
    //initialize distances
    for(int i = 0; i < nVertexs; i++)
    {
        dist[i] = POS_INF;
    }
    dist[source] = 0;
    visited.push(source);
    vertexs[source].isVisited = true;
    while(visited.size() < nVertexs)
    {
        int n = visited.front();
        for(int j = 0; j < nVertexs; j++)
        {
            int D = edges[n * nVertexs + j];
            if(D > 0 && vertexs[j].isVisited == false)
            {
                if(dist[n] + D < dist[j])
                {
                    dist[j] = dist[n] + D;
                }
            }
        }
        int next = findLeast(dist, nVertexs, vertexs);
        if(next == -1)
            return -1;
        else
        {
            visited.push(next);
            vertexs[next].isVisited = true;
        }

    }
    int max = 0;
    for(int i = 0; i < nVertexs; i++)
        if(dist[i] > max)
            max = dist[i];
    delete[] dist;
    return max;
}

int main()
{
    int nVertexs, nEdges;
    cin >> nVertexs >> nEdges;
    Vertex* vertexs = new Vertex[nVertexs];

    //initialize n vertexs
    for(int i = 0; i < nVertexs; i++)
    {
        vertexs[i].value = i+1;
        vertexs[i].isVisited = false;
    }
    //use adjacency matrix to store edges
    int* edges = new int[nVertexs * nVertexs];
    memset(edges, 0, (nVertexs) * (nVertexs) * sizeof(int));
    for(int i = 0; i < nEdges; i++)
    {
        int a, b, d;
        cin >> a >> b >> d;
        edges[(a - 1) * nVertexs + (b - 1)] = d;
        edges[(b - 1) * nVertexs + (a - 1)] = d;
    }

/*
    for(int i = 0; i < nVertexs; i++)
    {
        for(int j = 0; j < nVertexs; j++)
        {
            cout << edges[i * (nVertexs) + j] << '\t';
        }
        cout << endl;
    }
*/

    //find the longest spell for each animal
    int* longest = new int[nVertexs];
    for(int i = 0; i < nVertexs; i++)
    {
        int result = Dijkstra(i, vertexs, nVertexs, edges);
        if(result == -1)
        {
            cout << 0;
            return 0;
        }
        else
            longest[i] = result;
    }
    //find the shortest one
    int index = 0;
    for(int i = 1; i < nVertexs; i++)
    {
        if(longest[i] < longest[index])
            index = i;
    }
    cout << index << ' ' << longest[index];

    delete[] vertexs;
    delete[] edges;
    delete[] longest;
    return 0;
}
