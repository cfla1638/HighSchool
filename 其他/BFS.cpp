// BFS广度优先算法的实现
#include <iostream>
#include <string>
#include <stdlib.h>
//函数状态码及其他宏
#define MVNum 100
#define MAXQSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -1
using namespace std;
typedef int Status;		   //函数状态
typedef int OtherInfo;	   //边的信息
typedef string VerTexType; //节点信息

//标记数组
bool visited[MVNum];

//边节点的定义
typedef struct ArcNode
{
	int adjvex;
	struct ArcNode *nextarc;
	OtherInfo info;
} ArcNode;
//定点的定义
typedef struct VNode
{
	VerTexType data;
	ArcNode *firstarc;
} VNode, AdjList[MVNum];
//图的结构体
typedef struct
{
	AdjList vertices;
	int vexnum, arcnum;
} ALGraph;

//队列的结构体
//用于BFS
typedef struct
{
	int *base;
	int front;
	int rear;
} Queue;

//函数声明
void BFS(ALGraph G, int v);
Status InitALGraph(ALGraph &G);
int LocateVex(ALGraph G, VerTexType v);
Status InitQueue(Queue &Q);
bool QueueEmpty(Queue Q);
int EnQueue(Queue &Q, int e);
void DeQueue(Queue &Q, int &u);
int FirstAdjVex(ALGraph G, int v);
int NextAdjVex(ALGraph G, int u, int w);

//主函数
int main()
{
	ALGraph G;
	InitALGraph(G);
	cout << "广度优先搜索：" << endl;
	BFS(G, 0);
	return 0;
}

void BFS(ALGraph G, int v)
{
	int u; //出队的容器
	int w;
	Queue Q;
	cout << G.vertices[v].data << " "; //访问第一个元素
	visited[v] = true;
	InitQueue(Q);
	EnQueue(Q, v);
	while (!QueueEmpty(Q))
	{
		DeQueue(Q, u);
		/*
		3.4笔记：
		程序出错是NextAdjVex()函数的问题
		函数无法判断一个邻接点的边节点是否为最后一个
		即函数无法返回-1导致程序一直卡在下面这个for循环里
		*/
		for (w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
		// NextAdjVex(G,u,w) 返回图G的第u个节点的第w个邻接点的下一个邻接点
		{
			if (!visited[w]) // w没有被访问过
			{
				cout << G.vertices[w].data << " ";
				visited[w] = true;
				EnQueue(Q, w);
			}
		}
	}
}

int LocateVex(ALGraph G, VerTexType v)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vertices[i].data == v)
		{
			return i;
		}
	}
	return -1;
}

Status InitALGraph(ALGraph &G)
{
	cout << "请输入总结点数：";
	cin >> G.vexnum;
	cout << "请输入总边数：";
	cin >> G.arcnum;
	for (int i = 0; i < G.vexnum; i++)
	{
		cout << "请输入第" << i + 1 << "个节点的值：";
		cin >> G.vertices[i].data;
		G.vertices[i].firstarc = NULL; //初始化表头指针域为空
	}
	for (int k = 0; k < G.arcnum; k++)
	{
		VerTexType v1, v2;
		int i, j;
		cout << "请输入一条边依附的两个顶点：";
		cin >> v1 >> v2;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);

		ArcNode *p1, *p2;
		p1 = new ArcNode;
		p2 = new ArcNode;

		p1->adjvex = j;
		p2->adjvex = i;
		//插入
		p1->nextarc = G.vertices[i].firstarc;
		p2->nextarc = G.vertices[j].firstarc;

		G.vertices[i].firstarc = p1;
		G.vertices[j].firstarc = p2;
	}
	return OK;
}

Status InitQueue(Queue &Q)
{
	Q.base = new int[MAXQSIZE];
	Q.front = Q.rear = 0;
	return OK;
}

bool QueueEmpty(Queue Q)
{
	if (Q.rear == Q.front)
	{
		return true;
	}
	return false;
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

int FirstAdjVex(ALGraph G, int v)
{
	return G.vertices[v].firstarc->adjvex;
}

int NextAdjVex(ALGraph G, int u, int w)
{
	ArcNode *temp;
	//边表的最后一个节点的nextarc指针指向该边表的第一个节点；即G.vertices[u].firstarc
	temp = G.vertices[u].firstarc;
	if (temp->adjvex == w)
	{
		return temp->nextarc->adjvex;
	}
	temp = temp->nextarc;
	/*
	关键：
	要搞清楚边表最后一个节点的nextarc究竟是指向哪里
	即搞清楚while循环结束的标志
	*/
	//应该吧。。。我也不知道。。。
	// while(temp!=G.vertices[u].firstarc)  ×
	// while(temp!=NULL ×
	//下面的这个是对的！！！！
	while (temp->nextarc != NULL)
	{
		if (temp->adjvex == w)
		{
			return temp->nextarc->adjvex;
		}
		temp = temp->nextarc; //继续向下查找
	}
	return -1;
}
