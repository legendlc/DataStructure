#include <iostream>
#include <queue>
#include <climits>
using namespace std;

const int POS_INF = INT_MAX;

typedef struct {
	int distance;
	int total;
	int number;
	bool isVisited;
} City;

typedef struct Edge {
	int length;
	int startCity;
	int endCity;
	Edge* next;
} Edge;

struct cmp {
	bool operator()(Edge& a, Edge& b)
	{
		return a.length > b.length;
	}
};

int Dijkstra(City* cities, int nCities, Edge* roads, int startCity, int endCity,
	priority_queue<int>& pq_dist, priority_queue<Edge, vector<Edge>, cmp>& pq_edges)
{
	cities[startCity].distance = 0;
	cities[startCity].isVisited = true;
	Edge* tmp = roads[startCity].next;
	while (tmp != nullptr)
	{
		if (tmp->endCity == endCity)
		{
			pq_dist.push(cities[tmp->startCity].distance + tmp->length);
		}
		if (cities[tmp->endCity].distance > cities[startCity].distance + tmp->length)
		{
			cities[tmp->endCity].distance = cities[startCity].distance + tmp->length;
			cities[tmp->endCity].total = cities[startCity].total + cities[tmp->endCity].number;

		}
		pq_edges.push(*tmp);
		tmp = tmp->next;
	}

	while (pq_edges.size() > 0)
	{
		Edge e = pq_edges.top();
		cities[e.endCity].isVisited = true;
		pq_edges.pop();
		tmp = roads[e.endCity].next;
		while (tmp != nullptr)
		{
			if (tmp->endCity == endCity)
			{
				pq_dist.push(cities[tmp->startCity].distance + tmp->length);
			}
			if (!cities[tmp->endCity].isVisited)
			{
				if (cities[tmp->endCity].distance > cities[tmp->startCity].distance + tmp->length)
				{
					cities[tmp->endCity].distance = cities[startCity].distance + tmp->length;
					cities[tmp->endCity].total = cities[startCity].total + cities[tmp->endCity].number;
				}
				else if (cities[tmp->endCity].distance == cities[tmp->startCity].distance + tmp->length)
				{
					if (cities[tmp->endCity].total < cities[tmp->startCity].total + cities[tmp->endCity].number)
					{
						cities[tmp->endCity].total = cities[tmp->startCity].total + cities[tmp->endCity].number;
					}
				}
				pq_edges.push(*tmp);
			}
			tmp = tmp->next;
		}
	}
	int minimum = pq_dist.top();
	pq_dist.pop();
	int countShortest = 1;
	while (pq_dist.size() > 0 && pq_dist.top() == minimum)
	{
		pq_dist.pop();
		countShortest++;
	}
	return countShortest;
}

int main()
{
	int nCities, nRoads;
	cin >> nCities >> nRoads;
	int startCity, endCity;
	cin >> startCity >> endCity;
	City* cities = new City[nCities];
	Edge* roads = new Edge[nCities];
	//get cities
	for (int i = 0; i < nCities; i++)
	{
		cin >> cities[i].number;
		cities[i].total = cities[i].number;
		cities[i].isVisited = false;
		cities[i].distance = POS_INF;
		roads[i].endCity = i;
		roads[i].length = 0;
		roads[i].next = nullptr;
	}
	//get roads
	for (int i = 0; i < nRoads; i++)
	{
		int s, e, l;
		cin >> s >> e >> l;
		Edge* road = new Edge;
		road->startCity = s;
		road->endCity = e;
		road->length = l;
		Edge* tmp = roads[s].next;
		Edge* last = roads + s;
		while (tmp != nullptr && tmp->endCity < road->endCity)
		{
			last = tmp;
			tmp = tmp->next;
		}
		road->next = last->next;
		last->next = road;
	}
/*
	//print roads
	for (int i = 0; i < nCities; i++)
	{
		Edge* tmp = roads[i].next;
		cout << i << " : ";
		while (tmp != nullptr)
		{
			cout << "(" << tmp->startCity << ", " << tmp->endCity << ", " << tmp->length << ") ";
			tmp = tmp->next;
		}
		cout << endl;
	}
*/

	priority_queue<int> dist;
	priority_queue<Edge, vector<Edge>, cmp> edges;
	int nWays = Dijkstra(cities, nCities, roads, startCity, endCity, dist, edges);

	cout << nWays << " " << cities[endCity].total;
	return 0;
}
