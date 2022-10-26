//带头结点二叉树中序线索化及遍历
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
typedef string ElemType;

//结构体
typedef struct BiThrNode
{
	ElemType data;					   //数据域
	struct BiThrNode *lchild, *rchild; //左右孩子指针
	int LTag, RTag;					   //左右标志
} BiThrNode, *BiThrTree, *BiTree;

//全局变量
BiThrNode *Pre = new BiThrNode;

//函数声明
void IniBiTree(BiTree &T);						  //初始化二叉树
void InOrderTraverse(BiTree T);					  //中序遍历
void InThreading(BiTree &T);					  //线索化
void InOrderThreading(BiThrTree &Thrt, BiTree T); //带头结点中序线索化
void InOrderTraverse_Thr(BiThrTree T);
void CreateBiTree(BiTree &T);

//主函数
int main()
{
	//线索化之前要做的操作
	Pre->RTag = 1;
	Pre->rchild = NULL;
	//线索化准备完成
	BiTree T; //建立二叉树
	BiThrTree Thrt;
	IniBiTree(T); //初始化二叉树
	cout << "二叉树初始化完成！" << endl;
	system("pause");
	InOrderThreading(Thrt, T); //中序线索化
	cout << "二叉树线索化完成！" << endl;
	system("pause");
	cout << "中序遍历结果是：" << endl;
	InOrderTraverse_Thr(Thrt);
	cout << endl;
	system("pause");
	return 0;
}

//二叉树初始化
void IniBiTree(BiTree &T)
{
	T = new BiThrNode;
	T->data = 'a';
	T->rchild = NULL;								   //根节点没有右子树
	T->lchild = new BiThrNode;						   //申请B节点
	T->lchild->data = 'b';							   //设置b节点的数据域
	T->lchild->lchild = new BiThrNode;				   //申请c节点
	T->lchild->lchild->data = 'c';					   //设置c节点的数据域
	T->lchild->lchild->lchild = NULL;				   // c节点无左子树
	T->lchild->lchild->rchild = NULL;				   // c节点无右子树
	T->lchild->rchild = new BiThrNode;				   //申请d节点
	T->lchild->rchild->data = 'd';					   //设置d节点的数据域
	T->lchild->rchild->lchild = new BiThrNode;		   //申请e节点
	T->lchild->rchild->lchild->data = 'e';			   //设置e结点的数据域
	T->lchild->rchild->lchild->lchild = NULL;		   // e节点没有左子树
	T->lchild->rchild->lchild->rchild = new BiThrNode; //申请g节点
	T->lchild->rchild->lchild->rchild->data = 'g';	   //设置g节点的数据域
	T->lchild->rchild->lchild->rchild->lchild = NULL;
	T->lchild->rchild->lchild->rchild->rchild = NULL;
	T->lchild->rchild->rchild = new BiThrNode; //申请f节点
	T->lchild->rchild->rchild->data = 'f';
	T->lchild->rchild->rchild->lchild = NULL;
	T->lchild->rchild->rchild->rchild = NULL;
}

//线索化
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

//中序遍历
void InOrderTraverse(BiTree T)
{
	if (T)
	{
		InOrderTraverse(T->lchild);
		cout << T->data << " ";
		InOrderTraverse(T->rchild);
	}
}

//带头结点中序线索化
void InOrderThreading(BiThrTree &Thrt, BiTree T)
{
	Thrt = new BiThrNode; //建立头结点
	Thrt->LTag = 0;		  //头结点有左孩子
	Thrt->RTag = 1;		  //头结点的右孩子为线索
	Thrt->rchild = Thrt;  //初始化右孩子指向自己
	if (!T)				  //如果树为空则左孩子也指向自己
	{
		Thrt->lchild = Thrt;
	}
	else
	{
		Thrt->lchild = T; //左孩子为树根
		Pre = Thrt;		  //开始线索化
		InThreading(T);
		Pre->rchild = Thrt; //线索化后Pre为最后一个节点，右孩子指向头结点
		Pre->RTag = 1;
		Thrt->rchild = Pre; //头结点的右孩子指向Pre
	}
}

//线索化后的遍历
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
		cout << p->data << " "; //这个语句不能放到上面的循环中
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
	cout << "请输入：";
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
