#include <iostream>
#include <queue>
#include <climits>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int main()
{
	int N;
	cin >> N;
	vector<int> vec;
	for (int i = 0; i < N; i++)
	{
		int tmp;
		cin >> tmp;
		vec.push_back(tmp);
	}
	sort(vec.begin(), vec.end());
	for (int i = 0; i < N; i++)
	{
		cout << vec[i];
		if (i < N - 1)
			cout << " ";
	}
	return 0;
}
