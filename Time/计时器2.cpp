#include<windows.h>
#include<iostream>
#include<cstdio>
#include<conio.h>
#include<cstdlib>
using namespace std;

//��������
void gotoxy(int x,int y); 
void Save(int Sec);					//���� 

int main()
{
	int Sec=1;
	int input=-1;
	cout<<"��ʱ��"<<endl;
	cout<<"�������ʼ��<s>����<e>�˳���";
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
	COORD coord;   //��ȡ������ṹ��
	coord.X = x;
	coord.Y = y;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);  //��ȡ����̨�����ֵΪ-11
	SetConsoleCursorPosition(handle, coord);   //�ƶ���굽x��y��
}


void Save(int Sec)
{
	FILE *fp;
	fp=fopen("output.txt","a");
	fprintf(fp,"��ʱ�����%d\n",Sec);
	fclose(fp);
	gotoxy(0,3);
	cout<<"�ѱ���"; 
}
