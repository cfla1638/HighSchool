#include<iostream>
#include<string>
#include<cstdio>
//函数返回状态代码 
#define OK 1
#define ERROR 0
using namespace std;
typedef int Status;   //函数返回状态类型
typedef string ElemType;   //数据的类型 


//单链表的节点定义
typedef struct LNode
{
	ElemType Data;   //数据域 
	struct LNode *Next;  //指针域 
}LNode,*LinkList;


//函数的声明
Status IniLinkList(LinkList& L);   //单链表的初始化 
Status GetElem(LinkList L,int i,ElemType& e);   //单链表的取值 
LNode *LocateElem(LinkList L,ElemType e);   //单链表的按值查找 
Status LinkInsert(LinkList L,ElemType e);   //单链表的插入（直接在头结点的后面插入）
void TraverseLinkList(LinkList L);   //单链表的遍历 

 
//主函数
int main()
{
	string ch; 
	LinkList L;
	IniLinkList(L);
	//*************************************
	cout<<"***设置添加五个节点"<<endl<<endl; 
	for(int i=0;i<5;i++)
	{
		cout<<"设置节点元素为：";
		cin>>ch;
		LinkInsert(L,ch);
	}
	system("pause");
	cout<<endl<<endl;
	//**************************************
	cout<<"***单链表的取值"<<endl<<endl;
	int j;
	string e;
	cout<<"请输入要取值的节点：";
	cin>>j;
	GetElem(L,j,e);
	cout<<"该节点的数据域为："<<e<<endl;
	system("pause");
	cout<<endl<<endl;
	//**************************************
	cout<<"***单链表的按值查找："<<endl<<endl;
	string a;
	LNode *p;
	cout<<"请输入要查找的节点的数据域：";
	cin>>a;
	p=LocateElem(L,a);
	cout<<"查找到节点的数据域的为："<<p->Data<<endl;
	system("pause");
	cout<<endl<<endl;
	//************************************** 
	cout<<"***单链表的遍历："<<endl<<endl; 
	TraverseLinkList(L);
	system("pause");
	return 0;
} 


//单链表的初始化
Status IniLinkList(LinkList& L)
{
	L=new LNode;   //申请一个头结点 
	L->Next=NULL;   //指针域为空 
	return OK;
} 


//单链表的取值
Status GetElem(LinkList L,int i,ElemType& e)
{
	int j=1;   //计数器
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


//单链表按值查找
LNode *LocateElem(LinkList L,ElemType e)
{
	LNode *p=L->Next;   //初始化p指向首元节点
	while(p && p->Data!=e)
	{
		p=p->Next;
	} 
	return p;
} 


//单链表的插入
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


//单链表的遍历
void TraverseLinkList(LinkList L)
{
	LNode *p=L->Next;
	while(p)
	{
		cout<<"该节点元素为："<<p->Data<<endl;
		p=p->Next; 
	}
}
