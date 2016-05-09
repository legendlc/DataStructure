#include <iostream>
#include <queue>
#include <climits>
#include <cstring>
#define Min(a, b) (a) < (b) ? (a) : (b)
#define dist(s, e) distances[(s) * nVertices + (e)]
using namespace std;

const int POS_INF = INT_MAX;

typedef struct {
	int i;
	int v;
} X;

inline int existPath(int s, int e, int* edges, int nVertices)
{
	return edges[s * nVertices + e];
}

int maxDist(int s, int* distances, int nVertices)
{
	int tmp = dist(s, 0);
	for (int i = 1; i < nVertices; i++)
	{
		if (dist(s, i) > tmp)
			tmp = dist(s, i);
	}
	return tmp;
}

inline int distBetween(int s, int e, int* distances, int nVertices)
{
	return distances[s * nVertices + e];
}

struct cmp {
	bool operator()(X& a, X& b)
	{
		return a.v > b.v;
	}
		
};

int main()
{
	int nVertices, nEdges;
	cin >> nVertices >> nEdges;
	int* edges = new int[nVertices * nVertices];
	int* distances = new int[nVertices * nVertices];
	memset(edges, 0, sizeof(int) * nVertices * nVertices);
	for (int i = 0; i < nVertices; i++)
	{
		for (int j = 0; j < nVertices; j++)
		{
			dist(i, j) = POS_INF;
		}
	}
	for (int i = 0; i < nVertices; i++)
	{
		dist(i, i) = 0;
	}
	for (int i = 0; i < nEdges; i++)
	{
		int s, e, l;
		cin >> s >> e >> l;
		edges[(s - 1) * nVertices + e - 1] = l;
		edges[(e - 1) * nVertices + s - 1] = l;
		distances[(s - 1) * nVertices + e - 1] = l;
		distances[(e - 1) * nVertices + s - 1] = l;
	}
	for (int k = 0; k < nVertices; k++)
	{
		for (int i = 0; i < nVertices; i++)
		{
			for (int j = 0; j < nVertices; j++)
			{
				if (i != j)
				{
					if (i != k && k != j && dist(i, k) != POS_INF && dist(k, j) != POS_INF)
					{
						dist(i, j) = Min(dist(i, j), dist(i, k) + dist(k, j));
					}
				}
			}
		}
	}
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
	priority_queue<X, vector<X>, cmp> pq;
	for (int i = 0; i < nVertices; i++)
	{
		X tmp;
		tmp.i = i;
		int maxD = maxDist(i, distances, nVertices);
		if (maxD == POS_INF)
		{
			cout << 0;
			return 0;
		}
		tmp.v = maxD;
		pq.push(tmp);
	}
	cout << (pq.top()).i + 1 << " " << (pq.top()).v;
	return 0;
}
