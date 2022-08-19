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
	//隐藏光标 
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
	//结束 
	time_t t;
	struct tm * lt;
	while(1)
	{
		time (&t);												//获取Unix时间戳。
		lt = localtime (&t);									//转为时间结构。
		Gotoxy(0,0);
		printf ( "%d/%d/%d %d:%d:%d \n",lt->tm_year+1900, lt->tm_mon, lt->tm_mday,
		         lt->tm_hour, lt->tm_min, lt->tm_sec);			//输出结果
		Sleep(100);
	}
	getchar();
	return 0;
}
