#include<iostream>
#include<ctime>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
using namespace std;


//��������
void gotoxy(int x,int y);
int Getmin(int Sec);
int Save(int Sec);                                //����
void Pause();                               //pause

//������
int main()
{
	int Sec=0,input=0;
	cout<<"��ʱ��"<<endl<<"�������ʼ��ʱ . . .";
	getch();
	cout<<endl<<"��ʱ��ʼ,ѡ�e:exit s:save p:pause"<<endl;
	while(1)
	{
		Sleep(1000);
		if(kbhit())
		{
			fflush(stdin);//��ջ��������а����ͽ���
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
			if(input==101)          //����e
			{
				exit(0);
			}
			if(input==115)          //����s
			{
				Save(Sec);
			}
			if(input==112)          //����p
			{
				Pause();
			}
			gotoxy(0,5);
			cout<<Getmin(Sec)<<" �� "<<Sec%60<<" �� ";
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


//�õ�����
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
		cout<<"����ʧ�ܣ�";
		gotoxy(0,6);
		cout<<"                       ";
		return 0;
	}
	fprintf(p,"��ʱ�����%d\n",Sec);
	fclose(p);
	gotoxy(0,6);
	cout<<"����ɹ�";
}


void Pause()
{
	gotoxy(0,6);
	system("pause");
	gotoxy(0,6);
	cout<<"                       ";
}
