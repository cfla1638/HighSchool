#include<iostream>
#include<ctime>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
using namespace std;


//函数声明
void gotoxy(int x,int y);
int Getmin(int Sec);
int Save(int Sec);                                //保存
void Pause();                               //pause

//主函数
int main()
{
	int Sec=0,input=0;
	cout<<"计时器"<<endl<<"任意键开始计时 . . .";
	getch();
	cout<<endl<<"计时开始,选项：e:exit s:save p:pause"<<endl;
	while(1)
	{
		Sleep(1000);
		if(kbhit())
		{
			fflush(stdin);//清空缓存区？有按键就接受
			input=getch();
		}
		Sec++;
		gotoxy(0,3);
		cout<<"Sec="<<Sec;
		gotoxy(0,4);
		cout<<"input="<<input<<"   ";
		if(input!=0)
		{
			gotoxy(0,6);
			cout<<"                       ";
			if(input==101)          //输入e
			{
				exit(0);
			}
			if(input==115)          //输入s
			{
				Save(Sec);
			}
			if(input==112)          //输入p
			{
				Pause();
			}
			gotoxy(0,5);
			cout<<Getmin(Sec)<<" 分 "<<Sec%60<<" 秒 ";
			input=0;
		}
	}
	return 0;
}


void gotoxy(int x, int y)
{
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
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


int Save(int Sec)
{
	FILE *p;
	p=fopen("output.txt","a");
	if(!p)
	{
		gotoxy(0,6);
		cout<<"保存失败！";
		gotoxy(0,6);
		cout<<"                       ";
		return 0;
	}
	fprintf(p,"计时结果：%d\n",Sec);
	fclose(p);
	gotoxy(0,6);
	cout<<"保存成功";
}


void Pause()
{
	gotoxy(0,6);
	system("pause");
	gotoxy(0,6);
	cout<<"                       ";
}
