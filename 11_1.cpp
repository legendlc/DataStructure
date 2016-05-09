#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;

typedef unsigned long long ull;
const int TABLE_SIZE = 1000007;

typedef struct User{
	User()
	{
		times = 0;
		next = nullptr;
	}
	ull number;
	int times;
	User* next;
}User;

ull hashFunc(ull key)
{
	return key % 1000000000;
}

User* findList(User* head, ull key)
{
	User* aim = head;
	while (aim != nullptr && aim->number != key)
		aim = aim->next;
	return aim;
}

User* findTarget(User** users, ull key)
{
	ull pos = hashFunc(key) % TABLE_SIZE;
	return findList(users[pos], key);
}

void addKey(User** users, ull key)
{
	User* user = findTarget(users, key);
	if (user == nullptr)
	{
		User* pos = users[hashFunc(key) % TABLE_SIZE];
		User* last = nullptr;
		while (pos != nullptr)
		{
			last = pos;
			pos = pos->next;
		}
		User* newUser = new User;
		newUser->number = key;
		newUser->times = 1;
		if (last == nullptr)
		{
			users[hashFunc(key) % TABLE_SIZE] = newUser;
		}
		else
		{	
			last->next = newUser;
		}
	}
	else
	{
		user->times++;
	}
}

bool cmp(const ull& a, const ull& b)
{
	return a < b;
}

int main()
{
	set<ull> phone;
	User** users = new User*[TABLE_SIZE];
	memset(users, 0, sizeof(User*) * TABLE_SIZE);
	int N;
	cin >> N;

	ull sender, receiver;
	for (int i = 0; i < N; i++)
	{
		cin >> sender >> receiver;
		addKey(users, sender);
		addKey(users, receiver);
		phone.insert(sender);
		phone.insert(receiver);
	}

	//sort(phone.begin(), phone.end(), cmp);
	ull max;
	int maxTimes = 0;
	int countSame;
	for (auto itr = phone.begin(); itr != phone.end(); itr++)
	{
		User* user = findTarget(users, *itr);
		if (user->times > maxTimes)
			max = user->number, maxTimes = user->times, countSame = 1;
		else if (user->times == maxTimes)
		{
			countSame++;
			if (user->number < max)
				max = user->number;
		}
	}
	if(countSame == 1)
		cout << max << " " << maxTimes;
	else
		cout << max << " " << maxTimes << " " << countSame;
	return 0;
}
