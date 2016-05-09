#include <iostream>
#include <cstring>
#include <stack>
#include <queue>
#include <climits>
using namespace std;

const int POS_INF = INT_MAX;

typedef struct {
	int dst;
	int edge;
}Node;

typedef struct {
	int len;
	int cost;
}Edge, Dist;

typedef struct {
	bool isVisited;
	int value;
} Vertex;

int findLeast(Dist* dist, int nVertexs, Vertex* vertexs)
{
	int index = 0;
	while (vertexs[index].isVisited)
		index++;
	for (int i = index + 1; i < nVertexs; i++)
	{
		if (vertexs[i].isVisited == false)
		{
			if (dist[i].len < dist[index].len)
				index = i;
			else if (dist[i].len == dist[index].len)
			{
				if (dist[i].cost == dist[index].cost)
					index = i;
			}
		}
	}
	if (dist[index].len == POS_INF)
		return -1;
	return index;
}

Dist Dijkstra(int source, int destination, Vertex* vertexs, int nVertexs, Edge* edges)
{
	Dist* dist = new Dist[nVertexs];
	queue<int> visited;
	//priority_queue<Edge, vector<Edge>, cmp> pq_not_visited;
	//initialize distances
	for (int i = 0; i < nVertexs; i++)
	{
		dist[i].len = POS_INF;
		dist[i].cost = POS_INF;
	}
	dist[source].len = 0;
	dist[source].cost = 0;
	visited.push(source);
	vertexs[source].isVisited = true;
	while (!vertexs[destination].isVisited)
	{
		int n = visited.back();
		for (int j = 0; j < nVertexs; j++)
		{
			int D = edges[n * nVertexs + j].len;
			int C = edges[n * nVertexs + j].cost;
			if (D > 0 && vertexs[j].isVisited == false)
			{
				if (dist[n].len + D < dist[j].len)
				{
					dist[j].len = dist[n].len + D;
					dist[j].cost = dist[n].cost + C;
				}
				else if (dist[n].len + D == dist[j].len)
				{
					if (dist[n].cost + C < dist[j].cost)
						dist[j].cost = dist[n].cost + C;
				}
			}
		}
		int next = findLeast(dist, nVertexs, vertexs);
		visited.push(next);
		vertexs[next].isVisited = true;
	}
	Dist res = dist[destination];
	delete[] dist;
	return res;
}

int main()
{
	int nVertexs, nEdges;
	int src, dst;
	cin >> nVertexs >> nEdges;
	cin >> src >> dst;
	Vertex* vertexs = new Vertex[nVertexs];

	//initialize n vertexs
	for (int i = 0; i < nVertexs; i++)
	{
		vertexs[i].value = i;
		vertexs[i].isVisited = false;
	}
	//use adjacency matrix to store edges
	Edge* edges = new Edge[nVertexs * nVertexs];
	for (int i = 0; i < nVertexs; i++)
	{
		for (int j = 0; j < nVertexs; j++)
		{
			edges[i * nVertexs + j].len = 0;
			edges[i * nVertexs + j].cost = 0;
		}
	}
	for (int i = 0; i < nEdges; i++)
	{
		int s, d, dist, cost;
		cin >> s >> d >> dist >> cost;
		edges[s * nVertexs + d].len = dist;
		edges[d * nVertexs + s].len = dist;
		edges[s * nVertexs + d].cost = cost;
		edges[d * nVertexs + s].cost = cost;
	}

	Dist result = Dijkstra(src, dst, vertexs, nVertexs, edges);
	cout << result.len << " " << result.cost;

	delete[] vertexs;
	delete[] edges;
	return 0;
}
