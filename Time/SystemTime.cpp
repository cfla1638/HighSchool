#include <stdio.h>
#include <time.h>
#include<windows.h>

void Gotoxy(int x,int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(handle,coord);
}

int main ()
{
	//���ع�� 
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false; //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
	//���� 
	time_t t;
	struct tm * lt;
	while(1)
	{
		time (&t);												//��ȡUnixʱ�����
		lt = localtime (&t);									//תΪʱ��ṹ��
		Gotoxy(0,0);
		printf ( "%d/%d/%d %d:%d:%d \n",lt->tm_year+1900, lt->tm_mon, lt->tm_mday,
		         lt->tm_hour, lt->tm_min, lt->tm_sec);			//������
		Sleep(100);
	}
	getchar();
	return 0;
}
