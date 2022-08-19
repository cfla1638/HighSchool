#include<windows.h>
#include<iostream>
#include<cstdio>
#include<conio.h>
#include<cstdlib>
using namespace std;

//函数声明
void gotoxy(int x,int y); 
void Save(int Sec);					//保存 

int main()
{
	int Sec=1;
	int input=-1;
	cout<<"计时器"<<endl;
	cout<<"任意键开始，<s>保存<e>退出：";
	getch();
	while(input!=101)
	{
		Sleep(1000);
		gotoxy(0,3);
		cout<<"        ";
		gotoxy(0,2);
		cout<<"Sec="<<Sec;
		input=-1;
		Sec++;
		if (_kbhit())
		{
			fflush(stdin);
			input=_getch();
		}
		if(input!=-1)
		{
			if(input==115)
			{
				Save(Sec);
			}
		}
	}
}


void gotoxy(int x, int y)
{
	HANDLE handle;
	COORD coord;   //获取坐标轴结构体
	coord.X = x;
	coord.Y = y;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);  //获取控制台句柄，值为-11
	SetConsoleCursorPosition(handle, coord);   //移动光标到x，y处
}


void Save(int Sec)
{
	FILE *fp;
	fp=fopen("output.txt","a");
	fprintf(fp,"计时结果：%d\n",Sec);
	fclose(fp);
	gotoxy(0,3);
	cout<<"已保存"; 
}
