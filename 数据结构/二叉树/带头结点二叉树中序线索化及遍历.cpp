//��ͷ������������������������
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
typedef string ElemType;

//�ṹ��
typedef struct BiThrNode
{
	ElemType data;					   //������
	struct BiThrNode *lchild, *rchild; //���Һ���ָ��
	int LTag, RTag;					   //���ұ�־
} BiThrNode, *BiThrTree, *BiTree;

//ȫ�ֱ���
BiThrNode *Pre = new BiThrNode;

//��������
void IniBiTree(BiTree &T);						  //��ʼ��������
void InOrderTraverse(BiTree T);					  //�������
void InThreading(BiTree &T);					  //������
void InOrderThreading(BiThrTree &Thrt, BiTree T); //��ͷ�������������
void InOrderTraverse_Thr(BiThrTree T);
void CreateBiTree(BiTree &T);

//������
int main()
{
	//������֮ǰҪ���Ĳ���
	Pre->RTag = 1;
	Pre->rchild = NULL;
	//������׼�����
	BiTree T; //����������
	BiThrTree Thrt;
	IniBiTree(T); //��ʼ��������
	cout << "��������ʼ����ɣ�" << endl;
	system("pause");
	InOrderThreading(Thrt, T); //����������
	cout << "��������������ɣ�" << endl;
	system("pause");
	cout << "�����������ǣ�" << endl;
	InOrderTraverse_Thr(Thrt);
	cout << endl;
	system("pause");
	return 0;
}

//��������ʼ��
void IniBiTree(BiTree &T)
{
	T = new BiThrNode;
	T->data = 'a';
	T->rchild = NULL;								   //���ڵ�û��������
	T->lchild = new BiThrNode;						   //����B�ڵ�
	T->lchild->data = 'b';							   //����b�ڵ��������
	T->lchild->lchild = new BiThrNode;				   //����c�ڵ�
	T->lchild->lchild->data = 'c';					   //����c�ڵ��������
	T->lchild->lchild->lchild = NULL;				   // c�ڵ���������
	T->lchild->lchild->rchild = NULL;				   // c�ڵ���������
	T->lchild->rchild = new BiThrNode;				   //����d�ڵ�
	T->lchild->rchild->data = 'd';					   //����d�ڵ��������
	T->lchild->rchild->lchild = new BiThrNode;		   //����e�ڵ�
	T->lchild->rchild->lchild->data = 'e';			   //����e����������
	T->lchild->rchild->lchild->lchild = NULL;		   // e�ڵ�û��������
	T->lchild->rchild->lchild->rchild = new BiThrNode; //����g�ڵ�
	T->lchild->rchild->lchild->rchild->data = 'g';	   //����g�ڵ��������
	T->lchild->rchild->lchild->rchild->lchild = NULL;
	T->lchild->rchild->lchild->rchild->rchild = NULL;
	T->lchild->rchild->rchild = new BiThrNode; //����f�ڵ�
	T->lchild->rchild->rchild->data = 'f';
	T->lchild->rchild->rchild->lchild = NULL;
	T->lchild->rchild->rchild->rchild = NULL;
}

//������
void InThreading(BiTree &T)
{
	if (T)
	{
		InThreading(T->lchild);
		if (!T->lchild)
		{
			T->LTag = 1;
			T->lchild = Pre;
		}
		else
		{
			T->LTag = 0;
		}
		if (!Pre->rchild)
		{
			Pre->RTag = 1;
			Pre->rchild = T;
		}
		else
		{
			Pre->RTag = 0;
		}
		Pre = T;
		InThreading(T->rchild);
	}
}

//�������
void InOrderTraverse(BiTree T)
{
	if (T)
	{
		InOrderTraverse(T->lchild);
		cout << T->data << " ";
		InOrderTraverse(T->rchild);
	}
}

//��ͷ�������������
void InOrderThreading(BiThrTree &Thrt, BiTree T)
{
	Thrt = new BiThrNode; //����ͷ���
	Thrt->LTag = 0;		  //ͷ���������
	Thrt->RTag = 1;		  //ͷ�����Һ���Ϊ����
	Thrt->rchild = Thrt;  //��ʼ���Һ���ָ���Լ�
	if (!T)				  //�����Ϊ��������Ҳָ���Լ�
	{
		Thrt->lchild = Thrt;
	}
	else
	{
		Thrt->lchild = T; //����Ϊ����
		Pre = Thrt;		  //��ʼ������
		InThreading(T);
		Pre->rchild = Thrt; //��������PreΪ���һ���ڵ㣬�Һ���ָ��ͷ���
		Pre->RTag = 1;
		Thrt->rchild = Pre; //ͷ�����Һ���ָ��Pre
	}
}

//��������ı���
void InOrderTraverse_Thr(BiThrTree T)
{
	BiThrNode *p;
	p = T->lchild;
	while (p != T)
	{
		while (p->LTag == 0)
		{
			p = p->lchild;
		}
		cout << p->data << " "; //�����䲻�ܷŵ������ѭ����
		while (p->RTag == 1 && p->rchild != T)
		{
			p = p->rchild;
			cout << p->data << " ";
		}
		p = p->rchild;
	}
}

void CreateBiTree(BiTree &T)
{
	char ch;
	cout << "�����룺";
	cin >> ch;
	if (ch == '#')
	{
		T = NULL;
	}
	else
	{
		T = new BiThrNode;
		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
}
