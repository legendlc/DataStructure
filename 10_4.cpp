#include <iostream>
using namespace std;


int main()
{
	int N;
	cin >> N;
	int vec[51];
	for (int i = 0; i < 51; i++)
		vec[i] = 0;
	for (int i = 0; i < N; i++)
	{
		int tmp;
		cin >> tmp;
		vec[tmp]++;
	}
	for (int i = 0; i < 51; i++)
	{
		if (vec[i])
		{
			cout << i << ":" << vec[i] << endl;
		}
	}

	return 0;
}
