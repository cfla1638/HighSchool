/*
	�������У�
	InThreading(T);
	traverse_PreOrder(T);
	�������������þ�û���κ�����
	������ͬʱ��������ȴ������ѭ��
	��Ϊ InThreading(T);
	��������������Ƕ������Ŀ�ָ�뱻��Ϊ����ǰ������
	���Բ���ͬʱ����
*/

//����������������ز���
#include <iostream>
#include <cstdio>

using namespace std;
//�ṹ��
typedef struct BiTNode
{
	char data;
	struct BiTNode *left, *right;
	int LTag, RTag;
} BiTNode, *BiTree;
//ȫ�ֱ���
BiTree Pre;

//��������
void CreateBiTree(BiTree &T);	   //�ֶ�����������
void IniBiTree(BiTree &T);		   //��ʼ��������
void traverse_InOrder(BiTree T);   //�������
void traverse_PreOrder(BiTree T);  //�������
void traverse_PostOrder(BiTree T); //�������
void InThreading(BiTree &T);	   //����������
//������
int main()
{
	BiTree T;
	Pre = new BiTNode;
	Pre->right = NULL;
	IniBiTree(T);
	//����������
	InThreading(T);
	traverse_PreOrder(T);
	//������
	return 0;
}
//����������
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
		T = new BiTNode;
		T->data = ch;
		CreateBiTree(T->left);
		CreateBiTree(T->right);
	}
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
void traverse_InOrder(BiTree T)
{
	if (T)
	{
		traverse_InOrder(T->left);
		cout << T->data << " ";
		traverse_InOrder(T->right);
	}
}
//���������
void traverse_PreOrder(BiTree T)
{
	if (T)
	{
		cout << T->data << " ";
		traverse_PreOrder(T->left);
		traverse_PreOrder(T->right);
	}
}
//���������
void traverse_PostOrder(BiTree T)
{
	if (T)
	{
		traverse_PostOrder(T->left);
		traverse_PostOrder(T->right);
		cout << T->data << " ";
	}
}
//����������
void InThreading(BiTree &T)
{
	system("pause");
	if (T) //���ڵ�ǿ�
	{
		InThreading(T->left); //������������
		if (!T->left)		  // T������Ϊ��
		{
			T->LTag = 1;
			T->left = Pre;
		}
		else
		{
			T->LTag = 0;
		}
		if (!Pre->right) // T���Һ���Ϊ��
		{
			Pre->RTag = 1;
			Pre->right = T;
		}
		else
		{
			Pre->RTag = 0;
		}
		Pre = T;
		InThreading(T->right);
	}
}
