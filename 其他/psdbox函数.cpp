#include <cstdio>
#include <conio.h>
#define SIZE 100
using namespace std;
char ch[SIZE];

void psdbox();

int main()
{
	printf("密码栏实现\n支持backspace\n");
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
		if (ch[i] == 8) //如果输入backspace
		{
			ch[i - 1] = 0; //清零
			i = i - 1;	   //退格
			printf("\b \b");
			continue;
		}
		if (ch[i] == 13) //回车的键值是13
		{
			ch[i] = 0;
			break;
		}
		printf("*");
		i++;
	}
}
