#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s on line %d\n", __FILE__,GetLastError(), api, __LINE__);}

void MyCls(HANDLE);  
void clrscr();		//清屏函数 
int PagePrint(const char* path);

int main()
{
	
	PagePrint("C://CodeGraph.txt");
	printf("播放完毕");
	getch();
	clrscr();
	
	return 0;
}

int PagePrint(const char* path)
{
	int i=0;
	FILE *fp=fopen(path,"r");
	if(!fp)
	{
		printf("File Open Error!");
		return 0;
	}
	char buffer[128]={};
	char *error;
	do
	{
		error=fgets(buffer,sizeof(buffer),fp);		//读到 EOF/错误 会返回NULL       
		printf("%s",buffer);
		strcpy(buffer,"");
		i++;
		if(i%12==0)
		{
			Sleep(1000);
			clrscr();
		}
	}
	while(error!=NULL);
	fclose(fp);
	return 0;
}


void clrscr(void)
{
	HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
	MyCls(hStdOut);
	return;
}

void MyCls(HANDLE hConsole)
{
	COORD coordScreen={0,0};//设置清屏后光标返回的屏幕左上角坐标
	BOOL bSuccess;
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;//保存缓冲区信息
	DWORD dwConSize;//当前缓冲区可容纳的字符数
	bSuccess=GetConsoleScreenBufferInfo(hConsole,&csbi);//获得缓冲区信息
	PERR(bSuccess,"GetConsoleScreenBufferInfo");
	dwConSize=csbi.dwSize.X * csbi.dwSize.Y;//缓冲区容纳字符数目
	//用空格填充缓冲区
	bSuccess=FillConsoleOutputCharacter(hConsole,(TCHAR)' ',dwConSize,coordScreen,&cCharsWritten);
	PERR(bSuccess,"FillConsoleOutputCharacter");
	bSuccess=GetConsoleScreenBufferInfo(hConsole,&csbi);//获得缓冲区信息
	PERR(bSuccess,"ConsoleScreenBufferInfo");
	//填充缓冲区属性
	bSuccess=FillConsoleOutputAttribute(hConsole,csbi.wAttributes,dwConSize,coordScreen,&cCharsWritten);
	PERR(bSuccess,"FillConsoleOutputAttribute");
	//光标返回屏幕左上角坐标
	bSuccess=SetConsoleCursorPosition(hConsole,coordScreen);
	PERR(bSuccess,"SetConsoleCursorPosition");
	return;
}

