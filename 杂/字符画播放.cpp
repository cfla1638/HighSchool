#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s on line %d\n", __FILE__,GetLastError(), api, __LINE__);}

void MyCls(HANDLE);  
void clrscr();		//�������� 
int PagePrint(const char* path);

int main()
{
	
	PagePrint("C://CodeGraph.txt");
	printf("�������");
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
		error=fgets(buffer,sizeof(buffer),fp);		//���� EOF/���� �᷵��NULL       
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
	COORD coordScreen={0,0};//�����������귵�ص���Ļ���Ͻ�����
	BOOL bSuccess;
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;//���滺������Ϣ
	DWORD dwConSize;//��ǰ�����������ɵ��ַ���
	bSuccess=GetConsoleScreenBufferInfo(hConsole,&csbi);//��û�������Ϣ
	PERR(bSuccess,"GetConsoleScreenBufferInfo");
	dwConSize=csbi.dwSize.X * csbi.dwSize.Y;//�����������ַ���Ŀ
	//�ÿո���仺����
	bSuccess=FillConsoleOutputCharacter(hConsole,(TCHAR)' ',dwConSize,coordScreen,&cCharsWritten);
	PERR(bSuccess,"FillConsoleOutputCharacter");
	bSuccess=GetConsoleScreenBufferInfo(hConsole,&csbi);//��û�������Ϣ
	PERR(bSuccess,"ConsoleScreenBufferInfo");
	//��仺��������
	bSuccess=FillConsoleOutputAttribute(hConsole,csbi.wAttributes,dwConSize,coordScreen,&cCharsWritten);
	PERR(bSuccess,"FillConsoleOutputAttribute");
	//��귵����Ļ���Ͻ�����
	bSuccess=SetConsoleCursorPosition(hConsole,coordScreen);
	PERR(bSuccess,"SetConsoleCursorPosition");
	return;
}

