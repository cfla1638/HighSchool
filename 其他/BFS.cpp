// BFS��������㷨��ʵ��
#include <iostream>
#include <string>
#include <stdlib.h>
//����״̬�뼰������
#define MVNum 100
#define MAXQSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -1
using namespace std;
typedef int Status;		   //����״̬
typedef int OtherInfo;	   //�ߵ���Ϣ
typedef string VerTexType; //�ڵ���Ϣ

//�������
bool visited[MVNum];

//�߽ڵ�Ķ���
typedef struct ArcNode
{
	int adjvex;
	struct ArcNode *nextarc;
	OtherInfo info;
} ArcNode;
//����Ķ���
typedef struct VNode
{
	VerTexType data;
	ArcNode *firstarc;
} VNode, AdjList[MVNum];
//ͼ�Ľṹ��
typedef struct
{
	AdjList vertices;
	int vexnum, arcnum;
} ALGraph;

//���еĽṹ��
//����BFS
typedef struct
{
	int *base;
	int front;
	int rear;
} Queue;

//��������
void BFS(ALGraph G, int v);
Status InitALGraph(ALGraph &G);
int LocateVex(ALGraph G, VerTexType v);
Status InitQueue(Queue &Q);
bool QueueEmpty(Queue Q);
int EnQueue(Queue &Q, int e);
void DeQueue(Queue &Q, int &u);
int FirstAdjVex(ALGraph G, int v);
int NextAdjVex(ALGraph G, int u, int w);

//������
int main()
{
	ALGraph G;
	InitALGraph(G);
	cout << "�������������" << endl;
	BFS(G, 0);
	return 0;
}

void BFS(ALGraph G, int v)
{
	int u; //���ӵ�����
	int w;
	Queue Q;
	cout << G.vertices[v].data << " "; //���ʵ�һ��Ԫ��
	visited[v] = true;
	InitQueue(Q);
	EnQueue(Q, v);
	while (!QueueEmpty(Q))
	{
		DeQueue(Q, u);
		/*
		3.4�ʼǣ�
		���������NextAdjVex()����������
		�����޷��ж�һ���ڽӵ�ı߽ڵ��Ƿ�Ϊ���һ��
		�������޷�����-1���³���һֱ�����������forѭ����
		*/
		for (w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
		// NextAdjVex(G,u,w) ����ͼG�ĵ�u���ڵ�ĵ�w���ڽӵ����һ���ڽӵ�
		{
			if (!visited[w]) // wû�б����ʹ�
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
	cout << "�������ܽ������";
	cin >> G.vexnum;
	cout << "�������ܱ�����";
	cin >> G.arcnum;
	for (int i = 0; i < G.vexnum; i++)
	{
		cout << "�������" << i + 1 << "���ڵ��ֵ��";
		cin >> G.vertices[i].data;
		G.vertices[i].firstarc = NULL; //��ʼ����ͷָ����Ϊ��
	}
	for (int k = 0; k < G.arcnum; k++)
	{
		VerTexType v1, v2;
		int i, j;
		cout << "������һ�����������������㣺";
		cin >> v1 >> v2;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);

		ArcNode *p1, *p2;
		p1 = new ArcNode;
		p2 = new ArcNode;

		p1->adjvex = j;
		p2->adjvex = i;
		//����
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
	//�߱�����һ���ڵ��nextarcָ��ָ��ñ߱�ĵ�һ���ڵ㣻��G.vertices[u].firstarc
	temp = G.vertices[u].firstarc;
	if (temp->adjvex == w)
	{
		return temp->nextarc->adjvex;
	}
	temp = temp->nextarc;
	/*
	�ؼ���
	Ҫ������߱����һ���ڵ��nextarc������ָ������
	�������whileѭ�������ı�־
	*/
	//Ӧ�ðɡ�������Ҳ��֪��������
	// while(temp!=G.vertices[u].firstarc)  ��
	// while(temp!=NULL ��
	//���������ǶԵģ�������
	while (temp->nextarc != NULL)
	{
		if (temp->adjvex == w)
		{
			return temp->nextarc->adjvex;
		}
		temp = temp->nextarc; //�������²���
	}
	return -1;
}
