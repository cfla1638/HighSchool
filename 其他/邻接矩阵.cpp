#include <iostream>
#include <string>
#define MaxInt 32767
#define MVNum 100
#define OK 1
#define ERROR 0
using namespace std;

typedef int Status;
typedef string VerTexType;
typedef int ArcType;
typedef struct
{
	VerTexType vexs[MVNum];		//顶点表
	ArcType arcs[MVNum][MVNum]; //邻接矩阵
	int vexnum, arcnum;
} AMGraph;

//函数声明
Status CreateUDN(AMGraph &G);
int LocateVex(AMGraph G, VerTexType v);

int main()
{
	AMGraph G;
	CreateUDN(G);
	return 0;
}

Status CreateUDN(AMGraph &G)
{
	cout << "请输入总顶点数和总边数:";
	cin >> G.vexnum >> G.arcnum;
	//初始化顶点
	for (int i = 0; i < G.vexnum; i++)
	{
		cout << "请输入顶点信息：";
		cin >> G.vexs[i];
	}
	//初始化邻接矩阵
	for (int i = 0; i < G.arcnum; i++)
	{
		for (int j = 0; j < G.arcnum; j++)
		{
			G.arcs[i][j] = MaxInt;
		}
	}
	for (int k = 0; k < G.arcnum; k++)
	{
		int i, j;
		VerTexType v1, v2;
		ArcType w;
		cout << "请输入一条边依附的顶点和权值:";
		cin >> v1 >> v2 >> w;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.arcs[i][j] = w;
		G.arcs[j][i] = w;
	}
	return OK;
}

int LocateVex(AMGraph G, VerTexType v)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vexs[i] == v)
		{
			return i;
		}
	}
	return -1;
}
