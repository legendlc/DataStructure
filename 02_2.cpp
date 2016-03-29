/*************************************************************************
	> File Name: 02_2.cpp
*************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

typedef struct{
	Node()
	{

	}
	Node(Node& n)
	{
		addr = n.addr;
		value = n.value;
		next = n.next;
	}
	Node(string a, int v, string b)
	{
		addr = a;
		value = v;
		next = b;
	}
	string addr;
	int value;
	string next;
} Node;

class CompareFunctor
{
public:
	CompareFunctor(string& s)
	{
		_s = s;
	}
	bool operator()(Node& node)
	{
		return node.addr == _s;
	}
private:
	string _s;
};

vector<Node> vec;

int main()
{
	string head;
	int num;
	int interval;

	for(int i = 0; i < num; i++)
	{
		string addr_t;
		int value_t;
		string next_t;
		cin >> addr_t >> value_t >> next_t;
		Node tmp(addr_t, value_t, next_t);
		vec.push_back(tmp);
	}
	Node* arr = new Node[num];
	string target = head;
	int i = 0;
	while(target != "-1")
	{
		arr[i++] = *(find_if(vec.begin(), vec.end(), CompareFunctor(target)()));
		target = arr[i - 1].next;
	}
	
	for(int i = 0; i < num; i++)
	{
		cout << arr[i].value << ' ';
	}

	delete[] arr;
	return 0;
}

