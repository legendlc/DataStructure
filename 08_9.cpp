#include <iostream>
#include <queue>
#include <climits>
#include <cstring>

#define Max(a, b) (a) > (b) ? (a) : (b)
#define Min(a, b) (a) < (b) ? (a) : (b)
using namespace std;

const int POS_INF = INT_MAX;

typedef struct {
	int number;
	int in;
	int out;
	int earliest;
	int latest;
	bool isVisited;
} Vertex;

typedef struct Edge {
	int end;
	int len;
	struct Edge* next;
} Edge;

int edge(int s, int e, Edge* edges)
{
	Edge* tmp = edges[s].next;
	while (tmp != nullptr)
	{
		if (tmp->end == e)
			return tmp->len;
		tmp = tmp->next;
	}
	return -1;
}

int main()
{
	int nVertices, nEdges;
	cin >> nVertices >> nEdges;

	//initialize vertices
	Vertex* vertices = new Vertex[nVertices];
	for (int i = 0; i < nVertices; i++) {
		vertices[i].number = i;
		vertices[i].in = 0;
		vertices[i].out = 0;
		vertices[i].earliest = 0;
		vertices[i].latest = POS_INF;
		vertices[i].isVisited = false;
	}
	//initialize edges
	Edge* edges = new Edge[nVertices];
	for (int i = 0; i < nVertices; i++)
	{
		edges[i].end = i;
		edges[i].len = 0;
		edges[i].next = nullptr;
	}
	for (int i = 0; i < nEdges; i++)
	{
		int s, e, dist;
		cin >> s >> e >> dist;
		Edge* newEdge = new Edge;
		newEdge->end = e - 1;
		newEdge->len = dist;
		//add new Edge at the tail
		Edge* tmp = edges + s - 1;
		newEdge->next = tmp->next;
		tmp->next = newEdge;
		//refresh degrees in and out
		(vertices[s - 1].out)++;
		(vertices[e - 1].in)++;
	}

	//find earliest time
	queue<int> Q;
	int count = 0;
	int earliest = 0;
	for (int i = 0; i < nVertices; i++)
	{
		if (vertices[i].in == 0)
		{
			Q.push(i);
			vertices[i].isVisited = true;
			count++;
		}
	}//initialize Queue
	while (Q.size())
	{
		int index = Q.front();
		Edge* tmp = edges[index].next;
		while(tmp != nullptr)
		{
			int end = tmp->end;
			if(!vertices[end].isVisited)
			{
				vertices[end].earliest = Max(vertices[end].earliest, vertices[index].earliest + tmp->len);
				earliest = Max(earliest, vertices[end].earliest);
				if (--(vertices[end].in) == 0)
				{
					Q.push(end);
					vertices[end].isVisited = true;
					count++;
				}
			}
			tmp = tmp->next;
		}
		Q.pop();
	}
	if (count < nVertices)
	{
		cout << 0;
		return 0;
	}
	else
		cout << earliest << endl;


	//find latest time
	int latest = 0;
	queue<int> latestQueue;
	for (int i = 0; i < nVertices; i++)
		vertices[i].isVisited = false;
	for (int i = 0; i < nVertices; i++)
	{
		if (vertices[i].out == 0)
		{
			latestQueue.push(i);
			vertices[i].isVisited = true;
			vertices[i].latest = vertices[i].earliest;
		}
	}// initialize Queue
	while (latestQueue.size())
	{
		int index = latestQueue.front();
		for (int i = 0; i < nVertices; i++)
		{
			int dist = edge(i, index, edges);
			if ( dist != -1 && !vertices[i].isVisited)
			{
				vertices[i].latest = Min(vertices[i].latest, vertices[index].latest - dist);
				if (--(vertices[i].out) == 0)
				{
					latestQueue.push(i);
					vertices[i].isVisited = true;
				}
			}
		}
		latestQueue.pop();
	}

	for (int i = 0; i < nVertices; i++)
	{
		Edge* tmp = edges[i].next;
		while (tmp != nullptr)
		{
			int e = tmp->end;
			if (vertices[i].earliest == vertices[i].latest && vertices[e].earliest == vertices[e].latest)
				cout << i+1 << "->" << e+1 << endl;
			tmp = tmp->next;
		}
	}
	return 0;
}
