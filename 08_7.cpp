#include <iostream>
#include <queue>
#include <climits>
#include <cstring>

#define Min(a, b) (a) < (b) ? (a) : (b)
#define edge(s, e) edges[(s) * nVertices + (e)]

using namespace std;

const int POS_INF = INT_MAX;
const int UNDEFINED = -404;

typedef struct {
	int parent;
	int number;
	int dist;
} Vertex;

struct cmp {
	bool operator()(Vertex* a, Vertex* b)
	{
		return a->dist > b->dist;
	}	
};

int main()
{
	int nVertices, nEdges;
	cin >> nVertices >> nEdges;
	if (nEdges < nVertices - 1)
	{
		cout << -1;
		return 0;
	}
	//initialize vertices
	Vertex* vertices = new Vertex[nVertices];
	for (int i = 0; i < nVertices; i++) {
		vertices[i].parent = UNDEFINED;
		vertices[i].number = i + 1;
		vertices[i].dist = -1;
	}
	//initialize edges
	int* edges = new int[nVertices * nVertices];
	memset(edges, 0, sizeof(int) * nVertices * nVertices);
	for (int i = 0; i < nEdges; i++)
	{
		int s, e, dist;
		cin >> s >> e >> dist;
		edge(s - 1, e - 1) = dist;
		edge(e - 1, s - 1) = dist;
	}

	//start prim algo
	priority_queue<Vertex*, vector<Vertex*>, cmp> pq;
	int count = 0;
	Vertex& root = vertices[0];
	root.parent = -1;
	pq.push(&root);
	while (pq.size())
	{
		Vertex* head = pq.top();
		head->dist = 0;
		int index = head->number - 1;
		if (head->parent != -1)
			count += edge(index, head->parent);
		for (int i = 0; i < nVertices; i++)
		{
			if (vertices[i].dist != 0 && edge(index, i))
			{
				if (vertices[i].dist == -1)
				{
					vertices[i].dist = edge(index, i);
					vertices[i].parent = index;
					pq.push(vertices + i);
				}
				else if (vertices[i].dist > edge(index, i))
				{
					vertices[i].dist = edge(index, i);
					vertices[i].parent = index;
				}
			}
		}
		pq.pop();
	}
	
	int cnt = 0;
	for (int i = 0; i < nVertices; i++)
	{
		if (vertices[i].dist == 0)
			cnt++;
	}
	if (cnt == nVertices)
		cout << count;
	else
		cout << -1;

/*	
	for (int i = 0; i < nVertices; i++)
	{
		for (int j = 0; j < nVertices; j++)
		{
			cout << dist(i, j) << "\t";
		}
		cout << endl;
	}
*/
	
	return 0;
}
