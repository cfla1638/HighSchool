#include <iostream>
#include <cstdio>
#include <string>
#define OK 1
#define ERROR 0
using namespace std;
typedef int Status;
typedef string ElemType;

//链栈的结构体
typedef struct StackNode
{
	ElemType Data;
	struct StackNode *Next;
} StackNode, *LinkStack;

//函数的声明
Status IniStack(LinkStack &S);		   //链栈的初始化
Status Push(LinkStack &S, ElemType e); //链栈的入栈
Status Pop(LinkStack &S, ElemType &e); //链栈的出栈（删除栈顶元素，并将其返回给e）
ElemType GetTop(LinkStack S);		   //取栈顶元素
void TraverseStack(LinkStack S);	   //栈的遍历

//主函数
int main()
{
	LinkStack S;
	//*************************************
	IniStack(S);
	//*************************************
	cout << "***入栈" << endl
		 << endl;
	string e;
	for (int i = 0; i < 5; i++)
	{
		cout << "请输入要入栈的元素：";
		cin >> e;
		Push(S, e);
	}
	system("pause");
	cout << endl
		 << endl;
	//*************************************
	cout << "***出栈" << endl
		 << endl;
	cout << "出栈前栈的遍历" << endl
		 << endl;
	TraverseStack(S);
	cout << endl;
	string a;
	Pop(S, a);
	cout << "出栈元素的数据域是：" << a << endl;
	cout << "出栈后的栈的遍历" << endl
		 << endl;
	TraverseStack(S);
	system("pause");
	cout << endl
		 << endl;
	//*************************************
	cout << "***取栈顶元素" << endl
		 << endl;
	string b;
	b = GetTop(S);
	cout << "栈顶元素是：" << b << endl;
	system("pause");
	cout << endl
		 << endl;
	//*************************************
	cout << "***栈的遍历" << endl
		 << endl;
	TraverseStack(S);
	system("pause");
	return 0;
}

//链栈的初始化
Status IniStack(LinkStack &S)
{
	S = NULL;
	return OK;
}

//入栈
Status Push(LinkStack &S, ElemType e)
{
	StackNode *p = new StackNode; //生成新节点
	p->Data = e;				  //设置新节点的数据域
	p->Next = S;				  //将新节点插入栈
	S = p;						  //修改栈顶指针
	return OK;
}

//出栈
Status Pop(LinkStack &S, ElemType &e)
{
	StackNode *p;
	if (S == NULL) //栈为空
	{
		return ERROR;
	}
	e = S->Data; //返回栈顶元素
	p = S;		 //保留栈顶元素以备释放
	S = S->Next; //修改栈顶元素
	delete p;	 //释放栈顶元素
	return OK;
}

//取栈顶元素
ElemType GetTop(LinkStack S)
{
	if (S != NULL) //栈非空
	{
		return S->Data;
	}
}

//栈的遍历
void TraverseStack(LinkStack S)
{
	StackNode *p;
	p = S;
	while (p != NULL)
	{
		cout << "该节点的数据域为：" << p->Data << endl;
		p = p->Next;
	}
}
