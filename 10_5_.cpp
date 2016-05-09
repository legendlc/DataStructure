#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;


typedef struct User{
	User()
	{
		for (int i = 1; i < 6; i++)
			scores[i] = -1;
		total = -1;
		nPass = 0;
	}
	char id[6];
	int scores[6];
	int total;
	int nPass;
} User;

void intToCString(int id, char* buf)
{
	buf[5] = '\0';
	int i;
	for (i = 0; i < 5; i++)
		buf[i] = '0';
	int tmp = id;
	//
	i = 0;
	while (tmp)
	{
		buf[4 - i] = (tmp % 10) + '0';
		tmp /= 10; 
		i++;
	}
}

int cStringToInt(char* buf)
{
	int res = 0;
	int base = 1;
	for (int i = 0; i < 5; i++)
	{
		res += (buf[4 - i] - '0') * base;
		base *= 10;
	}
	return res;
}

bool cmpId(const char* id1, const char* id2)
{
	int ix = 0;
	while (id1[ix] == id2[ix])
		ix++;
	return id1[ix] < id2[ix];
}


bool cmp(const User& u1, const User& u2)
{
	if (u1.total > u2.total)
		return true;
	else if (u1.total < u2.total)
		return false;
	else
	{
		if (u1.nPass > u2.nPass)
			return true;
		else if (u1.nPass < u2.nPass)
			return false;
		else
			return cmpId(u1.id, u2.id);
	}
}


int main()
{	
	//get raw data
	int problems[6];
	int nUsers, nProblems, nSubmissions;
	cin >> nUsers >> nProblems >> nSubmissions;
	//get full marks of each problem
	for (int i = 1; i <= nProblems; i++)
	{
		cin >> problems[i];
	}
	//initialize users
	User* users = new User[nUsers + 1];
	for (int i = 1; i <= nUsers; i++)
	{
		intToCString(i, users[i].id);
	}
	//get submissions
	char id[6];
	int number;
	int problem, score;
	for (int i = 0; i < nSubmissions; i++)
	{
		cin >> id >> problem >> score;
		number = cStringToInt(id);
		User& user = users[number];
		if (user.scores[problem] == -1)
			user.scores[problem] = 0;
		if (score <= user.scores[problem]); //nothing need to change
		else
		{
			if (user.total < 0) //never pass the compiler
				user.total = 0;
			
			if (user.scores[problem] == -1)
			{
				user.total += score;
			}
			else
			{
				user.total += (score - user.scores[problem]);
			}
			user.scores[problem] = score;
			if (score < problems[problem])
			{ //not full mark

			}
			else
			{
				user.nPass++;
			}
			
		}
	}
	
	//sort
	sort(users + 1, users + nUsers + 1, cmp);

	/*test
	for (int i = 1; i <= nUsers; i++)
	{
		User& user = users[i];
		cout << user.id << "\t" << user.total << "\t" << user.nPass << endl;
		for (int j = 1; j <= nProblems; j++)
		{
			cout << j << " : " << user.scores[j] << endl;
		}
	}*/
	
	//output ranks
	int ix = 1, rank = 1;
	int total;
	int countSame;
	while (rank <= nUsers && users[rank].total >= 0)
	{
		countSame = 0;
		total = users[ix].total;
		while (users[ix].total == total)
		{
			countSame++;
			printf("%d %s %d ", rank, users[ix].id, total);
			for (int i = 1; i <= nProblems; i++)
			{
				if (users[ix].scores[i] < 0)
					printf("-");
				else
					printf("%d", users[ix].scores[i]);
				if (i < nProblems)
					printf(" ");
				else
					printf("\n");
			}
			//update
			ix++;			
		}
		rank += countSame;
	}
	

	return 0;
}
