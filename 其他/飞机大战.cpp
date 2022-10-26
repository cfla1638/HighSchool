#include <cstdio>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <iostream>

#define MAXQSIZE 100 //队列的最大节点数
#define MAPSIZE 2500 //图的最大节点数
#define OK 1		 //函数返回状态“成功”
#define ERROR 0		 //“失败”

#define MAX_ENEMY_COUNT 10 //地图上的敌机最大数目
#define MAP_LENTH 40	   //地图的长度
#define PERR(bSuccess, api)                                                                      \
	{                                                                                            \
		if (!(bSuccess))                                                                         \
			printf("%s:Error %d from %s on line %d\n", __FILE__, GetLastError(), api, __LINE__); \
	}
using namespace std;

typedef int Status; //函数返回状态类型

//全局变量
bool visited[MAPSIZE]; // bfs的标记数组

int key = 'a';	   //用来控制键盘输入
int gamePoint = 0; //得分
int gameTime = 0;  //游戏时间轴

//结构体
typedef struct //位置
{
	int x;
	int y;
} Pos;

typedef struct //自己的飞机
{
	Pos pos;
	bool ChangeFlag;
} Aircraft;

typedef struct //敌机
{
	Pos pos;		 //敌机的位置
	bool existFlag;	 //敌机是否存在
	int rebirthTime; //如果敌机死亡，则下次重生的时间
} Enemy[MAX_ENEMY_COUNT];

typedef struct //所有的敌机
{
	Enemy lists;
} Enemys;

//************************************************************
//用于放大招的广度优先搜索
//分布是邻接表的结构体和队列
typedef struct ArcNode
{
	int adjvex;
	struct ArcNode *nextarc;
} ArcNode;

typedef struct VNode
{
	int seqNum;
	Pos pos;
	ArcNode *firstarc;
} VNode, AdjList[MAPSIZE];

typedef struct
{
	AdjList vertices;
	int vexnum, arcnum;
} Map;

typedef struct
{
	int *base;
	int front;
	int rear;
} Queue;
//************************************************************

//函数声明
//主要使用的函数
void StartMenu();											  //显示初始界面
void InitEnemys(Enemys &enemys);							  //初始化敌机
void EnemyMove(Enemys &enemys);								  //敌机状态刷新（移动
void InitAircraft(Aircraft &aircraft);						  //初始化自己的飞机
void AircraftMove(Aircraft &aircraft, Enemys &enemys, Map M); //自己飞机的状态刷新（移动
void AircraftShot(Aircraft aircraft, Enemys &enemys);		  //射击
void BigSkill(Aircraft aircraft, Map M, Enemys &enemys);	  //放大招

//放大招所使用的函数
Status InitMap(Map &M, int len, int wid); //初始化地图
Status InitQueue(Queue &Q);				  //初始化队列
void BFS(Map M, int v);					  //广度优先搜索
void createArc(Map &M, int i, int j);	  //创建边
bool QueueEmpty(Queue Q);				  //判断队列是否为空
void DeQueue(Queue &Q, int &u);			  //出队
int EnQueue(Queue &Q, int e);			  //入队
int FirstAdjVex(Map M, int v);			  //返回某节点的第一个临界点
int getX(int seqNum, int len);			  //返回某顺序号在地图上的坐标（x
int getY(int seqNum, int len);			  //返回某顺序号在地图上的坐标（y

//辅助函数
void gotoxy(int x, int y);						 //光标移动
void MyCls(HANDLE);								 //清屏函数(辅助)
void clrscr();									 //清屏函数（本体）
int ChangeAircraftPos(Aircraft aircraft, Map M); //将坐标装换为顺序号

//主函数

int main(int argc, char const *argv[])
{
	//四个元素：地图、队列、我机、敌机
	Map M;
	Queue Q;
	Enemys enemys;
	Aircraft aircraft;

	//初始化地图和队列
	InitMap(M, MAP_LENTH, 25);
	InitQueue(Q);

	//进入初始界面，初始化飞机
	StartMenu();
	InitEnemys(enemys);
	InitAircraft(aircraft);

	//进入游戏主循环
	while (true)
	{
		//有两个 AircraftMove() 函数是为了让游戏更加流畅
		AircraftMove(aircraft, enemys, M);
		EnemyMove(enemys);
		AircraftMove(aircraft, enemys, M);
	}

	return 0;
}

void BigSkill(Aircraft aircraft, Map M, Enemys &enemys)
{
	BFS(M, ChangeAircraftPos(aircraft, M));
	for (int i = 0; i < MAPSIZE; ++i)
	{
		visited[i] = false;
	}
	int lifeCount = 0;
	for (int i = 0; i < MAX_ENEMY_COUNT; ++i)
	{
		if (enemys.lists[i].existFlag)
		{
			enemys.lists[i].existFlag = false;
			enemys.lists[i].pos.y = 0;
			srand(i);
			enemys.lists[i].rebirthTime = gameTime + rand() % 60 + 1;
			srand(i + 21);
			enemys.lists[i].pos.x = rand() % MAP_LENTH;
			lifeCount++;
		}
	}
	gamePoint = gamePoint + lifeCount;
	clrscr();
	for (int i = 0; i < 25; ++i)
	{
		gotoxy(MAP_LENTH, i);
		cout << "$";
	}
	gotoxy(45, 5);
	cout << "gamePoint:" << gamePoint;
}

