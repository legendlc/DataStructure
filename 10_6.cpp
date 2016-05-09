#include <iostream>
#include <algorithm>
using namespace std;

int countSwap = 0;

void swapInt(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
	countSwap++;
}

int findN(int N, int* arr, int len)
{
	int i = 0;
	while (i < len && arr[i] != N)
		i++;
	if (i == len)
		return -1;
	else
		return i;
}

int main()
{	
	int N;
	cin >> N;
	int* arr = new int[N];
	for (int i = 0; i < N; i++)
	{
		cin >> arr[i];
	}
	int ix0, ixSwap;

	ix0 = findN(0, arr, N);

	while (1) {
		
		if (ix0 == 0)
		{
			while (ix0 == arr[ix0] && ix0 < N)
				ix0++;
			if (ix0 == N)
				break;
			swapInt(arr[0], arr[ix0]);
		}
		else
		{
			ixSwap = findN(ix0, arr, N);
			swapInt(arr[ix0], arr[ixSwap]);
			ix0 = ixSwap;
		}
	}
	
	

	


	cout << countSwap;

	delete[] arr;
	return 0;
}
