#include<iostream>
#include<windows.h>
#include<conio.h>
#define MAPSIZE 2500	//地图的大小即 
#define MAXQSIZE 100
#define OK 1
#define ERROR 0
using namespace std;
typedef int Status;

//标记数组 
bool visited[MAPSIZE];

//结构体
typedef struct pos
{
	int x,y;
}Pos;
typedef struct ArcNode
{
	int adjvex;		//指向的顶点的位置
	struct ArcNode *nextarc; 
}ArcNode;

typedef struct VNode
{
	int seqNum;		//序号
	Pos pos;		//位置 
	ArcNode *firstarc;
} VNode,AdjList[MAPSIZE];

typedef struct
{
	AdjList vertices;
	int vexnum,arcnum;
}Map;

typedef struct
{
	int *base;
	int front;
	int rear;
}Queue;

//函数声明
Status InitMap(Map &M,int len,int wid);
void BFS(Map M,int v); 
void DFS(Map M,int v); 
//以下为辅助函数 
void createArc(Map &M,int i,int j);
void gotoxy(int x,int y); 
int getX(int seqNum,int len);
int getY(int seqNum,int len);
bool QueueEmpty(Queue Q);
int EnQueue(Queue &Q,int e);
void DeQueue(Queue &Q,int &u);
int FirstAdjVex(Map M,int v);
Status InitQueue(Queue &Q);

//主函数
int main()
{
	Map M;
	cout<<"任意键开始BFS...";
	getch();
	system("cls"); 
	InitMap(M,50,25);
	BFS(M,0);
	getch();
	return 0;
} 

Status InitMap(Map &M,int len,int wid)
{
	int sum;
	sum=len*wid;
	M.vexnum=sum;
	//弧的数目=[长*(宽-1)]+[宽*(长-1)] 
	M.arcnum=len*(wid-1)+wid*(len-1);
	//初始化顶点信息 
	for(int i=0;i<M.vexnum;i++)
	{
		M.vertices[i].seqNum=i;
		M.vertices[i].firstarc=NULL;
		//对其位置进行初始化 
		M.vertices[i].pos.x=getX(M.vertices[i].seqNum,len);
		M.vertices[i].pos.y=getY(M.vertices[i].seqNum,len);
	}
	//使用二维数组模拟图 
	int map[len][wid];
	int k=0;
	for(int i=0;i<wid;i++)
	{
		for(int j=0;j<len;j++)
		{
			map[j][i]=k;
			k++;
		}
	} 
	//生成边 
	for(int i=0;i<wid;i++)
	{
		for(int j=0;j<len-1;j++)
		{
			createArc(M,map[j][i],map[j+1][i]);
		}
	}
	for(int i=0;i<len;i++)
	{
		for(int j=0;j<wid-1;j++)
		{
			createArc(M,map[i][j],map[i][j+1]);
		}
	}
	return OK;
}

int getX(int seqNum,int len)
{
	return (seqNum%len);
}

int getY(int seqNum,int len)
{
	int i=0;
	while(seqNum>=len)
	{
		seqNum=seqNum-len;
		i++;
	}
	return i;
}

void createArc(Map &M,int i,int j)
{
	ArcNode *p1,*p2;
	p1=new ArcNode;
	p2=new ArcNode;
	
	p1->adjvex=j;
	p2->adjvex=i;
	//插入
	p1->nextarc=M.vertices[i].firstarc;
	p2->nextarc=M.vertices[j].firstarc;
	
	M.vertices[i].firstarc=p1;
	M.vertices[j].firstarc=p2;
}

void gotoxy(int x,int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(handle,coord);
}

int EnQueue(Queue &Q,int e)
{
	if((Q.rear + 1) % MAXQSIZE == Q.front)
	{
		return 0; 
	} 
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
}

void DeQueue(Queue &Q,int &u)
{
	u = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
}

bool QueueEmpty(Queue Q)
{
	if(Q.rear==Q.front)
	{
		return true;
	}
	return false;
}

int FirstAdjVex(Map M,int v)
{
	return M.vertices[v].firstarc->adjvex;
}

int NextAdjVex(Map M,int u,int w)
{ 
	ArcNode *temp;
	//边表的最后一个节点的nextarc指针指向该边表的第一个节点；即G.vertices[u].firstarc 
	temp=M.vertices[u].firstarc;
	if(temp->adjvex==w)
	{
		return temp->nextarc->adjvex;
	}
	temp=temp->nextarc; 
	while(temp->nextarc!=NULL)
	{
		if(temp->adjvex==w)
		{
			return temp->nextarc->adjvex;
		}
		temp=temp->nextarc;		//继续向下查找 
	}
	return -1;
}

Status InitQueue(Queue &Q)
{
	Q.base=new int[MAXQSIZE];
	Q.front=Q.rear=0;
	return OK;
}

void BFS(Map M,int v)
{
	int u;		//出队的容器 
	int w;
	Queue Q;
	Sleep(100);
	gotoxy(M.vertices[v].pos.x,M.vertices[v].pos.y);
	cout<<"*"; 
	visited[v]=true;
	InitQueue(Q);
	EnQueue(Q,v);
	while(!QueueEmpty(Q))
	{
		DeQueue(Q,u);
		for(w=FirstAdjVex(M,u);w>=0;w=NextAdjVex(M,u,w))
		//NextAdjVex(G,u,w) 返回图G的第u个节点的第w个邻接点的下一个邻接点 
		{
			if(!visited[w])		//w没有被访问过 
			{
				Sleep(10);
				gotoxy(M.vertices[w].pos.x,M.vertices[w].pos.y);
				cout<<"@";  
				visited[w]=true;
				EnQueue(Q,w); 
			}
		}
	}
}

void DFS(Map M,int v)
{
	Sleep(10);
	gotoxy(M.vertices[v].pos.x,M.vertices[v].pos.y);
	cout<<"@";
	visited[v]=true;
	ArcNode *p;
	int w;
	p=M.vertices[v].firstarc;
	while(p!=NULL)
	{
		w=p->adjvex;
		if(!visited[w])
		{
			DFS(M,w);
		}
		p=p->nextarc;
	}
}
