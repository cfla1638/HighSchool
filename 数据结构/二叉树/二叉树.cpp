//����������ز���
#include <iostream>
#define MAXTSIZE 100
using namespace std;
//���Ľṹ��
typedef struct BiTNode
{
	char data;					  //�ڵ��������
	struct BiTNode *left, *right; //�ڵ�����Һ���
} BiTNode, *BiTree;
//������������
void createtree(BiTree &T);
void traverse_InOrder(BiTree T);
void traverse_PreOrder(BiTree T);
void traverse_PostOrder(BiTree T);
//������
int main()
{
	BiTree T;
	createtree(T);
	cout << "���������";
	traverse_InOrder(T);
	cout << endl;
	cout << "���������";
	traverse_PreOrder(T);
	cout << endl;
	cout << "���������";
	traverse_PostOrder(T);
	cout << endl;
	return 0;
}
//�������������������
void createtree(BiTree &T)
{
	char ch;
	cout << "������:";
	cin >> ch;
	if (ch == '#')
	{
		T = NULL;
	}
	else
	{
		T = new BiTNode;
		T->data = ch;
		createtree(T->left);
		createtree(T->right);
	}
}
//���������������
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
