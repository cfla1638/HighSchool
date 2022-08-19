#include<iostream>
#include<windows.h>
#include<conio.h>
#define MAPSIZE 2500	//��ͼ�Ĵ�С�� 
#define MAXQSIZE 100
#define OK 1
#define ERROR 0
using namespace std;
typedef int Status;

//������� 
bool visited[MAPSIZE];

//�ṹ��
typedef struct pos
{
	int x,y;
}Pos;
typedef struct ArcNode
{
	int adjvex;		//ָ��Ķ����λ��
	struct ArcNode *nextarc; 
}ArcNode;

typedef struct VNode
{
	int seqNum;		//���
	Pos pos;		//λ�� 
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

//��������
Status InitMap(Map &M,int len,int wid);
void BFS(Map M,int v); 
void DFS(Map M,int v); 
//����Ϊ�������� 
void createArc(Map &M,int i,int j);
void gotoxy(int x,int y); 
int getX(int seqNum,int len);
int getY(int seqNum,int len);
bool QueueEmpty(Queue Q);
int EnQueue(Queue &Q,int e);
void DeQueue(Queue &Q,int &u);
int FirstAdjVex(Map M,int v);
Status InitQueue(Queue &Q);

//������
int main()
{
	Map M;
	cout<<"�������ʼBFS...";
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
	//������Ŀ=[��*(��-1)]+[��*(��-1)] 
	M.arcnum=len*(wid-1)+wid*(len-1);
	//��ʼ��������Ϣ 
	for(int i=0;i<M.vexnum;i++)
	{
		M.vertices[i].seqNum=i;
		M.vertices[i].firstarc=NULL;
		//����λ�ý��г�ʼ�� 
		M.vertices[i].pos.x=getX(M.vertices[i].seqNum,len);
		M.vertices[i].pos.y=getY(M.vertices[i].seqNum,len);
	}
	//ʹ�ö�ά����ģ��ͼ 
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
	//���ɱ� 
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
	//����
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
	//�߱�����һ���ڵ��nextarcָ��ָ��ñ߱�ĵ�һ���ڵ㣻��G.vertices[u].firstarc 
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
		temp=temp->nextarc;		//�������²��� 
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
	int u;		//���ӵ����� 
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
		//NextAdjVex(G,u,w) ����ͼG�ĵ�u���ڵ�ĵ�w���ڽӵ����һ���ڽӵ� 
		{
			if(!visited[w])		//wû�б����ʹ� 
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
