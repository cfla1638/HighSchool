//图的邻接表表示法
#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<string>
#define MVNum 100       //最大节点数
#define OK 1
#define ERROR 0
using namespace std;
typedef int Status;


//----------邻接表储存表示----------
typedef string OtherInfo;
typedef string VerTexType;      //vertex 定点
typedef struct ArcNode      //边界点
{
	int adjvex;         //该边所指向节点的位置
	struct ArcNode *nextarc;        //指向下一条边的指针
	OtherInfo info;
} ArcNode;
typedef struct VNode        //顶点信息
{
	VerTexType data;
	ArcNode *firstarc;       //指向第一条依附于该定点的边的指针
} VNode,AdjList[MVNum];
typedef struct
{
	AdjList vertices;
	int vexnum,arcnum;
} ALGraph;

//----------函数声明----------
Status CreateUDG(ALGraph &G);       //采用邻接表创建无向图G
int LocateVex(ALGraph G , VerTexType v);

//----------主函数----------
int main()
{
	ALGraph G;
	CreateUDG(G);
	getch();
	return 0;
}


int LocateVex(ALGraph G , VerTexType v)
{
	//确定点v在G中的位置
	for(int i = 0; i < G.vexnum; ++i)
		if(G.vertices[i].data == v)
			return i;
	return -1;
}//LocateVex


Status CreateUDG(ALGraph &G)
{
	cout<<"请输入总定点数，总边数："<<endl;
	cin>>G.vexnum;
	cin>>G.arcnum;
	for(int i=0; i<G.vexnum; ++i)
	{
		cout<<"请输入第"<<(i+1)<<"个定点值:";
		cin>>G.vertices[i].data;        //输入定点值
		G.vertices[i].firstarc=NULL;     //初始化表头节点指针域为NULL
	}

	for(int k=0; k<G.arcnum; ++k)
	{
		VerTexType v1,v2;
		int i,j;
		cout<<"请输入第" << (k + 1) << "条边依附的顶点:";
		cin>>v1>>v2;
		//确定v1，v2在G中的位置
		i=LocateVex(G,v1);
		j=LocateVex(G,v2);
		ArcNode *p1=new ArcNode;
		p1->adjvex=j;
		p1->nextarc=G.vertices[i].firstarc;
		G.vertices[i].firstarc=p1;
		//同理...
		ArcNode *p2=new ArcNode;
		p2->adjvex=i;
		p2->nextarc=G.vertices[j].firstarc;
		G.vertices[j].firstarc=p2;
	}
	return OK;
}
