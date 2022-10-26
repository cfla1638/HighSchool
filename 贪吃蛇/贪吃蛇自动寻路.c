#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#define MAPHIGHT 25	 //地图的高度
#define MAPLENGTH 60 //地图的宽度
#define SNAKESIZE 50 //蛇的最大节数

//食物的结构体
struct
{
	int x; //食物的横坐标
	int y; //食物的纵坐标
} food;

//蛇的结构体
struct
{
	//记录一节蛇的位置
	int x[SNAKESIZE];
	int y[SNAKESIZE];
	int length; //目前蛇的长度
	int speed;	//蛇的速度
} snake;

//全局变量
int input = 'a';
int key = 'a';		//初始化移动方向
int changeFlag = 0; //蛇的变化标记

/*
特殊符号
食物⊙
圈地▇
*/

//函数声明
void gotoxy(int x, int y);
void inimap();
void keydown(); //按键操作
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
	printf("游戏结束");
	gotoxy(MAPLENGTH / 2, MAPHIGHT / 2);
	printf("得分:%d", snake.length - 5);
	gotoxy(MAPLENGTH / 2, MAPHIGHT / 2 + 1);
	printf("任意键重新开始游戏");
	getch();
	goto lab;
	return 0;
}

// gotoxy函数
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
	key = 'a';		//初始化移动方向
	changeFlag = 0; //蛇的变化标记
	//初始化边界
	//#define MAPHIGHT 30//地图的高度
	//#define MAPLENGTH 30 //地图的宽度

	//画出竖向边界
	int i, j, k;
	for (i = 0; i <= MAPHIGHT; i++)
	{
		gotoxy(0, i);
		printf("▇ ");
		gotoxy(MAPLENGTH, i);
		printf("▇ ");

		//画出横向边界
	}
	for (j = 0; j <= MAPLENGTH; j += 2) //因为 ▇占用两个字符
	{
		gotoxy(j, 0);
		printf("▇");
		gotoxy(j, MAPHIGHT);
		printf("▇");
	}

	//初始化蛇的属性
	snake.length = 5; //初始化蛇的长度
	snake.speed = 50; //初始化蛇的速度

	gotoxy(MAPLENGTH + 2, 1);
	printf("获得的速度:%d", 300 - snake.speed);
	gotoxy(MAPLENGTH + 2, 3);
	printf("得分:%d", snake.length - 5);

	//初始化蛇头的坐标，使其在屏幕的中间
	snake.x[0] = MAPLENGTH / 2;
	snake.y[0] = MAPHIGHT / 2;
	//画蛇头
	gotoxy(snake.x[0], snake.y[0]);
	printf("▇");
	//画蛇的身子
	for (k = 1; k <= snake.length; k++)
	{
		snake.x[k] = snake.x[k - 1]; //原来是 snake.x[k]=snake.x[k-1]+2;
		snake.y[k] = snake.y[k - 1];
		gotoxy(snake.x[k], snake.y[k]);
		printf("▇");
	}

	//初始化食物
	srand((unsigned int)time(NULL)); //播撒随机数种子
	//随机生成食物的坐标
	while (1)
	{
		food.x = rand() % (MAPLENGTH - 4) + 2;
		if (food.x % 2 == 0)
		{
			break;
		}
	}
	food.y = rand() % (MAPHIGHT - 2) + 1;
	gotoxy(food.x, food.y); //设置食物坐标
	printf("⊙");			//放置食物
}

void keydown()
{

	int i;
	//无按键的操作
	if (_kbhit())
	{
		fflush(stdin); //清空缓存区？有按键就接受
		input = _getch();
	}
	if (!(key == 'a' && input == 'd' || key == 'w' && input == 's' || key == 's' && input == 'w' || key == 'd' && input == 'a'))
	{
		key = input;
	}
	//蛇移动
	//擦掉原来的最后一个
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
	//移动方向的处理
	//改变蛇头方向
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
	printf("▇");
	gotoxy(MAPLENGTH + 2, 5);
	printf("X:%d", snake.x[0]);
	gotoxy(MAPLENGTH + 2, 6);
	printf("Y:%d ", snake.y[0]);
	changeFlag = 0;
	gotoxy(MAPHIGHT + 2, 0);
}

void createfood()
{
	//判断蛇吃食物
	if (snake.x[0] == food.x && snake.y[0] == food.y)
	{
		srand((unsigned int)time(NULL));
		//产生的食物不能在蛇的身上
		while (1)
		{
			int flag, k;
			flag = 1;
			food.x = rand() % (MAPLENGTH - 4) + 2;
			food.y = rand() % (MAPHIGHT - 2) + 1;
			//产生的食物不能在蛇身上
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
		printf("⊙");
		// snake.length++;
		if (snake.length == 6)
		{
			snake.speed = 50;
		}
		gotoxy(MAPLENGTH + 2, 1);
		printf("获得的速度:%d", 300 - snake.speed);
		gotoxy(MAPLENGTH + 2, 3);
		printf("得分:%d", snake.length - 5);
		changeFlag = 1;
	}
}

int snakestatus()
{
	int k;
	//蛇撞墙
	if (snake.x[0] == 0 || snake.x[0] == MAPLENGTH - 1 || snake.y[0] == 0 || snake.y[0] == MAPHIGHT)
	{
		return 0;
	}
	//蛇不能撞自己
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
	//蛇移动
	if(!changeFlag)
	{
		gotoxy(snake.x[snake.length-1],snake.y[snake.length-1]);
		printf("  ");
	}
	*/
	//使蛇的长度不增加
	//--------------------------
	gotoxy(snake.x[snake.length - 1], snake.y[snake.length - 1]);
	printf("  ");
	//--------------------------
	for (i = snake.length - 1; i > 0; i--)
	{
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1];
	}

	//----------自动寻路----------------
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
	printf("▇");
	gotoxy(MAPLENGTH + 2, 5);
	printf("X:%d", snake.x[0]);
	gotoxy(MAPLENGTH + 2, 6);
	printf("Y:%d", snake.y[0]);
	changeFlag = 0;
	gotoxy(MAPHIGHT + 2, 0);
}
