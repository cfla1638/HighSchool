#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#define MAPHIGHT 25	 //��ͼ�ĸ߶�
#define MAPLENGTH 60 //��ͼ�Ŀ��
#define SNAKESIZE 50 //�ߵ�������

//ʳ��Ľṹ��
struct
{
	int x; //ʳ��ĺ�����
	int y; //ʳ���������
} food;

//�ߵĽṹ��
struct
{
	//��¼һ���ߵ�λ��
	int x[SNAKESIZE];
	int y[SNAKESIZE];
	int length; //Ŀǰ�ߵĳ���
	int speed;	//�ߵ��ٶ�
} snake;

//ȫ�ֱ���
int input = 'a';
int key = 'a';		//��ʼ���ƶ�����
int changeFlag = 0; //�ߵı仯���

/*
�������
ʳ���
Ȧ�ب~
*/

//��������
void gotoxy(int x, int y);
void inimap();
void keydown(); //��������
void createfood();
int snakestatus();
void automove();

int main()
{
lab:
	system("cls");
	inimap();
	while (1)
	{
		createfood();
		Sleep(snake.speed);
		automove();
		if (!snakestatus())
		{
			break;
		}
	}
	gotoxy(MAPLENGTH / 2, MAPHIGHT / 2 - 1);
	printf("��Ϸ����");
	gotoxy(MAPLENGTH / 2, MAPHIGHT / 2);
	printf("�÷�:%d", snake.length - 5);
	gotoxy(MAPLENGTH / 2, MAPHIGHT / 2 + 1);
	printf("��������¿�ʼ��Ϸ");
	getch();
	goto lab;
	return 0;
}

// gotoxy����
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(handle, coord);
}

void inimap()
{

	input = 'a';
	key = 'a';		//��ʼ���ƶ�����
	changeFlag = 0; //�ߵı仯���
	//��ʼ���߽�
	//#define MAPHIGHT 30//��ͼ�ĸ߶�
	//#define MAPLENGTH 30 //��ͼ�Ŀ��

	//��������߽�
	int i, j, k;
	for (i = 0; i <= MAPHIGHT; i++)
	{
		gotoxy(0, i);
		printf("�~ ");
		gotoxy(MAPLENGTH, i);
		printf("�~ ");

		//��������߽�
	}
	for (j = 0; j <= MAPLENGTH; j += 2) //��Ϊ �~ռ�������ַ�
	{
		gotoxy(j, 0);
		printf("�~");
		gotoxy(j, MAPHIGHT);
		printf("�~");
	}

	//��ʼ���ߵ�����
	snake.length = 5; //��ʼ���ߵĳ���
	snake.speed = 50; //��ʼ���ߵ��ٶ�

	gotoxy(MAPLENGTH + 2, 1);
	printf("��õ��ٶ�:%d", 300 - snake.speed);
	gotoxy(MAPLENGTH + 2, 3);
	printf("�÷�:%d", snake.length - 5);

	//��ʼ����ͷ�����꣬ʹ������Ļ���м�
	snake.x[0] = MAPLENGTH / 2;
	snake.y[0] = MAPHIGHT / 2;
	//����ͷ
	gotoxy(snake.x[0], snake.y[0]);
	printf("�~");
	//���ߵ�����
	for (k = 1; k <= snake.length; k++)
	{
		snake.x[k] = snake.x[k - 1]; //ԭ���� snake.x[k]=snake.x[k-1]+2;
		snake.y[k] = snake.y[k - 1];
		gotoxy(snake.x[k], snake.y[k]);
		printf("�~");
	}

	//��ʼ��ʳ��
	srand((unsigned int)time(NULL)); //�������������
	//�������ʳ�������
	while (1)
	{
		food.x = rand() % (MAPLENGTH - 4) + 2;
		if (food.x % 2 == 0)
		{
			break;
		}
	}
	food.y = rand() % (MAPHIGHT - 2) + 1;
	gotoxy(food.x, food.y); //����ʳ������
	printf("��");			//����ʳ��
}

