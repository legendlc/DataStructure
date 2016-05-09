#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>
#define parent(i) (i) / 2
#define leftChild(i) (i) * 2
#define rightChild(i) ((i) * 2 + 1)
using namespace std;

int minimum(int node, int N)
{
	while (node <= N)
	{
		node = leftChild(node);
	}
	node = parent(node);
	return node;
}

int nextNode(int node, int N)
{
	if (node % 2 == 0) //node is a left child
	{
		if (rightChild(node) <= N)
			return minimum(rightChild(node), N);
		else
		{
			return parent(node) > 0 ? parent(node) : -1;
		}
	}
	else
	{
		if (rightChild(node) <= N)
			return minimum(rightChild(node), N);
		else
		{
			int p = parent(node);
			int pp = parent(p);
			while (p && pp)
			{
				if (p == leftChild(pp))
					return pp;
				else
				{
					p = pp;
					pp = parent(pp);
				}
			}
			return -1;
		}
	}
}

int main()
{
	int N;
	cin >> N;
	int nLayers = log2(N + 1);
	vector<int> vec;
	for (int i = 0; i < N; i++)
	{
		int tmp;
		cin >> tmp;
		vec.push_back(tmp);
	}
	sort(vec.begin(), vec.end());
	//calculate the position of a node
	int* arr = new int[N + 1];
	int cnt = 0;
	int tmp = 1;
	while (tmp <= N)
	{
		tmp = leftChild(tmp);
	}
	tmp = parent(tmp);
	
	while (tmp != -1)
	{
		arr[tmp] = cnt++;
		tmp = nextNode(tmp, N);
	}

	for (int i = 1; i <= N; i++)
	{
		cout << vec[arr[i]];
		if (i < N)
			cout << " ";
	}

	delete[] arr;
	return 0;
}
