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

void heapify(int* arr, int t, int N)
{
	int tmp = t;
	int toComp;
	while (tmp <= N)
	{
		if (rightChild(tmp) > N)
		{
			if (leftChild(tmp) > N)
				return;
			else
				toComp = leftChild(tmp);
		}
		else
			toComp = arr[leftChild(tmp)] > arr[rightChild(tmp)] ? leftChild(tmp) : rightChild(tmp);
		if (arr[tmp] < arr[toComp])
		{
			swapInt(arr[tmp], arr[toComp]);
			tmp = toComp;
		}
		else
			return;
	}
}

void makeHeap(int* arr, int N)
{
	for (int i = N / 2; i >= 1; i--)
	{
		heapify(arr, i, N);
	}
}

void desc(int* arr, int N)
{
	heapify(arr, 1, N);
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

int main()
{
	int N;
	cin >> N;
	int* unsorted = new int[N];
	int* partSorted = new int[N];
	int* insertSort = new int[N];
	int* heapSort = new int[N+1];

	for (int i = 0; i < N; i++)
	{
		cin >> unsorted[i];
		insertSort[i] = unsorted[i];
		heapSort[i+1] = unsorted[i];
	}
	for (int i = 0; i < N; i++)
	{
		cin >> partSorted[i];
	}
	makeHeap(heapSort, N);

	int step;
	bool isInsert;
	bool isHeap;
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

		//heap sort
		swapInt(heapSort[1], heapSort[N + 1 - step]);
		desc(heapSort, N - step);
		isHeap = isSame(heapSort + 1, partSorted, N);
		if (isInsert && isHeap || (!(isInsert || isHeap)))
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
				cout << "Heap Sort\n";
				swapInt(heapSort[1], heapSort[N - step]);
				desc(heapSort, N - step - 1);
				disp(heapSort + 1, N);
			}
				
			break;
		}
	}
	return 0;
}
