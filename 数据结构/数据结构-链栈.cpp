#include <iostream>
#include <cstdio>
#include <string>
#define OK 1
#define ERROR 0
using namespace std;
typedef int Status;
typedef string ElemType;

//��ջ�Ľṹ��
typedef struct StackNode
{
	ElemType Data;
	struct StackNode *Next;
} StackNode, *LinkStack;

//����������
Status IniStack(LinkStack &S);		   //��ջ�ĳ�ʼ��
Status Push(LinkStack &S, ElemType e); //��ջ����ջ
Status Pop(LinkStack &S, ElemType &e); //��ջ�ĳ�ջ��ɾ��ջ��Ԫ�أ������䷵�ظ�e��
ElemType GetTop(LinkStack S);		   //ȡջ��Ԫ��
void TraverseStack(LinkStack S);	   //ջ�ı���

//������
int main()
{
	LinkStack S;
	//*************************************
	IniStack(S);
	//*************************************
	cout << "***��ջ" << endl
		 << endl;
	string e;
	for (int i = 0; i < 5; i++)
	{
		cout << "������Ҫ��ջ��Ԫ�أ�";
		cin >> e;
		Push(S, e);
	}
	system("pause");
	cout << endl
		 << endl;
	//*************************************
	cout << "***��ջ" << endl
		 << endl;
	cout << "��ջǰջ�ı���" << endl
		 << endl;
	TraverseStack(S);
	cout << endl;
	string a;
	Pop(S, a);
	cout << "��ջԪ�ص��������ǣ�" << a << endl;
	cout << "��ջ���ջ�ı���" << endl
		 << endl;
	TraverseStack(S);
	system("pause");
	cout << endl
		 << endl;
	//*************************************
	cout << "***ȡջ��Ԫ��" << endl
		 << endl;
	string b;
	b = GetTop(S);
	cout << "ջ��Ԫ���ǣ�" << b << endl;
	system("pause");
	cout << endl
		 << endl;
	//*************************************
	cout << "***ջ�ı���" << endl
		 << endl;
	TraverseStack(S);
	system("pause");
	return 0;
}

//��ջ�ĳ�ʼ��
Status IniStack(LinkStack &S)
{
	S = NULL;
	return OK;
}

//��ջ
Status Push(LinkStack &S, ElemType e)
{
	StackNode *p = new StackNode; //�����½ڵ�
	p->Data = e;				  //�����½ڵ��������
	p->Next = S;				  //���½ڵ����ջ
	S = p;						  //�޸�ջ��ָ��
	return OK;
}

//��ջ
Status Pop(LinkStack &S, ElemType &e)
{
	StackNode *p;
	if (S == NULL) //ջΪ��
	{
		return ERROR;
	}
	e = S->Data; //����ջ��Ԫ��
	p = S;		 //����ջ��Ԫ���Ա��ͷ�
	S = S->Next; //�޸�ջ��Ԫ��
	delete p;	 //�ͷ�ջ��Ԫ��
	return OK;
}

//ȡջ��Ԫ��
ElemType GetTop(LinkStack S)
{
	if (S != NULL) //ջ�ǿ�
	{
		return S->Data;
	}
}

//ջ�ı���
void TraverseStack(LinkStack S)
{
	StackNode *p;
	p = S;
	while (p != NULL)
	{
		cout << "�ýڵ��������Ϊ��" << p->Data << endl;
		p = p->Next;
	}
}