int ChangeAircraftPos(Aircraft aircraft, Map M)
{
	for (int i = 0; i < MAPSIZE; ++i)
	{
		if (getX(i, MAP_LENTH) == aircraft.pos.x && getY(i, MAP_LENTH) == aircraft.pos.y)
		{
			return i;
		}
	}
}

void AircraftShot(Aircraft aircraft, Enemys &enemys)
{
	int y = aircraft.pos.y - 1;

	for (int i = 0; i < MAX_ENEMY_COUNT; ++i)
	{
		//击中敌机
		if (enemys.lists[i].pos.x == aircraft.pos.x && enemys.lists[i].existFlag)
		{
			gamePoint++;
			enemys.lists[i].existFlag = false; //敌机销毁

			srand((unsigned int)time(NULL));
			enemys.lists[i].rebirthTime = gameTime + rand() % 60 + 1; //设置重生时间

			gotoxy(45, 5);
			cout << "gamePoint:" << gamePoint;
		}
	}

	for (int i = 0; i < aircraft.pos.y; ++i)
	{
		gotoxy(aircraft.pos.x, y);
		cout << "!";
		y--;
	}
	Sleep(200);

	y = aircraft.pos.y - 1;
	for (int i = 0; i < aircraft.pos.y; ++i)
	{
		gotoxy(aircraft.pos.x, y);
		cout << " ";
		y--;
	}
}

void AircraftMove(Aircraft &aircraft, Enemys &enemys, Map M)
{
	if (_kbhit())
	{
		fflush(stdin);
		key = _getch();
		aircraft.ChangeFlag = true;
	}
	if (aircraft.ChangeFlag)
	{
		gotoxy(aircraft.pos.x, aircraft.pos.y);
		cout << " ";
		switch (key)
		{
		case 'W':
		case 'w':
			aircraft.pos.y--;
			break;
		case 'A':
		case 'a':
			aircraft.pos.x--;
			break;
		case 'S':
		case 's':
			aircraft.pos.y++;
			break;
		case 'D':
		case 'd':
			aircraft.pos.x++;
			break;
		case 'J':
		case 'j':
			AircraftShot(aircraft, enemys);
			break;
		case 'K':
		case 'k':
			BigSkill(aircraft, M, enemys);
			break;
		}
		gotoxy(aircraft.pos.x, aircraft.pos.y);
		cout << "#";
		aircraft.ChangeFlag = false;
	}
}

void InitAircraft(Aircraft &aircraft)
{
	aircraft.pos.x = MAP_LENTH / 2;
	aircraft.pos.y = 20;
	gotoxy(aircraft.pos.x, aircraft.pos.y);
	cout << "#";
}

void EnemyMove(Enemys &enemys)
{
	gameTime++;
	Sleep(1000);

	for (int i = 0; i < MAX_ENEMY_COUNT; ++i)
	{
		if (enemys.lists[i].existFlag)
		{
			gotoxy(enemys.lists[i].pos.x, enemys.lists[i].pos.y);
			cout << " ";
			enemys.lists[i].pos.y++;
			gotoxy(enemys.lists[i].pos.x, enemys.lists[i].pos.y);
			cout << "@";
		}
		else
		{
			if (enemys.lists[i].rebirthTime == gameTime) //重生
			{
				enemys.lists[i].existFlag = true;
				srand((unsigned int)time(NULL));
				enemys.lists[i].pos.x = rand() % MAP_LENTH;
				enemys.lists[i].pos.y = 0;
				gotoxy(enemys.lists[i].pos.x, enemys.lists[i].pos.y);
				cout << "@";
			}
		}

		if (enemys.lists[i].pos.y > 20)
		{
			gotoxy(enemys.lists[i].pos.x, enemys.lists[i].pos.y);
			cout << " ";
			enemys.lists[i].pos.y = 0;
			enemys.lists[i].existFlag = true;
		}
	}
}

void InitEnemys(Enemys &enemys)
{
	for (int i = 0; i < MAX_ENEMY_COUNT; ++i)
	{
		enemys.lists[i].pos.x = 2 + 4 * i;
		enemys.lists[i].pos.y = 0;
		enemys.lists[i].existFlag = false;
		srand(i);
		enemys.lists[i].rebirthTime = gamePoint + rand() % 60 + 1;
	}
}

