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
	cout<<"����"<<endl;
	cout<<"��ʽ��ʱ (�س�) ��"<<endl; 
	cout<<"������ʱ��:"<<endl;
	cin>>mt.tm_hour;
	cin>>mt.tm_min;
	cout<<"Please wait...";
	while(1)
	{
		time (&t);												//��ȡUnixʱ�����
		lt = localtime (&t);
		if(lt->tm_hour==mt.tm_hour && lt->tm_min==mt.tm_min)
		{
			cout<<endl<<"ʱ�䵽"<<endl;
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
