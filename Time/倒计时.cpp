#include<windows.h>
#include<cstdlib>
#include<iostream>
#include<ctime>
#include<conio.h>
using namespace std;


//�������� 
int Getmin(int Sec);								//�õ����� 
void Gotoxy(int x,int y);							//�ƶ���� 


//������ 
int main()
{
	int s;
	while(1)
	{
		cout<<"����ʱ��"<<endl<<"������Ҫ����ʱ������(0�˳�)��";
		cin>>s;
		if(s==0)									//����0�˳� 
		{
			exit(0);
		}
		for(int i=s; i>=0; i--)						//�����������ֵ��ʼ�ݼ� 
		{
			Gotoxy(0,2);							//ͨ��Gotoxy����ʵ��ˢ�� 
			cout<<"�����������"<<i<<"��!";
			Gotoxy(0,3);
			cout<<"��  "<<Getmin(i)<<" "<<"����"<<" "<<i%60<<" ��"; 
			Sleep(1000);
		}
		Gotoxy(0,4);
		cout<<"ʱ�䵽��";
		getch();
		system("cls"); 
	}
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


//����ƶ� 
void Gotoxy(int x,int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(handle,coord);
}
