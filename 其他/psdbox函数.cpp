#include <cstdio>
#include <conio.h>
#define SIZE 100
using namespace std;
char ch[SIZE];

void psdbox();

int main()
{
	printf("������ʵ��\n֧��backspace\n");
	printf("cin>>");
	psdbox();
	printf("\n");
	printf("output:\n%s", ch);
	getch();
	return 0;
}

void psdbox()
{
	int i = 0;
	while (ch[i] = getch())
	{
		if (ch[i] == 8) //�������backspace
		{
			ch[i - 1] = 0; //����
			i = i - 1;	   //�˸�
			printf("\b \b");
			continue;
		}
		if (ch[i] == 13) //�س��ļ�ֵ��13
		{
			ch[i] = 0;
			break;
		}
		printf("*");
		i++;
	}
}
