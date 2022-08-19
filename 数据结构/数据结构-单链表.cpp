#include<iostream>
#include<string>
#include<cstdio>
//��������״̬���� 
#define OK 1
#define ERROR 0
using namespace std;
typedef int Status;   //��������״̬����
typedef string ElemType;   //���ݵ����� 


//������Ľڵ㶨��
typedef struct LNode
{
	ElemType Data;   //������ 
	struct LNode *Next;  //ָ���� 
}LNode,*LinkList;


//����������
Status IniLinkList(LinkList& L);   //������ĳ�ʼ�� 
Status GetElem(LinkList L,int i,ElemType& e);   //�������ȡֵ 
LNode *LocateElem(LinkList L,ElemType e);   //������İ�ֵ���� 
Status LinkInsert(LinkList L,ElemType e);   //������Ĳ��루ֱ����ͷ���ĺ�����룩
void TraverseLinkList(LinkList L);   //������ı��� 

 
//������
int main()
{
	string ch; 
	LinkList L;
	IniLinkList(L);
	//*************************************
	cout<<"***�����������ڵ�"<<endl<<endl; 
	for(int i=0;i<5;i++)
	{
		cout<<"���ýڵ�Ԫ��Ϊ��";
		cin>>ch;
		LinkInsert(L,ch);
	}
	system("pause");
	cout<<endl<<endl;
	//**************************************
	cout<<"***�������ȡֵ"<<endl<<endl;
	int j;
	string e;
	cout<<"������Ҫȡֵ�Ľڵ㣺";
	cin>>j;
	GetElem(L,j,e);
	cout<<"�ýڵ��������Ϊ��"<<e<<endl;
	system("pause");
	cout<<endl<<endl;
	//**************************************
	cout<<"***������İ�ֵ���ң�"<<endl<<endl;
	string a;
	LNode *p;
	cout<<"������Ҫ���ҵĽڵ��������";
	cin>>a;
	p=LocateElem(L,a);
	cout<<"���ҵ��ڵ���������Ϊ��"<<p->Data<<endl;
	system("pause");
	cout<<endl<<endl;
	//************************************** 
	cout<<"***������ı�����"<<endl<<endl; 
	TraverseLinkList(L);
	system("pause");
	return 0;
} 


//������ĳ�ʼ��
Status IniLinkList(LinkList& L)
{
	L=new LNode;   //����һ��ͷ��� 
	L->Next=NULL;   //ָ����Ϊ�� 
	return OK;
} 


//�������ȡֵ
Status GetElem(LinkList L,int i,ElemType& e)
{
	int j=1;   //������
	LNode *p=L->Next;
	while(p && j<i)
	{
		p=p->Next;
		++j;
	} 
	if(!p || j>i)
	{
		return ERROR;
	}
	e=p->Data;
	return OK;
} 


//������ֵ����
LNode *LocateElem(LinkList L,ElemType e)
{
	LNode *p=L->Next;   //��ʼ��pָ����Ԫ�ڵ�
	while(p && p->Data!=e)
	{
		p=p->Next;
	} 
	return p;
} 


//������Ĳ���
Status LinkInsert(LinkList L,ElemType e)
{
	LNode *p,*temp;
	p=new LNode;
	temp=L->Next;
	L->Next=p;
	p->Next=temp;
	p->Data=e;
	return OK; 
} 


//������ı���
void TraverseLinkList(LinkList L)
{
	LNode *p=L->Next;
	while(p)
	{
		cout<<"�ýڵ�Ԫ��Ϊ��"<<p->Data<<endl;
		p=p->Next; 
	}
}
