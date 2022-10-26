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
	VerTexType vexs[MVNum];		//�����
	ArcType arcs[MVNum][MVNum]; //�ڽӾ���
	int vexnum, arcnum;
} AMGraph;

//��������
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
	cout << "�������ܶ��������ܱ���:";
	cin >> G.vexnum >> G.arcnum;
	//��ʼ������
	for (int i = 0; i < G.vexnum; i++)
	{
		cout << "�����붥����Ϣ��";
		cin >> G.vexs[i];
	}
	//��ʼ���ڽӾ���
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
		cout << "������һ���������Ķ����Ȩֵ:";
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
