#include<iostream>
#include<ctime>
#include<cstdlib>
#include<windows.h>
using namespace std;


void Gotoxy(int x,int y);


int main()
{
	time_t t;
	struct tm *lt,mt;
	cout<<"闹钟"<<endl;
	cout<<"格式：时 (回车) 分"<<endl; 
	cout<<"请输入时间:"<<endl;
	cin>>mt.tm_hour;
	cin>>mt.tm_min;
	cout<<"Please wait...";
	while(1)
	{
		time (&t);												//获取Unix时间戳。
		lt = localtime (&t);
		if(lt->tm_hour==mt.tm_hour && lt->tm_min==mt.tm_min)
		{
			cout<<endl<<"时间到"<<endl;
			system("pause");
			exit(0);
		}
		Sleep(100);
	}
	return 0;
}


void Gotoxy(int x,int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(handle,coord);
}
