//��ͷ�ڵ�Ķ���������������
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
typedef string ElemType;

//�����������ṹ��
typedef struct BiThrNode
{
	ElemType data;
	struct BiThrNode *left, *right;
	int LTag, RTag;
} BiTNode, *BiTree;

//ȫ�ֱ���
BiTNode *Pre = new BiTNode;

//��������
void IniBiTree(BiTree &T);
void InOrderThreading(BiTree &Thrt, BiTree T);
void InThreading(BiTree &T); //����������

//������
int main()
{
	BiTree T, Thrt;
	IniBiTree(T);
	InOrderThreading(Thrt, T);
	cout << "��ɣ�" << endl;
	getchar();
	return 0;
}

//ֱ�Ӵ�������������ʼ����
void IniBiTree(BiTree &T)
{
	//���ڵ�
	T = new BiTNode;
	T->data = 'a';
	T->right = NULL;						   //���ڵ�û��������
	T->left = new BiTNode;					   //����B�ڵ�
	T->left->data = 'b';					   //����b�ڵ��������
	T->left->left = new BiTNode;			   //����c�ڵ�
	T->left->left->data = 'c';				   //����c�ڵ��������
	T->left->left->left = NULL;				   // c�ڵ���������
	T->left->left->right = NULL;			   // c�ڵ���������
	T->left->right = new BiTNode;			   //����d�ڵ�
	T->left->right->data = 'd';				   //����d�ڵ��������
	T->left->right->left = new BiTNode;		   //����e�ڵ�
	T->left->right->left->data = 'e';		   //����e����������
	T->left->right->left->left = NULL;		   // e�ڵ�û��������
	T->left->right->left->right = new BiTNode; //����g�ڵ�
	T->left->right->left->right->data = 'g';   //����g�ڵ��������
	T->left->right->left->right->left = NULL;
	T->left->right->left->right->right = NULL;
	T->left->right->right = new BiTNode; //����f�ڵ�
	T->left->right->right->data = 'f';
	T->left->right->right->left = NULL;
	T->left->right->right->right = NULL;
}

//������������ͷ��������
void InOrderThreading(BiTree &Thrt, BiTree T)
{
	Thrt = new BiTNode; //����ͷ���
	Thrt->LTag = 0;		//ͷ��������ӣ������ǿգ���������Ϊ����
	Thrt->RTag = 1;		//ͷ����Һ���Ϊ������
	Thrt->right = Thrt; //��ʼ��ʱ�Һ���ָ���Լ�
	if (!T)				//�����Ϊ��������Ҳָ���Լ�
		Thrt->left = Thrt;
	else
	{
		Thrt->left = T;
		Pre = Thrt;
		InThreading(T);
		Pre->right = Thrt;
		Pre->RTag = 1;
		Thrt->right = Pre;
	}
}

//��һ���㷨������������
void InThreading(BiTree &T)
{
	if (T) //���ڵ�ǿ�
	{
		InThreading(T->left); //������������
		if (!T->left)		  // T������Ϊ��
		{
			T->LTag = 1;
			T->left = Pre;
		}
		else
			T->LTag = 0;
		if (!Pre->right) // T���Һ���Ϊ��
		{
			Pre->RTag = 1;
			Pre->right = T;
		}
		else
			Pre->RTag = 0;
		Pre = T;
		InThreading(T->right);
	}
}
