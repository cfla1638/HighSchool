//˳��� 
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
	QElemType *base;		//����ַ
	int front;				//ͷָ��
	int rear;				//βָ�� 
} SqQueue;


//��������
Status InitQueue(SqQueue &Q);
Status EnQueue(SqQueue &Q,QElemType e);
Status DeQueue(SqQueue &Q,QElemType &e);

int main()
{
	SqQueue Q;
	if(InitQueue(Q))
	{
		cout<<"���г�ʼ�����"<<endl; 
		getch();
	}
	else
	{
		cout<<"Error";
		getch();
	}
	//------------------------------
	cout<<"���"<<endl; 
	QElemType EnElem;
	cout<<"���������Ԫ�أ�";
	cin>>EnElem;
	if(EnQueue(Q,EnElem))
	{
		cout<<"��ӳɹ���"<<endl;
		getch(); 
	}
	else
	{
		cout<<"Error"<<endl;
		getch(); 
	} 
	//-------------------------------
	cout<<"����"<<endl;
	QElemType DeElem;
	if(DeQueue(Q,DeElem))
	{
		cout<<"���ӳɹ�"<<endl;
		cout<<"���ӵ�Ԫ���ǣ�"<<DeElem;
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
