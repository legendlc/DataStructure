#include <iostream>
#include <algorithm>
#define parent(i) (i) / 2
#define leftChild(i) (i) * 2
#define rightChild(i) ((i) * 2 + 1)

using namespace std;

void swapInt(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

bool isSame(int* a, int* b, int N)
{
	int i = 0;
	while (i < N)
	{
		if (a[i] != b[i])
			return false;
		i++;
	}
	return true;
}

void disp(int* arr, int N)
{
	for (int i = 0; i < N; i++)
	{
		cout << arr[i];
		if (i < N - 1)
			cout << " ";
	}
}

void merge(int* arr, int as, int bs, int numA, int numB)
{
	int* space = new int[numA + numB];
	int ai = as, bi = bs;
	int index = 0;
	while (index < numA + numB)
	{
		if (bi >= bs + numB)
		{
			space[index++] = arr[ai++];
		}
		else if(ai >= as + numA)
		{
			space[index++] = arr[bi++];
		}
		else if (arr[ai] < arr[bi])
		{
			space[index++] = arr[ai++];
		}
		else
			space[index++] = arr[bi++];
	}
	for (int i = 0; i < numA + numB; i++)
		arr[as + i] = space[i];
	delete[] space;
}

int main()
{
	int N;
	cin >> N;
	int* unsorted = new int[N];
	int* partSorted = new int[N];
	int* insertSort = new int[N];
	int* mergeSort = new int[N];

	for (int i = 0; i < N; i++)
	{
		cin >> unsorted[i];
		insertSort[i] = unsorted[i];
		mergeSort[i] = unsorted[i];
	}
	for (int i = 0; i < N; i++)
	{
		cin >> partSorted[i];
	}


	int step;
	bool isInsert;
	bool isMerge;
	for (step = 1; step < N; step++)
	{
		//insert sort
		int index = step;
		while (index > 0 && insertSort[index] < insertSort[index - 1])
		{
			swapInt(insertSort[index], insertSort[index - 1]);
			index--;
		}
		isInsert = isSame(insertSort, partSorted, N);

		//merge sort
		int size = 1 << (step - 1);
		int skip = 1 << step;
		if (N % skip == 0)
		{
			for (int i = 0; i < N; i += skip)
			{
				merge(mergeSort, i, i + size, size, size);
			}
		}
		else if (N % skip <= size)
		{
			for (int i = 0; i + skip < N; i += skip)
			{
				merge(mergeSort, i, i + size, size, size);
			}
		}
		else
		{
			for (int i = 0; i < N; i += skip)
			{
				merge(mergeSort, i, i + size, size, N - i - size);
			}
		}
		//cout << step << ":\n";  disp(mergeSort, N); cout << "\n";
		isMerge = isSame(mergeSort, partSorted, N);
		if (isInsert && isMerge || (!(isInsert || isMerge)))
			continue;
		else
		{
			if (isInsert)
			{
				cout << "Insertion Sort\n";
				index = step + 1;
				while (index > 0 && insertSort[index] < insertSort[index - 1])
				{
					swapInt(insertSort[index], insertSort[index - 1]);
					index--;
				}
				disp(insertSort, N);
			}
			else
			{
				cout << "Merge Sort\n";
				int size = 1 << step;
				int skip = 1 << (step + 1);
				if (N % skip == 0)
				{
					for (int i = 0; i < N; i += skip)
					{
						merge(mergeSort, i, i + size, size, size);
					}
				}
				else if (N % skip <= size)
				{
					for (int i = 0; i + skip < N; i += skip)
					{
						merge(mergeSort, i, i + size, size, size);
					}
				}
				else
				{
					for (int i = 0; i < N; i += skip)
					{
						merge(mergeSort, i, i + size, size, N - i - size);
					}
				}
				disp(mergeSort, N);
			}
			break;
		}
	}
	return 0;
}
