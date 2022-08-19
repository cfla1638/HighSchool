//顺序队 
#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<string>
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define MAXQSIZE 100
using namespace std;
typedef int Status;
typedef string QElemType;

typedef struct 
{
	QElemType *base;		//基地址
	int front;				//头指针
	int rear;				//尾指针 
} SqQueue;


//函数声明
Status InitQueue(SqQueue &Q);
Status EnQueue(SqQueue &Q,QElemType e);
Status DeQueue(SqQueue &Q,QElemType &e);

int main()
{
	SqQueue Q;
	if(InitQueue(Q))
	{
		cout<<"队列初始化完成"<<endl; 
		getch();
	}
	else
	{
		cout<<"Error";
		getch();
	}
	//------------------------------
	cout<<"入队"<<endl; 
	QElemType EnElem;
	cout<<"请输入入队元素：";
	cin>>EnElem;
	if(EnQueue(Q,EnElem))
	{
		cout<<"入队成功！"<<endl;
		getch(); 
	}
	else
	{
		cout<<"Error"<<endl;
		getch(); 
	} 
	//-------------------------------
	cout<<"出队"<<endl;
	QElemType DeElem;
	if(DeQueue(Q,DeElem))
	{
		cout<<"出队成功"<<endl;
		cout<<"出队的元素是："<<DeElem;
		getch();
	}
	else
	{
		cout<<"Error"<<endl;
		getch();
	}
	
	return 0;
} 


Status InitQueue(SqQueue &Q)
{
	Q.base=new QElemType[MAXQSIZE];
	if(!Q.base)
	{
		exit(OVERFLOW); 
	}
	Q.front=Q.rear=0;
	return OK;
}


Status EnQueue(SqQueue &Q,QElemType e)
{
	if((Q.rear+1)%MAXQSIZE==Q.front)
	{
		return ERROR;
	}
	Q.base[Q.rear]=e;
	Q.rear=(Q.rear+1)%MAXQSIZE;
	return OK;
}


Status DeQueue(SqQueue &Q,QElemType &e)
{
	if(Q.front==Q.rear)
	{
		return ERROR;
	}
	e=Q.base[Q.front];
	Q.front=(Q.front+1)%MAXQSIZE;
	return OK;
}