void StartMenu()
{
	gotoxy(32, 0);
	cout << "Aircraft Wars";
	gotoxy(8, 2);
	cout << "1. FBI WARNNING : Federal Law provides severe civil and criminal";
	gotoxy(11, 3);
	cout << "penalties for the unauthorized reproduction, distribution, or";
	gotoxy(11, 4);
	cout << "exhibition of copyrighted motion pictures (Title 17, United S";
	gotoxy(11, 5);
	cout << "tatus Code, Sections 501 and 508). The Federal Bureau of Inve";
	gotoxy(11, 6);
	cout << "stigation inversgate allegations of criminal copyright infrin";
	gotoxy(11, 7);
	cout << "gement (Title 17, United States Code, Section 506)";
	gotoxy(8, 9);
	cout << "2. Operation : Use 'w', 'a', 's', 'd' to move, 'j' to shot.";
	gotoxy(8, 11);
	cout << "3. Type anything to start your game ...";
	getch();
	clrscr();
	for (int i = 0; i < 25; ++i)
	{
		gotoxy(MAP_LENTH, i);
		cout << "$";
	}
	gotoxy(45, 5);
	cout << "gamePoint:" << gamePoint;
}

void clrscr(void)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	MyCls(hStdOut);
	return;
}

void MyCls(HANDLE hConsole)
{
	COORD coordScreen = {0, 0};
	BOOL bSuccess;
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
	PERR(bSuccess, "GetConsoleScreenBufferInfo");
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	bSuccess = FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
	PERR(bSuccess, "FillConsoleOutputCharacter");
	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
	PERR(bSuccess, "ConsoleScreenBufferInfo");
	bSuccess = FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	PERR(bSuccess, "FillConsoleOutputAttribute");
	bSuccess = SetConsoleCursorPosition(hConsole, coordScreen);
	PERR(bSuccess, "SetConsoleCursorPosition");
	return;
}

void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(handle, coord);
}

//放大招使用的函数:BFS广度优先搜索

Status InitMap(Map &M, int len, int wid)
{
	int sum;
	sum = len * wid;
	M.vexnum = sum;
	M.arcnum = len * (wid - 1) + wid * (len - 1);
	for (int i = 0; i < M.vexnum; i++)
	{
		M.vertices[i].seqNum = i;
		M.vertices[i].firstarc = NULL;
		M.vertices[i].pos.x = getX(M.vertices[i].seqNum, len);
		M.vertices[i].pos.y = getY(M.vertices[i].seqNum, len);
	}
	int map[len][wid];
	int k = 0;
	for (int i = 0; i < wid; i++)
	{
		for (int j = 0; j < len; j++)
		{
			map[j][i] = k;
			k++;
		}
	}
	for (int i = 0; i < wid; i++)
	{
		for (int j = 0; j < len - 1; j++)
		{
			createArc(M, map[j][i], map[j + 1][i]);
		}
	}
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < wid - 1; j++)
		{
			createArc(M, map[i][j], map[i][j + 1]);
		}
	}
	return OK;
}

int getX(int seqNum, int len)
{
	return (seqNum % len);
}

int getY(int seqNum, int len)
{
	int i = 0;
	while (seqNum >= len)
	{
		seqNum = seqNum - len;
		i++;
	}
	return i;
}

void createArc(Map &M, int i, int j)
{
	ArcNode *p1, *p2;
	p1 = new ArcNode;
	p2 = new ArcNode;

	p1->adjvex = j;
	p2->adjvex = i;

	p1->nextarc = M.vertices[i].firstarc;
	p2->nextarc = M.vertices[j].firstarc;

	M.vertices[i].firstarc = p1;
	M.vertices[j].firstarc = p2;
}

int EnQueue(Queue &Q, int e)
{
	if ((Q.rear + 1) % MAXQSIZE == Q.front)
	{
		return 0;
	}
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
}

void DeQueue(Queue &Q, int &u)
{
	u = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
}

bool QueueEmpty(Queue Q)
{
	if (Q.rear == Q.front)
	{
		return true;
	}
	return false;
}

int FirstAdjVex(Map M, int v)
{
	return M.vertices[v].firstarc->adjvex;
}

int NextAdjVex(Map M, int u, int w)
{
	ArcNode *temp;

	temp = M.vertices[u].firstarc;
	if (temp->adjvex == w)
	{
		return temp->nextarc->adjvex;
	}
	temp = temp->nextarc;
	while (temp->nextarc != NULL)
	{
		if (temp->adjvex == w)
		{
			return temp->nextarc->adjvex;
		}
		temp = temp->nextarc;
	}
	return -1;
}

Status InitQueue(Queue &Q)
{
	Q.base = new int[MAXQSIZE];
	Q.front = Q.rear = 0;
	return OK;
}

void BFS(Map M, int v)
{
	int u;
	int w;
	Queue Q;
	Sleep(100);
	gotoxy(M.vertices[v].pos.x, M.vertices[v].pos.y);
	cout << "#";
	visited[v] = true;
	InitQueue(Q);
	EnQueue(Q, v);
	while (!QueueEmpty(Q))
	{
		DeQueue(Q, u);
		for (w = FirstAdjVex(M, u); w >= 0; w = NextAdjVex(M, u, w))
		{
			if (!visited[w])
			{
				gotoxy(M.vertices[w].pos.x, M.vertices[w].pos.y);
				cout << "*";
				visited[w] = true;
				EnQueue(Q, w);
			}
		}
	}
}
