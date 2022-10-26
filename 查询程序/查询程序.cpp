#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

#define USER_COUNT 1000
#define MAX_ARR_SIZE 50

//数据结构
typedef struct UserData
{
	string userNum;
	string otherInfo;
	UserData *next;
} UserData;

typedef struct
{
	string userName;
	UserData *data;
} UserList[USER_COUNT];

typedef struct
{
	UserList list;
	int userCount;
} UserTable;

//函数声明
void ReadFile(UserTable &T);
void FindUser(UserTable T, string userName);
void ShowAll(UserTable T);
bool OneInList(UserTable T, string userName);
int LocateUser(UserTable T, string userName);

//主函�?
int main(int argc, char const *argv[])
{
	UserTable T;
	string userName;

	ReadFile(T);

	cout << "please input your name:";
	cin >> userName;
	if (!OneInList(T, userName))
	{
		cout << endl
			 << "Can Not Find This Name!" << endl;
		getch();
		return 0;
	}
	FindUser(T, userName);

	getch();
	return 0;
}

void ShowAll(UserTable T)
{
	for (int i = 0; i < T.userCount; ++i)
	{
		UserData *point = T.list[i].data;

		cout << "Name:"
			 << "\t" << T.list[i].userName << endl;
		while (point != NULL)
		{
			cout << "Num:"
				 << "\t" << point->userNum << endl;
			point = point->next;
		}
	}
}

void FindUser(UserTable T, string userName)
{
	for (int i = 0; i < T.userCount; ++i)
	{
		if (T.list[i].userName == userName)
		{
			int seqNum = 1;
			UserData *point = T.list[i].data;

			cout << "Name:"
				 << "\t" << T.list[i].userName << endl
				 << endl;
			while (point != NULL)
			{
				if (point->otherInfo != "*")
				{
					cout << seqNum << "\t";
					cout << "Num:"
						 << "\t" << point->userNum;
					cout << "\totherInfo:\t" << point->otherInfo << endl;
				}
				else
				{
					cout << seqNum << "\t";
					cout << "Num:"
						 << "\t" << point->userNum << endl;
				}
				seqNum++;
				point = point->next;
			}
		}
	}
}

void ReadFile(UserTable &T)
{
	FILE *fp;
	int i = 0;
	char cuserName[MAX_ARR_SIZE];
	char cuserNum[MAX_ARR_SIZE];
	char cotherInfo[MAX_ARR_SIZE];

	T.userCount = 0;
	fp = fopen("userData.txt", "r");
	while (!feof(fp))
	{
		fscanf(fp, "%s\t%s\t%s\n", cuserName, cuserNum, cotherInfo);
		string userName(cuserName);
		string userNum(cuserNum);
		string otherInfo(cotherInfo);

		if (OneInList(T, userName))
		{
			int x = LocateUser(T, userName);

			T.list[x].userName = userName;

			UserData *data;
			data = new UserData;
			data->userNum = userNum;
			data->otherInfo = otherInfo;
			data->next = T.list[x].data;
			T.list[x].data = data;
		}
		else
		{
			T.list[i].userName = userName;
			T.list[i].data = NULL;

			UserData *data;
			data = new UserData;
			data->userNum = userNum;
			data->otherInfo = otherInfo;
			data->next = T.list[i].data;
			T.list[i].data = data;
			T.userCount++;
			// cout<<T.list[i].data->userNum<<endl;
			// cout<<T.list[i].data->otherInfo<<endl;
			// system("pause");

			i++;
		}
	}
	fclose(fp);
}

bool OneInList(UserTable T, string userName)
{
	for (int i = 0; i < T.userCount; ++i)
	{
		if (T.list[i].userName == userName)
		{
			return true;
		}
	}
	return false;
}

int LocateUser(UserTable T, string userName)
{
	for (int i = 0; i < T.userCount; ++i)
	{
		if (T.list[i].userName == userName)
		{
			return i;
		}
	}
	return -1;
}
