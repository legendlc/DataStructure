#include <iostream>
#include <queue>
#include <climits>
#include <cstring>
#define edge(s, e) edges[(s) * nVertices + (e)]
#define Max(a, b) (a) > (b) ? (a) : (b)
using namespace std;


typedef struct {
	int number;
	int in;
	int out;
	int earliest;
	int latest;
	bool isVisited;
} Vertex;

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
		vertices[i].isVisited = false;
	}
	//initialize edges and find whether there exist loops
	int* edges = new int[nVertices * nVertices];
	memset(edges, -1, sizeof(int) * nVertices * nVertices);
	for (int i = 0; i < nEdges; i++)
	{
		int s, e, dist;
		cin >> s >> e >> dist;
		edge(s, e) = dist;
		(vertices[e].in)++;
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
		for (int i = 0; i < nVertices; i++)
		{
			if (edge(index, i) != -1)
			{
				vertices[i].earliest = Max(vertices[i].earliest, vertices[index].earliest + edge(index, i));
				earliest = Max(earliest, vertices[i].earliest);
				edge(index, i) = -1;
				if (--(vertices[i].in) == 0)
				{
					Q.push(i);
					vertices[i].isVisited = true;
					count++;
				}
			}
		}
		Q.pop();
	}
	if (count < nVertices)
		cout << "Impossible";
	else
		cout << earliest;
	return 0;
}