void keydown()
{

	int i;
	//�ް����Ĳ���
	if (_kbhit())
	{
		fflush(stdin); //��ջ��������а����ͽ���
		input = _getch();
	}
	if (!(key == 'a' && input == 'd' || key == 'w' && input == 's' || key == 's' && input == 'w' || key == 'd' && input == 'a'))
	{
		key = input;
	}
	//���ƶ�
	//����ԭ�������һ��
	if (!changeFlag)
	{
		gotoxy(snake.x[snake.length - 1], snake.y[snake.length - 1]);
		printf("  ");
	}
	for (i = snake.length - 1; i > 0; i--)
	{
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1];
	}
	//�ƶ�����Ĵ���
	//�ı���ͷ����
	switch (key)
	{
	case 'W':
	case 'w':
		snake.y[0]--;
		break;
	case 'A':
	case 'a':
		snake.x[0] -= 2;
		break;
	case 'S':
	case 's':
		snake.y[0]++;
		break;
	case 'D':
	case 'd':
		snake.x[0] += 2;
		break;
	}
	gotoxy(snake.x[0], snake.y[0]);
	printf("�~");
	gotoxy(MAPLENGTH + 2, 5);
	printf("X:%d", snake.x[0]);
	gotoxy(MAPLENGTH + 2, 6);
	printf("Y:%d ", snake.y[0]);
	changeFlag = 0;
	gotoxy(MAPHIGHT + 2, 0);
}

void createfood()
{
	//�ж��߳�ʳ��
	if (snake.x[0] == food.x && snake.y[0] == food.y)
	{
		srand((unsigned int)time(NULL));
		//������ʳ�ﲻ�����ߵ�����
		while (1)
		{
			int flag, k;
			flag = 1;
			food.x = rand() % (MAPLENGTH - 4) + 2;
			food.y = rand() % (MAPHIGHT - 2) + 1;
			//������ʳ�ﲻ����������
			for (k = 0; k < snake.length; k++)
			{
				if (snake.x[k] == food.x && snake.y[k] == food.y)
				{
					flag = 0;
					break;
				}
			}
			if (flag && food.x % 2 == 0)
			{
				break;
			}
		}
		gotoxy(food.x, food.y);
		printf("��");
		// snake.length++;
		if (snake.length == 6)
		{
			snake.speed = 50;
		}
		gotoxy(MAPLENGTH + 2, 1);
		printf("��õ��ٶ�:%d", 300 - snake.speed);
		gotoxy(MAPLENGTH + 2, 3);
		printf("�÷�:%d", snake.length - 5);
		changeFlag = 1;
	}
}

int snakestatus()
{
	int k;
	//��ײǽ
	if (snake.x[0] == 0 || snake.x[0] == MAPLENGTH - 1 || snake.y[0] == 0 || snake.y[0] == MAPHIGHT)
	{
		return 0;
	}
	//�߲���ײ�Լ�
	/*
	for(k=1; k<snake.length; k++)
		{
			if(snake.x[0]==snake.x[k] && snake.y[0]==snake.y[k])
				{
					return 0;
				}
		}
		*/
	return 1;
}

void automove()
{
	int i;
	/*
	//���ƶ�
	if(!changeFlag)
	{
		gotoxy(snake.x[snake.length-1],snake.y[snake.length-1]);
		printf("  ");
	}
	*/
	//ʹ�ߵĳ��Ȳ�����
	//--------------------------
	gotoxy(snake.x[snake.length - 1], snake.y[snake.length - 1]);
	printf("  ");
	//--------------------------
	for (i = snake.length - 1; i > 0; i--)
	{
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1];
	}

	//----------�Զ�Ѱ·----------------
	if (snake.x[0] < food.x)
	{
		key = 'd';
	}
	else if (snake.x[0] > food.x)
	{
		key = 'a';
	}
	else
	{
		if (snake.y[0] < food.y)
		{
			key = 's';
		}
		else if (snake.y[0] > food.y)
		{
			key = 'w';
		}
	}
	//-----------------------------------
	switch (key)
	{
	case 'W':
	case 'w':
		snake.y[0]--;
		break;
	case 'A':
	case 'a':
		snake.x[0] -= 2;
		break;
	case 'S':
	case 's':
		snake.y[0]++;
		break;
	case 'D':
	case 'd':
		snake.x[0] += 2;
		break;
	}
	gotoxy(snake.x[0], snake.y[0]);
	printf("�~");
	gotoxy(MAPLENGTH + 2, 5);
	printf("X:%d", snake.x[0]);
	gotoxy(MAPLENGTH + 2, 6);
	printf("Y:%d", snake.y[0]);
	changeFlag = 0;
	gotoxy(MAPHIGHT + 2, 0);
}
