#include<windows.h>
#include<cstdlib>
#include<iostream>
#include<ctime>
#include<conio.h>
using namespace std;


//函数声明 
int Getmin(int Sec);								//得到分钟 
void Gotoxy(int x,int y);							//移动光标 


//主函数 
int main()
{
	int s;
	while(1)
	{
		cout<<"倒计时器"<<endl<<"请输入要倒计时的秒数(0退出)：";
		cin>>s;
		if(s==0)									//输入0退出 
		{
			exit(0);
		}
		for(int i=s; i>=0; i--)						//秒数从输入的值开始递减 
		{
			Gotoxy(0,2);							//通过Gotoxy函数实现刷新 
			cout<<"距离结束还有"<<i<<"秒!";
			Gotoxy(0,3);
			cout<<"即  "<<Getmin(i)<<" "<<"分钟"<<" "<<i%60<<" 秒"; 
			Sleep(1000);
		}
		Gotoxy(0,4);
		cout<<"时间到！";
		getch();
		system("cls"); 
	}
}


//得到分钟
int Getmin(int Sec)
{
	int n,i;
	n=Sec;
	i=0;
	while(n>=60)
	{
		n=n-60;
		i++;
	}
	return i;
} 


//光标移动 
void Gotoxy(int x,int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(handle,coord);
}
