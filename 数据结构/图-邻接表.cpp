//ͼ���ڽӱ��ʾ��
#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<string>
#define MVNum 100       //���ڵ���
#define OK 1
#define ERROR 0
using namespace std;
typedef int Status;


//----------�ڽӱ����ʾ----------
typedef string OtherInfo;
typedef string VerTexType;      //vertex ����
typedef struct ArcNode      //�߽��
{
	int adjvex;         //�ñ���ָ��ڵ��λ��
	struct ArcNode *nextarc;        //ָ����һ���ߵ�ָ��
	OtherInfo info;
} ArcNode;
typedef struct VNode        //������Ϣ
{
	VerTexType data;
	ArcNode *firstarc;       //ָ���һ�������ڸö���ıߵ�ָ��
} VNode,AdjList[MVNum];
typedef struct
{
	AdjList vertices;
	int vexnum,arcnum;
} ALGraph;

//----------��������----------
Status CreateUDG(ALGraph &G);       //�����ڽӱ�������ͼG
int LocateVex(ALGraph G , VerTexType v);

//----------������----------
int main()
{
	ALGraph G;
	CreateUDG(G);
	getch();
	return 0;
}


int LocateVex(ALGraph G , VerTexType v)
{
	//ȷ����v��G�е�λ��
	for(int i = 0; i < G.vexnum; ++i)
		if(G.vertices[i].data == v)
			return i;
	return -1;
}//LocateVex


Status CreateUDG(ALGraph &G)
{
	cout<<"�������ܶ��������ܱ�����"<<endl;
	cin>>G.vexnum;
	cin>>G.arcnum;
	for(int i=0; i<G.vexnum; ++i)
	{
		cout<<"�������"<<(i+1)<<"������ֵ:";
		cin>>G.vertices[i].data;        //���붨��ֵ
		G.vertices[i].firstarc=NULL;     //��ʼ����ͷ�ڵ�ָ����ΪNULL
	}

	for(int k=0; k<G.arcnum; ++k)
	{
		VerTexType v1,v2;
		int i,j;
		cout<<"�������" << (k + 1) << "���������Ķ���:";
		cin>>v1>>v2;
		//ȷ��v1��v2��G�е�λ��
		i=LocateVex(G,v1);
		j=LocateVex(G,v2);
		ArcNode *p1=new ArcNode;
		p1->adjvex=j;
		p1->nextarc=G.vertices[i].firstarc;
		G.vertices[i].firstarc=p1;
		//ͬ��...
		ArcNode *p2=new ArcNode;
		p2->adjvex=i;
		p2->nextarc=G.vertices[j].firstarc;
		G.vertices[j].firstarc=p2;
	}
	return OK;
}
